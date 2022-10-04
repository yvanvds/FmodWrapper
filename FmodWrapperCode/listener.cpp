#include "listener.h"
#include "listener_internal.h"

namespace FW {
	listener& Listener() {
		static listener s;
		return s;
	}

	listener::listener() {
		_pos.zero();
		_forward.zero().z = 1.f;
		_upward.zero().y = 1.f;
	}

	inline const Vector& listener::pos() const { return _pos; }
	inline const Vector& listener::forward() const { return _forward; }
	inline const Vector& listener::upward() const { return _upward; }

	const Vector& listener::vel() const {
		return INTERNAL::Listener().velocity();
	}

	void listener::move(const Vector& pos, const Vector& forward, const Vector& upward) {
		_pos = pos;
		_forward = forward;
		_upward = upward;
	}

	void listener::update() {
		
		INTERNAL::Listener().update(_pos, _forward, _upward);
	}
}
