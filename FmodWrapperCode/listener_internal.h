#pragma once
#include "vector.h"


namespace FW {
	namespace INTERNAL {
		class listener {
		public:
			listener();
			const Vector& velocity() const;
			const Vector& position() const;
			void update(const Vector& pos, const Vector& forward, const Vector& upward);
			
		private:
			Vector _lastPos;
			Vector _newPos;
			Vector _velocity;
		};

		listener& Listener();
	}
}