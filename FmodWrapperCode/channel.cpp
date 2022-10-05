#include "channel.h"
#include "channel_internal.h"
#include "system_internal.h"
#include "channels.h"

namespace FW {
	channel::channel() : _key(-1) {
		internal_channel = new INTERNAL::channel();
	}

	channel::channel(const std::string& name, bool canGoVirtual, int key, channel* parent) : _key(key) {
		internal_channel = new INTERNAL::channel(name, parent == nullptr ? Channels().Master()->internal_channel : parent->internal_channel);
		internal_channel->canGoVirtual(canGoVirtual);
		internal_channel->volume(1.0f);
		_name = name;
	}

	channel::~channel() {
		if (internal_channel != nullptr) {
			delete internal_channel;
			internal_channel = nullptr;
		}
	}

	channel& channel::volume(float value) {
		_volume = value;
		internal_channel->volume(value);
		return *this;
	}

	float channel::volume() const {
		return _volume;
	}

	channel& channel::moveTo(channel& parent) {
		internal_channel->moveTo(*parent.internal_channel);
		return *this;
	}

	channel& channel::setVirtual(bool value) {
		_virtual = value;
		internal_channel->canGoVirtual(value);
		return *this;
	}

	bool channel::getVirtual() const {
		return _virtual;
	}

	channel& channel::reverb(float wet) {
		internal_channel->reverb(wet);
		return *this;
	}

	API bool channel::isValid() const {
		return internal_channel->isValid();
	}

	API const std::string& channel::name() const {
		return _name;
	}
}