#pragma once
#include "fmod.hpp"
#include "info.h"
#include "enums.h"

namespace FW {
	namespace INTERNAL {
		class system {
		public:
			bool init();
			void update();
			void close();

			void pause();
			void resume();
			int missedCallbacks();

			FMOD::System& get();

			float dopplerScale() const;
			float distanceFactor() const;
			float rolloffScale() const;

			void reverb(REVERB preset);

			const soundInfo& getSoundInfo();
			const cpuInfo& getCpuInfo();


		private:
			friend system& System();
			system();
			FMOD::System* fmod_system = nullptr;
			void* extradriverdata = 0;
			FMOD_RESULT result;

			float _dopplerScale;
			float _distanceFactor;
			float _rolloffScale;

			soundInfo _soundInfo;
			cpuInfo _cpuInfo;
		};

		system& System();
	}
}
