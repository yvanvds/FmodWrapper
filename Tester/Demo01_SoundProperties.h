
#pragma once

#include "basePage.h"

class DemoSoundProperties : public basePage
{
public:
	DemoSoundProperties();
	
	void IncSpeed();
	void DecSpeed();
	void IncVolume();
	void DecVolume();

private:
	FW::sound* sound;
};

