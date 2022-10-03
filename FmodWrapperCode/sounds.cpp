#include "sounds.h"
#include "sound_internal.h"

namespace FW {

	sounds& Sounds() {
		static sounds s;
		return s;
	}

	sounds::sounds() : counter(0) {

	}

	sound* sounds::create(std::string fileName, bool loop, float volume, bool streaming) {
		auto result = map.emplace(counter, new sound(fileName, loop, volume, streaming, counter));
		counter++;

		if (result.second == true) {
			return result.first->second;
		}
		else {
			return nullptr;
		}
	}

	void sounds::release(sound* sound) {
		int key = sound->key;
		delete map.at(key);
		map.erase(key);
	}

	void sounds::releaseAll() {
		auto it = map.begin();
		while (it != map.end()) {
			delete it->second;
			it++;
		}
		map.clear();
	}
}
