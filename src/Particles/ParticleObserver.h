#pragma once 

namespace SAPHRON
{
	// forward declare. 
	class ParticleEvent;

	// Base abstract class for particle observers.
	class ParticleObserver
	{
		public:
			// Update observer.
			virtual void ParticleUpdate(const ParticleEvent& pEvent) = 0;

			virtual ~ParticleObserver() {}
	};
}