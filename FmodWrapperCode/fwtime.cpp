#include "fwtime.h"
#include <ctime>

namespace FW {
	namespace INTERNAL {
		time& Time() {
			static time s;
			return s;
		}

		void time::update() {
			_last = _current;
			_current = std::clock();
			_delta = (_current - _last) / static_cast<float>(CLOCKS_PER_SEC);
			if (_delta < 0.001) {
				_delta = 0.001;
			}
		}

		float time::delta() {
			return _delta;
		}
	}
}