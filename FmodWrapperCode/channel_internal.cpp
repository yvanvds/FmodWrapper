#include "channel_internal.h"
#include "system_internal.h"
#include "error.h"

namespace FW {
	namespace INTERNAL {
		channel::channel() : _isMaster(true) {
			result = System().get().getMasterChannelGroup(&fmod_channelgroup);
			ERRCHECK(result);
		}

		channel::channel(const std::string & name, channel* parent) : _isMaster(false) {
			result = System().get().createChannelGroup(name.c_str(), &fmod_channelgroup);
			ERRCHECK(result);
			if (parent != nullptr) {
				moveTo(*parent);
			}
		}

		channel::~channel() {
			if (fmod_channelgroup != nullptr) {
				result = fmod_channelgroup->release();
				ERRCHECK(result);
			}
		}

		void channel::canGoVirtual(bool value) {
			_canGoVirtual = value;
			int count;
			result = fmod_channelgroup->getNumChannels(&count);
			ERRCHECK(result);
			for (int i = 0; i < count; i++) {
				FMOD::Channel* channel;
				result = fmod_channelgroup->getChannel(i, &channel);
				ERRCHECK(result);
				result = channel->setPriority(_canGoVirtual ? 128 : 200);
				ERRCHECK(result);
			}
		}

		void channel::volume(float value) {
			if (value < 0) value = 0;
			result = fmod_channelgroup->setVolume(value);
			ERRCHECK(result);
		}

		void channel::moveTo(channel& parent) {
			result = parent.fmod_channelgroup->addGroup(fmod_channelgroup);
			ERRCHECK(result);
		}

		void channel::reverb(float wet) {
			result = fmod_channelgroup->setReverbProperties(0, wet);
			ERRCHECK(result);
		}

		bool channel::isValid() const {
			return fmod_channelgroup != nullptr;
		}
	}
}