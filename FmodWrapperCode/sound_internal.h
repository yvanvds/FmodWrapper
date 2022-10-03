#pragma once
#include "fmod.hpp"
#include <string>
#include "vector.h"

namespace FW {
	namespace INTERNAL {
		enum SOUND_INTENT {
			SI_PLAY,
			SI_PAUSE,
			SI_STOP,
			SI_NONE,
		};

		class sound {
		public:
			sound(std::string fileName, bool loop, float volume, bool streaming);
			~sound();

			bool isValid() const;

			void looping(bool value);
			bool looping() const;

			void play();
			bool isPlaying() const;

			void pause();
			bool isPaused() const;

			void stop();
			bool isStopped() const;

			void toggle();
			void restart();

			void pos(const Vector& pos);
			const Vector& pos() const;

			void speed(float value);
			float speed() const;

			void size(float value);
			float size() const;

			void volume(float value, unsigned int time = 0);
			float volume() const;

			void relative(bool value);
			bool relative() const;

			void doppler(float value);
			float doppler() const;

			unsigned int length() const;
			unsigned int time() const;
			void time(unsigned int value);

		private:
			FMOD::Sound* fmod_sound = nullptr;
			FMOD::Channel* fmod_channel = nullptr;
			FMOD_RESULT result;
			bool loop;
			SOUND_INTENT intent = SI_NONE;
			float _volume;
			unsigned int _volumeRamp = 0;

			Vector _newPos, _lastPos, _velocity;
			bool _isRelative = false;
			float _speed = 1.f;
			float _frequency = 1;
			float _doppler = 0;
			float _size = 5000;
		};
	}
}
