
#pragma once

#include "basePage.h"

class DemoReverb : public basePage
{
public:
  DemoReverb();
  ~DemoReverb();

  virtual void ExplainDemo();

private:
  void MoveForward();
  void MoveBack();
  void GlobalReverbHall();
  void GlobalReverbSewer();
  void GlobalReverbOff();

  FW::sound* voice;
  //YSE::reverb bathroom, hall, sewer, custom;*/
};

