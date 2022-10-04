#include "listener_internal.h"
#include "system_internal.h"
#include "vector_tools.h"
#include "fwtime.h"
#include <error.h>

namespace FW {
	namespace INTERNAL {
		listener& Listener() {
			static listener s;
			return s;
		}

		listener::listener()
		{
			_lastPos.zero();
			_velocity.zero();
		}

		const Vector& listener::velocity() const {
			return _velocity;
		}

		const Vector& listener::position() const {
			return _newPos;
		}

		void listener::update(const Vector& pos, const Vector& forward, const Vector& upward) {
			_newPos = pos * System().distanceFactor();
			float delta = Time().delta();
			_velocity = (_newPos - _lastPos) / Time().delta();
			_lastPos = _newPos;

			auto position = ToFMOD(pos);
			auto velocity = ToFMOD(_velocity);
			auto fw = ToFMOD(forward);
			auto up = ToFMOD(upward);
			
			result = System().get().set3DListenerAttributes(
				0,
				&position,
				&velocity,
				&fw,
				&up
			);
			ERRCHECK(result);
		}
	}
}
