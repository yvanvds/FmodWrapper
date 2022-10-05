#include "reverb.h"
#include "reverb_internal.h"

namespace FW {
	reverb::reverb(REVERB preset, int key) : _key(key), internal_reverb(new INTERNAL::reverb(preset)) {
		_preset = preset;
	}

	reverb::~reverb() {
		if (internal_reverb != nullptr) {
			delete internal_reverb;
			internal_reverb = nullptr;
		}
	}

	reverb& reverb::setPreset(REVERB preset) {
		_preset = preset;
		internal_reverb->setProperties(preset);
		return *this;
	}

	REVERB reverb::preset() const {
		return _preset;
	}

	reverb& reverb::set3D(const Vector& pos, float minDistance, float maxDistance) {
		_position = pos;
		_minDistance = minDistance;
		_maxDistance = maxDistance;
		internal_reverb->set3DAttributes(pos, minDistance, maxDistance);
		return *this;
	}

	const Vector& reverb::pos() const {
		return _position;
	}

	float reverb::maxDistance() const {
		return _maxDistance;
	}

	float reverb::minDistance() const {
		return _minDistance;
	}

	bool reverb::isActive() const {
		return _active;
	}

	reverb& reverb::setActive(bool value) {
		_active = value;
		internal_reverb->setActive(value);
		return *this;
	}
}