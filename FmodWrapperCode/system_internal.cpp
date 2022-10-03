#include "system_internal.h"
#include "sounds.h"
#include "error.h"
#include "fwtime.h"

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
			result = fmod_system->init(32, FMOD_INIT_NORMAL, extradriverdata);
			ERRCHECK(result);
			result = fmod_system->set3DSettings(1.0f, 1.0f, 1.0f);

			return true;
		}

		void system::update() {
			Time().update();
			result = fmod_system->update();
			ERRCHECK(result);
		}

		void system::close() {
			
			Sounds().releaseAll();
			result = fmod_system->release();
			ERRCHECK(result);
		}

		void system::pause() {
			
		}

		void system::resume() {

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
	}
}



