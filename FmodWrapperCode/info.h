#pragma once
#include "defines.h"

namespace FW {
	struct API soundInfo {
	public:
		int allSounds;
		int realSounds;
		int virtualSounds;
	};

	struct API cpuInfo {
	public: 
		float dsp;
		float stream;
		float update;
		float total;
	};
}
