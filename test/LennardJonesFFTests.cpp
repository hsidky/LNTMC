#include "../src/ForceFields/LennardJonesFF.h"
#include "../src/ForceFields/ForceFieldManager.h"
#include "../src/Simulation/StandardSimulation.h"
#include "../src/Moves/MoveManager.h"
#include "../src/Moves/TranslateMove.h"
#include "../src/Particles/Particle.h"

#include "../src/Worlds/World.h"
#include "../src/Worlds/WorldManager.h"
#include "TestAccumulator.h"
#include "json/json.h"
#include "gtest/gtest.h"
#include <fstream>

using namespace SAPHRON;

TEST(LennardJonesFF, DefaultBehavior)
{
	double rcut = 14.0;
	LennardJonesFF ff(1.0, 1.0, {rcut});
	Particle s1({0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, "L1");
	Particle s2({1.5, 0.0, 0.0}, {0.0, 0.0, 0.0}, "L1");
	s1.AddNeighbor(&s2);
	s2.AddNeighbor(&s1);

	ForceFieldManager ffm;
	ffm.AddNonBondedForceField("L1", "L1", ff);

	// Validate invidual components first.
	auto NB = ff.Evaluate(s1, s2, s1.GetPosition() - s2.GetPosition(), 0);
	ASSERT_NEAR(-0.320336594278575, NB.energy, 1e-10);
	ASSERT_NEAR(-4.859086276627293e-04, ff.EnergyTailCorrection(0), 1e-10);
	ASSERT_NEAR(-0.002915451636909, ff.PressureTailCorrection(0), 1e-10);
	ASSERT_NEAR(0.772019220697437, NB.virial, 1e-10);

	auto H = ffm.EvaluateEnergy(s2);

	ASSERT_NEAR(-0.3203365, H.energy.intervdw, 1e-6);
	ASSERT_NEAR(-0.579014415, H.pressure.isotropic(), 1e-7);
}

// Validate results from NIST MC LJ standards 
// to confirm virial, energy, pressure calc. 
TEST(LennardJonesFF, ConfigurationValues)
{
	// Load file (assumes we are in build folder.
	std::ifstream t("../test/nist_lj_config1.json");
	std::stringstream buffer;
	buffer << t.rdbuf();
	// Read JSON.
	Json::Reader reader;
	Json::Value root;
	ASSERT_TRUE(reader.parse(buffer, root));

	// Build world.
	World* w = nullptr;
	ASSERT_NO_THROW(w = World::Build(root["worlds"][0], root["blueprints"]));
	ASSERT_NE(nullptr, w);

	ASSERT_EQ(800, w->GetParticleCount());
	w->UpdateNeighborList();
	ASSERT_EQ(3.5, w->GetNeighborRadius());
	ASSERT_EQ(0.5, w->GetSkinThickness());

	// Define potential (for 2 different rcut).
	LennardJonesFF ff(1.0, 1.0, {3.0, 3.0});

	// Evaluate energy and compare to LJ.
	ForceFieldManager ffm;
	ffm.AddNonBondedForceField("LJ", "LJ", ff);

	// rcut = 3.0.
	auto E = ffm.EvaluateEnergy(*w);
	ASSERT_NEAR(-4.3515E+03, E.energy.intervdw, 1e-1);
	ASSERT_NEAR(-1.9849E+02, E.energy.tail, 1e-2);
	auto virial = (E.pressure.pxx + E.pressure.pyy + E.pressure.pzz)*w->GetVolume();
	ASSERT_NEAR(-5.6867E+02, virial, 1e-2);

	// rcut = 4.0.
	LennardJonesFF ff2(1.0, 1.0, {4.0, 4.0});

	w->SetNeighborRadius(4.5);
	ffm.RemoveNonBondedForceField("LJ", "LJ");
	ffm.AddNonBondedForceField("LJ", "LJ", ff2);
	w->UpdateNeighborList();
	E = ffm.EvaluateEnergy(*w);

	ASSERT_NEAR(-4.4675E+03, E.energy.intervdw, 1e-1);
	ASSERT_NEAR(-8.3769E+01, E.energy.tail, 1e-2);
	virial = (E.pressure.pxx + E.pressure.pyy + E.pressure.pzz)*w->GetVolume();
	ASSERT_NEAR(-1.2639E+03, virial, 1e-1);

	delete w;
}

// Validate results from NIST MC LJ standards page.
// http://mmlapps.nist.gov/srs/LJ_PURE/mc.htm
TEST(LennardJonesFF, NISTValidation1)
{
	// Target reduced density to validate.
	double rdensity = 7.76E-01;
	int N = 500; // Number of LJ particles per NIST.
	double sigma = 1.0; 
	double eps   = 1.0; 
	//double kb = 1.0;
	double T = 0.85;
	double rcut = 3.0*sigma;

	// Prototype particle.
	Particle* ljatom = new Particle({0,0,0}, {0,0,0}, "LJ");
	Particle ljm("LJM");
	//ljm.AddChild(ljatom);

	// Add lj atom to world and initialize in simple lattice configuration.
	// World volume is adjusted by packworld.
	World world(1, 1, 1, rcut + 1.0, 1.0);
	world.PackWorld({ljatom}, {1.0}, N, rdensity);
	world.UpdateNeighborList();
	world.SetTemperature(T);

	// Initialize world manager.
	WorldManager wm;
	wm.AddWorld(&world);

	ASSERT_EQ(N, world.GetParticleCount());
	ASSERT_NEAR((double)N*pow(sigma,3)/rdensity, world.GetVolume(), 1e-10);

	// Initialize LJ forcefield.
	LennardJonesFF ff(eps, sigma, {rcut, rcut, rcut, rcut});
	ForceFieldManager ffm;
	ffm.AddNonBondedForceField("LJ", "LJ", ff);

	// Initialize moves. 
	TranslateMove move(0.22);
	MoveManager mm;
	mm.AddMove(&move);

	// Initialize observer.
	SimFlags flags;
	flags.world_energy = 1;
	flags.iteration = 1;
	flags.move_acceptances = 1;
	flags.world_pressure = 1;

	// Initialize accumulator. 
	TestAccumulator accumulator(flags, 10, 20000);

	// Initialize ensemble. 
	StandardSimulation ensemble(&wm, &ffm, &mm);
	ensemble.AddObserver(&accumulator);

	// Run 
	ensemble.Run(50000);

	// "Conservation" of energy and pressure.
	EPTuple H = ffm.EvaluateEnergy(world);
	ASSERT_NEAR(H.pressure.isotropic(), world.GetPressure().isotropic()-world.GetPressure().ideal, 1e-8);
	ASSERT_NEAR(H.energy.total(), world.GetEnergy().total(), 1e-8);

	auto P = accumulator.GetAveragePressures()[&world];

	std::cout << "virial: " << (P.pxx + P.pyy + P.pzz)/3.0 << " Ideal : " << P.ideal << " tail: " << P.ptail 
	<< std::endl;

	ASSERT_NEAR(-5.5121, accumulator.GetAverageEnergies()[&world].total()/(double)N, 1e-3);
	ASSERT_NEAR(6.7714E-03, accumulator.GetAveragePressures()[&world].isotropic(), 1e-3);	
}
