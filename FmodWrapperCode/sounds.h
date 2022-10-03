#pragma once
#include "sound.h"
#include "defines.h" 
#include <unordered_map>

namespace FW {

	class sounds {
	public:

		API sound* create(std::string fileName, bool loop, float volume, bool streaming);
		API void release(sound* sound);

		API void releaseAll();

	private:
		friend API sounds& Sounds();
		sounds();
		std::unordered_map<int, sound*> map;
		int counter;
	};

	API sounds& Sounds();
}
