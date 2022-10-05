#include "Demo08_Occlusion.h"


float OccludeValue = 0;

float OcclusionFunction(const FW::Vector& pos, const FW::Vector& listener) {
  // for simplicity's sake, we just check with a global var here.
  // In reality you should do a raycast here to check these positions with
  // the physx or bullet implementation in your game.
  return OccludeValue;
}


DemoOcclusion::DemoOcclusion()
{
	SetTitle("Occlusion Demo");
	AddAction('1', "Increase Occlusion", std::bind(&DemoOcclusion::OcclusionInc, this));
	AddAction('2', "Decrease Occlusion", std::bind(&DemoOcclusion::OcclusionDec, this));

	OccludeValue = 0;

	FW::System().occlusionCallback(OcclusionFunction);
	sound = FW::Sounds().create("../TestResources/contact.ogg", true, 1.f, false);
	sound->occlusionActive(true);
	sound->play();
}


DemoOcclusion::~DemoOcclusion()
{
    FW::System().occlusionCallback(nullptr);
}

void DemoOcclusion::ExplainDemo()
{
    std::cout << "This is a basic implementation of the sound occlusion callback." << std::endl;
}

void DemoOcclusion::OcclusionInc()
{
	OccludeValue += 0.1f;
}

void DemoOcclusion::OcclusionDec()
{
	OccludeValue -= 0.1f;
}
