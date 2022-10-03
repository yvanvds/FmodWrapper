#include "system.h"
#include <iostream>
#include "fmod.hpp"
#include "system_internal.h"

FW::system & FW::System() {
	static FW::system s;
	return s;
}

bool FW::system::init() {
	return INTERNAL::System().init();
}

void FW::system::update()
{
	INTERNAL::System().update();
}

void FW::system::close()
{
	INTERNAL::System().close();
}

void FW::system::pause()
{
	INTERNAL::System().pause();
}

void FW::system::resume()
{
	INTERNAL::System().resume();
}

int FW::system::missedCallbacks()
{
	return 0;
}



