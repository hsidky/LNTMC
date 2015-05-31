#pragma once

#include "../Simulation/SimObservable.h"
#include "../Properties/Energy.h"
#include <map>
#include <vector>

namespace SAPHRON
{
	// Base class for simulation Ensembles. An ensemble is provided with a reference to a World and a
	// ForceFieldManager. The World is responsible for handling the "box" geometry and particles. The
	// ForeceFieldManager contains the forcefield data for all Particle types and interactions.
	class Ensemble : public SimObservable
	{
		private:
			// Boltzmann constant.
			double _kb = 1.0;

			// Iteration counter.
			int _iterations = 0;

		protected:

			// Increment iterations.
			inline void IncrementIterations()
			{
				++_iterations;
			}

			// Visit children.
			virtual void VisitChildren(Visitor& v) = 0;

		public:
			typedef std::map<std::string, double> AcceptanceMap;

			// Run the Ensemble simulation for a specified number of iterations.
			virtual void Run(int iterations) = 0;

			// Sets the Boltzmann constant.
			void SetBoltzmannConstant(double kb)
			{
				_kb = kb;
			}

			// Gets the Boltzmann constant.
			inline double GetBoltzmannConstant()
			{
				return _kb;
			}

			// Gets the current iteration count.
			inline int GetIteration()
			{
				return _iterations;
			}

			// Reset iteration count.
			void ResetIterations()
			{
				_iterations = 0;
			}

			// Accept a visitor.
			virtual void AcceptVisitor(class Visitor &v)
			{
				v.Visit(this);
				VisitChildren(v);
			}

			/* Properties */
			virtual double GetTemperature() { return 0.0; }
			virtual Energy GetEnergy() { return Energy(0,0); }
			virtual double GetPressure() { return 0.0; }
			virtual AcceptanceMap GetAcceptanceRatio() { return {}; }

			virtual ~Ensemble(){}
	};
}
