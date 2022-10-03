#pragma once
#include "defines.h"
#include "vector.h"

namespace FW {
	class listener {
	public:
		API void update(const Vector& pos, const Vector& forward, const Vector& upward);

		API const Vector& pos() const;
		API const Vector& vel() const;
		API const Vector& forward() const;
		API const Vector& upward() const;

	private:
		friend API listener& Listener();
		listener();

		Vector _pos, _forward, _upward;
	};

	API listener& Listener();
}