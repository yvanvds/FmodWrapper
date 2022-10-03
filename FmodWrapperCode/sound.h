#pragma once
#include <string>
#include "defines.h"
#include "vector.h"

namespace FW {
	namespace INTERNAL {
		class sound;
	}

	class sound {
	public:
		API sound& looping(bool value);
		API bool looping() const;

		API sound& play();
		API bool isPlaying();

		API sound& pause();
		API bool isPaused();

		API sound& stop();
		API bool isStopped();

		API sound& toggle();
		API sound& restart();

		API unsigned int length() const;
		API unsigned int time() const;
		API sound& time(unsigned int value);

		API bool isValid() const;

		API sound& pos(const Vector& pos);
		API const Vector& pos() const;

		API sound& speed(float value);
		API float speed() const;

		API sound& size(float value);
		API float size() const;

		API sound& volume(float value, unsigned int time = 0);
		API float volume() const;

		API sound& relative(bool value);
		API bool relative() const;

		API sound& doppler(float value);
		API float doppler() const;




	private:
		friend class sounds;
		sound(std::string fileName, bool loop, float volume, bool streaming, int key);
		~sound();

		int key;
		INTERNAL::sound* internal_sound;
	};
}