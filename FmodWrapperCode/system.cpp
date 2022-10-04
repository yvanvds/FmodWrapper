#include "system.h"
#include <iostream>
#include "fmod.hpp"
#include "system_internal.h"
#include <listener.h>
#include <channels.h>
#include <sounds.h>

FW::system & FW::System() {
	static FW::system s;
	return s;
}

bool FW::system::init() {
	bool result = INTERNAL::System().init();
	if (result) {
		Channels().Master()->volume(1.0f);
	}
	return result;
}

void FW::system::update()
{
	Sounds().update();
	Listener().update();
	INTERNAL::System().update();
}

FW::system& FW::system::reverb(REVERB preset) {
	INTERNAL::System().reverb(preset);
	return *this;
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

const FW::soundInfo& FW::system::getSoundInfo() {
	return INTERNAL::System().getSoundInfo();
}

const FW::cpuInfo& FW::system::getCpuInfo() {
	return INTERNAL::System().getCpuInfo();
}

