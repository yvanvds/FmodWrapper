#pragma once
#include <string>
#include "defines.h"

namespace FW {
	namespace INTERNAL {
		class channel;
		class sound;
	}

	class channel {
	public:
		API channel& volume(float value);
		API float volume() const;

		API channel& moveTo(channel& parent);

		API channel& setVirtual(bool value);
		API bool getVirtual() const;

		API channel& reverb(float wet);

		API bool isValid() const;

		API const std::string & name() const;

	private:
		friend class channels;
		friend class sound;
		channel(); // gets the master channel group
		channel(const std::string & name, bool canGoVirtual, int key, channel * parent);
		~channel();

		float _volume = 1.0f;
		bool _virtual = true;
		std::string _name;
		int _key;
		INTERNAL::channel* internal_channel = nullptr;
	};
}