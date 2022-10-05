#include "system_internal.h"
#include "sounds.h"
#include "error.h"
#include "fwtime.h"
#include <listener_internal.h>
#include <channels.h>
#include "conversions.h"

namespace FW {
	namespace INTERNAL {
		system& System()
		{
			static system s;
			return s;
		}

		system::system()
			: _dopplerScale(1.f), _distanceFactor(1.f), _rolloffScale(1.f)
		{

		}

		bool system::init() {
			result = FMOD::System_Create(&fmod_system);
			ERRCHECK(result);
			result = fmod_system->setSoftwareChannels(128);
			result = fmod_system->init(4095, FMOD_INIT_NORMAL | FMOD_INIT_VOL0_BECOMES_VIRTUAL, extradriverdata);
			ERRCHECK(result);
			result = fmod_system->set3DSettings(1.0f, 1.0f, 1.0f);
			ERRCHECK(result);

			return true;
		}

		void system::update() {
			Time().update();
			result = fmod_system->update();
			ERRCHECK(result);
		}

		void system::close() {
			
			Sounds().releaseAll();
			Channels().releaseAll();
			result = fmod_system->release();
			ERRCHECK(result);
		}

		void system::pause() {
			
		}

		void system::resume() {

		}

		void system::reverb(REVERB preset) {
			FMOD_REVERB_PROPERTIES prop = ToFMOD(preset);
			result = fmod_system->setReverbProperties(0, &prop);
			ERRCHECK(result);
		}

		int system::missedCallbacks() {
			return 0;
		}

		float system::dopplerScale() const { return _dopplerScale; }
		float system::distanceFactor() const { return _distanceFactor; }
		float system::rolloffScale() const { return _rolloffScale; }

		FMOD::System& system::get() {
			return *fmod_system;
		}

		const soundInfo & system::getSoundInfo() {
			int allChannels;
			int realChannels;
			result = fmod_system->getChannelsPlaying(&allChannels, &realChannels);
			ERRCHECK(result);
			_soundInfo.allSounds = allChannels;
			_soundInfo.realSounds = realChannels;
			_soundInfo.virtualSounds = allChannels - realChannels;
			return _soundInfo;
		}

		const cpuInfo& system::getCpuInfo() {
			FMOD_CPU_USAGE usage;

			result = fmod_system->getCPUUsage(&usage);
			ERRCHECK(result);
			_cpuInfo.dsp = usage.dsp;
			_cpuInfo.stream = usage.stream;
			_cpuInfo.update = usage.update;
			_cpuInfo.total = usage.convolution1 + usage.convolution2 + usage.dsp + usage.stream + usage.update;
			return _cpuInfo;
		}

		void system::occlusionCallback(float(*func)(const Vector&, const Vector&)) {
			_occlusionPtr = func;
		}

		float system::getOcclusion(const Vector& source) {
			if (_occlusionPtr == nullptr) return 0;
			return _occlusionPtr(source, Listener().position());
		}

	}
}



