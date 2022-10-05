#pragma once
#include "vector.h"
#include "enums.h"

namespace FW {
	namespace INTERNAL{
		class reverb;
	}

	class reverb {
	public:
		API reverb& setPreset(REVERB preset);
		API REVERB preset() const;
		
		API reverb & set3D(const Vector& pos, float minDistance, float maxDistance);
		API const Vector& pos() const;
		API float minDistance() const;
		API float maxDistance() const;

		API bool isActive() const;
		API reverb& setActive(bool value);

	private:
		friend class reverbs;

		reverb(REVERB preset, int key);
		~reverb();

		REVERB _preset = R_OFF;
		Vector _position = Vector(0.f, 0.f, 0.f);
		float _minDistance = 0;
		float _maxDistance = 0;
		bool _active = true;
		int _key;

		INTERNAL::reverb* internal_reverb = nullptr;
	};
}