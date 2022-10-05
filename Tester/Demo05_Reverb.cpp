
#include "Demo05_Reverb.h"


DemoReverb::DemoReverb()
{
    FW::channel * channel = FW::Channels().Voice();
	voice = FW::Sounds().create("../testResources/singing.wav", true, 1.0f, false, channel);
	voice->play();
  
    // set global reverb
    FW::System().reverb(FW::R_GENERIC);

    // enable reverb on voice channel
    // btw, you can enable this for every channel except master
    channel->reverb(1.0f);

    // 'world' reverbs can be added at specific positions
    // size is the maximum distance from the reverb at which it its influence is at maximum level
    // rolloff indicates how far outside its size it will drop to zero influence (linear curve)

 // // add reverb at 5 meter
    bathroom = FW::Reverbs().create(FW::R_BATHROOM);
    bathroom->set3D(FW::Vector(0.f, 0.f, 5.f), 2, 2);

 // // add reverb at 10 meter
    hall = FW::Reverbs().create(FW::R_HALLWAY);
    hall->set3D(FW::Vector(0.f, 0.f, 10.f), 2, 2);

 // // add reverb at 15 meter
    sewer = FW::Reverbs().create(FW::R_SEWERPIPE);
    sewer->set3D(FW::Vector(0.f, 0.f, 15.f), 2, 2);

 // // add reverb at 20 meter
 // custom.create();
 // custom.setPosition(YSE::Pos(0, 0, 20)).setSize(1).setRollOff(1);
 // // for this reverb we use custom parameters instead of a preset
 // // (these are meant to sound awkward)
 // custom.setRoomSize(1.0f).setDamping(0.1f).setDryWetBalance(0.0f, 1.0f).setModulation(6.5, 0.7);
 // custom.setReflection(0, 1000, 0.5f).setReflection(1, 1500, 0.6f);
 // custom.setReflection(2, 2100, 0.8f).setReflection(3, 2999, 0.9f);

  SetTitle("Reverb Demo");
  AddAction('q', "Move sound and listener forward.", std::bind(&DemoReverb::MoveForward, this));
  AddAction('a', "Move sound and listener backward.", std::bind(&DemoReverb::MoveBack, this));
  AddAction('1', "Global reverb to concerthall.", std::bind(&DemoReverb::GlobalReverbHall, this));
  AddAction('2', "Global reverb to sewerpipe.", std::bind(&DemoReverb::GlobalReverbSewer, this));
  AddAction('3', "Turn global reverb off.", std::bind(&DemoReverb::GlobalReverbOff, this));
}


DemoReverb::~DemoReverb()
{
    FW::System().reverb(FW::R_OFF);
}

void DemoReverb::ExplainDemo()
{
  std::cout << "This example as one global reverb. On top of that, there are several localized reverbs which will alter the listener's experience when moving around." << std::endl;
}

void DemoReverb::ShowStatus() {
    FW::Vector pos = FW::Listener().pos();
    std::cout << "listener z position: " << pos.z << std::endl;
}

void DemoReverb::MoveForward()
{
  FW::Vector pos = FW::Listener().pos();
  pos.z += 0.1;
  FW::Listener().move(pos, FW::Vector(0.f, 0.f, 1.f), FW::Vector(0.f, 1.f, 0.f));
  voice->pos(pos);
}

void DemoReverb::MoveBack()
{
    FW::Vector pos = FW::Listener().pos();
    pos.z -= 0.1;
    FW::Listener().move(pos, FW::Vector(0.f, 0.f, 1.f), FW::Vector(0.f, 1.f, 0.f));
    voice->pos(pos);
}

void DemoReverb::GlobalReverbHall()
{
  FW::System().reverb(FW::R_CONCERTHALL);
}

void DemoReverb::GlobalReverbSewer()
{
    FW::System().reverb(FW::R_SEWERPIPE);
}

void DemoReverb::GlobalReverbOff()
{
    FW::System().reverb(FW::R_OFF);
}
