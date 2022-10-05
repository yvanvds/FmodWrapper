#include "reverbs.h"

namespace FW {
	reverbs& Reverbs() {
		static reverbs s;
		return s;
	}

	reverbs::reverbs() : _counter(0) {

	}

	reverb* reverbs::create(REVERB preset) {
		auto result = _map.emplace(_counter, new reverb(preset, _counter));
		_counter++;

		if (result.second == true) {
			return result.first->second;
		}
		else {
			return nullptr;
		}
	}

	void reverbs::release(reverb* reverb) {
		int key = reverb->_key;
		delete _map.at(key);
		_map.erase(key);
	}

	void reverbs::releaseAll() {
		auto it = _map.begin();
		while (it != _map.end()) {
			delete it->second;
			it++;
		}
		_map.clear();
	}
}