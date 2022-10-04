#pragma once
#include "defines.h"
#include "vector.h"
#include "system.h"

namespace FW {
	class listener {
	public:
		
		API void move(const Vector& pos, const Vector& forward, const Vector& upward);

		API const Vector& pos() const;
		API const Vector& vel() const;
		API const Vector& forward() const;
		API const Vector& upward() const;

		//Called internally
		

	private:
		friend API listener& Listener();
		friend class system;
		listener();
		void update();

		Vector _pos, _forward, _upward;
	};

	API listener& Listener();
}