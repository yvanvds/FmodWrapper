#include "sound_pool.h"
#include "system_internal.h"
#include  "error.h"

namespace FW {
	namespace INTERNAL {
		soundPool& SoundPool() {
			static soundPool s;
			return s;
		}

		soundPool::soundPool() {

		}
		
		FMOD::Sound* soundPool::claim(const std::string& fileName) {
			auto sound= map.find(fileName);
			if (sound != map.end()) {
				sound->second.users++;
				return sound->second.sound;
			}
			else {
				auto newitem = map.emplace(fileName, poolResource());
				if (newitem.second == true) {
					result = System().get().createSound(fileName.c_str(), FMOD_3D, 0, &newitem.first->second.sound);
					ERRCHECK(result);
					newitem.first->second.users = 1;
					return newitem.first->second.sound;
				}
				else {
					return nullptr;
				}
			}
		}

		void soundPool::release(const std::string& fileName) {
			auto sound = map.find(fileName);
			if (sound != map.end()) {
				sound->second.users--;
				if (sound->second.users == 0) {
					sound->second.sound->release();
					map.erase(fileName);
				}
			}
		}


	}
}