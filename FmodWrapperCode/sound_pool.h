#pragma once
#include "fmod.hpp"
#include <string>
#include <unordered_map>

namespace FW {
	namespace INTERNAL {
		struct poolResource {
			int users = 0;
			FMOD::Sound * sound;
		};

		class soundPool {
		public:
			FMOD::Sound* claim(const std::string& fileName);
			void release(const std::string& fileName);

		private:
			friend soundPool& SoundPool();
			soundPool();
			std::unordered_map<std::string, poolResource> map;
			FMOD_RESULT result;
		};

		soundPool& SoundPool();
	}
}