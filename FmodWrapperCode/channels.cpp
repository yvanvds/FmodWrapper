#include <log.h>
#include "channels.h"
#include "channel_internal.h"

namespace FW {
	channels& Channels() {
		static channels s;
		return s;
	}

	channels::channels() : _counter(0) {
		// create master
		_master = new channel();

		_fx = new channel("FX", true, -1, _master);
		_music = new channel("Music", false, -1, _master);
		_ambient = new channel("Ambient", true, -1, _master);
		_voice = new channel("Voice", false, -1, _master);
		_gui = new channel("Gui", false, -1, _master);
	}

	channel* channels::create(const std::string & name, bool canGoVirtual, channel* parent) {
		auto result = _map.emplace(_counter, new channel(name, canGoVirtual, _counter, parent));
		_counter++;

		if (result.second == true) {
			return result.first->second;
		}
		else {
			return nullptr;
		}
	}

	void channels::release(channel* channel) {
		int key = channel->_key;
		delete _map.at(key);
		_map.erase(key);
	}

	void channels::releaseAll() {
		auto it = _map.begin();
		while (it != _map.end()) {
			delete it->second;
			it++;
		}
		_map.clear();
	}

	channel* channels::Master() {
		return _master;
	}

	channel* channels::FX() {
		return _fx;
	}
	
	channel* channels::Music() {
		return _music;
	}
	
	channel* channels::Ambient() {
		return _ambient;
	}

	channel* channels::Voice() {
		return _voice;
	}

	channel* channels::Gui() {
		return _gui;
	}
}

