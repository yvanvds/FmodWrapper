
#pragma once
#include "basePage.h"

class DemoPlaySound :
	public basePage
{
public:
	DemoPlaySound();
	
	void ToggleSound();
	void PlaySound();
	void StopSound();
	void PauseSound();

private:
	FW::sound* sound;
};

