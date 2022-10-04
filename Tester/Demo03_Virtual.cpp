

#include "Demo03_Virtual.h"
#include <cstdlib>


DemoVirtual::DemoVirtual()
{
	/*YSE::Log().setHandler(this);
	YSE::System().maxSounds(100);*/

	SetTitle("Virtual Sounds");
	AddAction('1', "Add 10 sounds", std::bind(&DemoVirtual::AddSound, this));
}

DemoVirtual::~DemoVirtual()
{
	//YSE::Log().setHandler(nullptr);
}



void DemoVirtual::ExplainDemo()
{
	std::cout << "Virtualization allows you to add lots of sound to a scene. Only the sounds nearest to the listener will play." << std::endl;
	std::cout << "Press the spacebar to add 10 sounds at a random position." << std::endl;
}

void DemoVirtual::ShowStatus()
{
	const FW::soundInfo & info = FW::System().getSoundInfo();
	const FW::cpuInfo& cpu = FW::System().getCpuInfo();
	std::cout << std::endl;
	std::cout << "Total   Sounds: " << info.allSounds << std::endl;
	std::cout << "Real    Sounds: " << info.realSounds << std::endl;
	std::cout << "Virtual Sounds: " << info.virtualSounds << std::endl;
	std::cout << std::endl;
	std::cout << "cpu    (dsp): " << cpu.dsp << std::endl;
	std::cout << "cpu (stream): " << cpu.stream << std::endl;
	std::cout << "cpu (update): " << cpu.update << std::endl;
	std::cout << "cpu  (total): " << cpu.total << std::endl;
}

void DemoVirtual::AddMessage(const std::string & message)
{
	std::cout << message << std::endl;
}

void DemoVirtual::AddSound()
{
	for (int i = 0; i < 10; i++) {
		switch (FW::Random(4)) {
		case 0: sounds.emplace_front(FW::Sounds().create("../testResources/contact.ogg", true, 0.1f, false)); break;
		case 1: sounds.emplace_front(FW::Sounds().create("../testResources/drone.ogg", true, 0.1f, false)); break;
		case 2: sounds.emplace_front(FW::Sounds().create("../testResources/kick.ogg", true, 0.1f, false)); break;
		case 3: sounds.emplace_front(FW::Sounds().create("../testResources/subtle_beat.ogg", true, 0.1f, false)); break;
		}
		if (sounds.front()->isValid()) {
			sounds.front()->pos(FW::Vector(FW::Random(20) - 10.f, FW::Random(20) - 10.f, FW::Random(20) - 10.f));
			sounds.front()->play();
			counter++;
		}
	}
}

