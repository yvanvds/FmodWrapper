#include "listener_internal.h"
#include "system_internal.h"
#include "vector_tools.h"
#include "fwtime.h"

namespace FW {
	namespace INTERNAL {
		listener& Listener() {
			static listener s;
			return s;
		}

		listener::listener() {
			_lastPos.zero();
			_velocity.zero();
			Vector forward(0.f);
			Vector up(0.f, 1.f, 0.f);
			update(_lastPos, forward, up);
		}

		const Vector& listener::velocity() const {
			return _velocity;
		}

		const Vector& listener::position() const {
			return _newPos;
		}

		void listener::update(const Vector& pos, const Vector& forward, const Vector& upward) {
			_newPos = pos * System().distanceFactor();
			_velocity = (_newPos - _lastPos) * (1.f / Time().delta());
			_lastPos = _newPos;

			auto position = ToFMOD(pos);
			auto velocity = ToFMOD(_velocity);
			auto fw = ToFMOD(forward);
			auto up = ToFMOD(upward);
			
			System().get().set3DListenerAttributes(
				0,
				&position,
				&velocity,
				&fw,
				&up
			);
		}
	}
}
