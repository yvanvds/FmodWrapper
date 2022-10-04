#include "Demo04_Channels.h"

/* Channels

In FW, Channels are groups of sounds that can be modified together. For example, changing the volume
of a channel will impact all sounds in the channel. But it is also possible to link DSP filters to
channels, or asign reverb.

Channels can also be members of other channels. So you could build a more complex tree of channels and
sounds. If you remove a custom made channel, all sounds will be moved to the master channel. Moving sounds
between channels is posible, but there might be glitches if the channel's gain level is very different.

*/

DemoChannels::DemoChannels() 
{
	customChannel = FW::Channels().create("my channel", true, FW::Channels().Master());

	//// add a sound to your custom channel
	kick = FW::Sounds().create("../testResources/kick.ogg", true, 1.f, false, customChannel);
	kick->play();

	//// add a sound to the music channel
	pulse = FW::Sounds().create("../testResources/subtle_beat.ogg", true, 1.f, false, FW::Channels().Music());
	pulse->play();

	SetTitle("Custom Channels");
	AddAction('q', "Increase Volume (Master Channel)", std::bind(&DemoChannels::MasterIncVol, this));
	AddAction('a', "Decrease Volume (Master Channel)", std::bind(&DemoChannels::MasterDecVol, this));

	AddAction('w', "Increase Volume (Custom Channel)", std::bind(&DemoChannels::CustomIncVol, this));
	AddAction('s', "Decrease Volume (Custom Channel)", std::bind(&DemoChannels::CustomDecVol, this));

	AddAction('e', "Increase Volume (Music Channel)", std::bind(&DemoChannels::MusicIncVol, this));
	AddAction('d', "Decrease Volume (Music Channel)", std::bind(&DemoChannels::MusicDecVol, this));

	AddAction('r', "Delete Custom Channel", std::bind(&DemoChannels::CustomDelete, this));
}

DemoChannels::~DemoChannels()
{
	CustomDelete();
}

void DemoChannels::ExplainDemo()
{
	std::cout << "Sounds are mixed in channels. Every channel is linked to the global channel. Custom channels can be created. If you delete a channel, the sounds in that channel move to the parent channel." << std::endl;
}

void DemoChannels::MasterIncVol()
{
	FW::Channels().Master()->volume(FW::Channels().Master()->volume() + 0.1f);
}

void DemoChannels::MasterDecVol()
{
	FW::Channels().Master()->volume(FW::Channels().Master()->volume() - 0.1f);
}

void DemoChannels::CustomIncVol()
{
	if (customChannel != nullptr) customChannel->volume(customChannel->volume() + 0.1f);
}

void DemoChannels::CustomDecVol()
{
	if (customChannel != nullptr) customChannel->volume(customChannel->volume() - 0.1f);
}

void DemoChannels::MusicIncVol()
{
	FW::Channels().Music()->volume(FW::Channels().Music()->volume() + 0.1f);
}

void DemoChannels::MusicDecVol()
{
	FW::Channels().Music()->volume(FW::Channels().Music()->volume() - 0.1f);
}

void DemoChannels::CustomDelete()
{
	if (customChannel != nullptr) {
		FW::Channels().release(customChannel);
		customChannel = nullptr;
		std::cout << "The custom channel is deleted. All sounds and subchannels are automatically moved to the master channel." << std::endl;
	}
}

