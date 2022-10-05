#pragma once
#include "defines.h" 
#include <string>
#include "info.h"
#include "enums.h"
#include "vector.h"

namespace FW {
	const ::std::string VERSION = "1.0.77";

	class API system
	{
	public:
		bool init();
		void update();
		void close();

		void pause();
		void resume();
		int missedCallbacks();

		const soundInfo& getSoundInfo();
		const cpuInfo& getCpuInfo();

		system& reverb(REVERB preset);
		system& occlusionCallback(float(*func)(const Vector&, const Vector&));

		std::string version() const { return VERSION; }

	};

	API system& System();
}


