#include "../src/ForceFields/LennardJonesFF.h"
#include "../src/ForceFields/ForceFieldManager.h"
#include "../src/Ensembles/NVTEnsemble.h"
#include "../src/Moves/MoveManager.h"
#include "../src/Moves/TranslateMove.h"
#include "../src/Particles/Site.h"
#include "../src/Simulation/ConsoleObserver.h"
#include "../src/Worlds/SimpleWorld.h"
#include "gtest/gtest.h"

using namespace SAPHRON;

TEST(LennardJonesFF, DefaultBehavior)
{
	LennardJonesFF ff(1.0, 1.0, 14);
	Site s1({0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, "L1");
	Site s2({1.5, 0.0, 0.0}, {0.0, 0.0, 0.0}, "L1");
	s1.AddNeighbor(&s2);
	s2.AddNeighbor(&s1);

	ForceFieldManager ffm;
	ffm.AddForceField("L1", "L1", ff);

	std::map<int, int> compositions = 
	{
		{s1.GetSpeciesID(), 1000}
	};

	// Validate invidual components first.
	auto NB = ff.Evaluate(s1, s2);
	ASSERT_NEAR(-0.320336594278575, NB.energy, 1e-10);
	ASSERT_NEAR(-4.859086276627293e-04, ff.EnergyTailCorrection(), 1e-10);
	ASSERT_NEAR(-0.002915451636909, ff.PressureTailCorrection(), 1e-10);
	ASSERT_NEAR(0.772019220697437, NB.virial, 1e-10);

	auto H = ffm.EvaluateHamiltonian(s2, compositions, 30*30*30);

	ASSERT_NEAR(-0.320449670350796, H.energy.nonbonded, 1e-10);
	ASSERT_NEAR(-2.144487494523771e-05, H.pressure.isotropic(), 1e-9);
}

// Validate results from NIST MC LJ standards page.
// http://mmlapps.nist.gov/srs/LJ_PURE/mc.htm
TEST(LennardJonesFF, ReducedProperties)
{
	// Target reduced density to validate.
	double rdensity = 9.00E-03;
	int N = 500; // Number of LJ particles per NIST.
	double sigma = 1.0; 
	double eps   = 1.0; 
	double kb = 1.0;
	double T = 0.85;

	double volume = (double)N*pow(sigma,3)/rdensity;
	double side = pow(volume, 1.0/3.0);
	double rcut = 3.0*sigma;

	// Prototype particle.
	Site ljatom({0,0,0}, {0,0,0}, "LJ");

	// Add lj atom to world and initialize in simple lattice configuration.
	SimpleWorld world(side, side, side, rcut + 5.0);
	world.SetSkinThickness(5.0);
	world.ConfigureParticles({&ljatom}, {1.0}, N);
	world.UpdateNeighborList();

	ASSERT_EQ(N, world.GetParticleCount());
	ASSERT_NEAR(volume, world.GetVolume(), 1e-10);

	// Initialize LJ forcefield.
	LennardJonesFF ff(eps, sigma, rcut);
	ForceFieldManager ffm;
	ffm.AddForceField("LJ", "LJ", ff);

	// Initialize moves. 
	TranslateMove move(1.0);
	MoveManager mm;
	mm.PushMove(move);

	// Initialize observer.
	SimFlags flags;
	flags.temperature = 1;
	flags.energy = 1;
	flags.iterations = 1;
	flags.acceptance = 1;
	ConsoleObserver observer(flags, 100);

	// Initialize ensemble. 
	NVTEnsemble ensemble(world, ffm, mm, T, 34435);
	ensemble.SetBoltzmannConstant(kb);
	ensemble.AddObserver(&observer);
	// Run 
	ensemble.Run(100000);
}