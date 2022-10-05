
#pragma once

#include "basePage.h"

class DemoReverb : public basePage
{
public:
  DemoReverb();
  ~DemoReverb();

  virtual void ExplainDemo();
  virtual void ShowStatus();

private:
  void MoveForward();
  void MoveBack();
  void GlobalReverbHall();
  void GlobalReverbSewer();
  void GlobalReverbOff();

  FW::sound* voice;
  FW::reverb* bathroom, * hall, * sewer;
};

