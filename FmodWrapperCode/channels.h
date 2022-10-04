#pragma once

#include "channel.h"
#include "defines.h"
#include <unordered_map>

namespace FW {
	class channels {
	public:
		API channel* create(const std::string & name, bool canGoVirtual, channel* parent);
		API void release(channel* channel);
		API void releaseAll();

		API channel * Master();
		API channel * FX();
		API channel * Music();
		API channel * Ambient();
		API channel * Voice();
		API channel * Gui();

	private:
		friend API channels& Channels();
		channels();

		std::unordered_map<int, channel*> _map;
		int _counter;

		channel* _master;
		channel* _fx;
		channel* _music;
		channel* _ambient;
		channel* _voice;
		channel* _gui;
	};

	API channels& Channels();
}