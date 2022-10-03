#pragma once
#include "defines.h" 
#include <string>

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

		std::string version() const { return VERSION; }

	};

	API system& System();
}


