
#pragma once

#include "basePage.h"

class DemoLoadPatcher : public basePage {
public:
  DemoLoadPatcher();

  void LoadPatch1();

	void FreqUp();
	void FreqDown();

	void LfoUp();
	void LfoDown();

	void VolumeUp();
	void VolumeDown();

private:
  //YSE::sound sound;
  //YSE::patcher patcher;

	float noteValue;
	float lfoValue;
	float volumeValue;
};