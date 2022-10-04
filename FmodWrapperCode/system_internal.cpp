#include "system_internal.h"
#include "sounds.h"
#include "error.h"
#include "fwtime.h"
#include <channels.h>

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
			FMOD_REVERB_PROPERTIES prop = FMOD_PRESET_OFF;
			switch (preset) {
				case R_OFF: prop = FMOD_PRESET_OFF; break;
				case R_GENERIC: prop = FMOD_PRESET_GENERIC; break;
				case R_PADDEDCELL: prop = FMOD_PRESET_PADDEDCELL; break;
				case R_ROOM: prop = FMOD_PRESET_ROOM; break;
				case R_BATHROOM: prop = FMOD_PRESET_BATHROOM; break;
				case R_LIVINGROOM: prop = FMOD_PRESET_LIVINGROOM; break;
				case R_STONEROOM: prop = FMOD_PRESET_STONEROOM; break;
				case R_AUDITORIUM: prop = FMOD_PRESET_AUDITORIUM; break;
				case R_CONCERTHALL: prop = FMOD_PRESET_CONCERTHALL; break;
				case R_CAVE: prop = FMOD_PRESET_CAVE; break;
				case R_ARENA: prop = FMOD_PRESET_ARENA; break;
				case R_HANGAR: prop = FMOD_PRESET_HANGAR; break;
				case R_CARPETTEDHALLWAY: prop = FMOD_PRESET_CARPETTEDHALLWAY; break;
				case R_HALLWAY: prop = FMOD_PRESET_HALLWAY; break;
				case R_STONECORRIDOR: prop = FMOD_PRESET_STONECORRIDOR; break;
				case R_ALLEY: prop = FMOD_PRESET_ALLEY; break;
				case R_FOREST: prop = FMOD_PRESET_FOREST; break;
				case R_CITY: prop = FMOD_PRESET_CITY; break;
				case R_MOUNTAINS: prop = FMOD_PRESET_MOUNTAINS; break;
				case R_QUARRY: prop = FMOD_PRESET_QUARRY; break;
				case R_PLAIN: prop = FMOD_PRESET_PLAIN; break;
				case R_PARKINGLOT: prop = FMOD_PRESET_PARKINGLOT; break;
				case R_SEWERPIPE: prop = FMOD_PRESET_SEWERPIPE; break;
				case R_UNDERWATER: prop = FMOD_PRESET_UNDERWATER; break;
			}
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
	}
}



