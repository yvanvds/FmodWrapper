#pragma once
#include "fmod.hpp"
#include "enums.h"
#include "vector.h"

namespace FW {
	namespace INTERNAL {

		class reverb {
		public:
			reverb(REVERB preset);
			~reverb();

			void setProperties(REVERB preset);
			void set3DAttributes(const Vector & pos, float min, float max);
			void setActive(bool value);

			bool isValid() const;

		private:
			FMOD::Reverb3D* fmod_reverb = nullptr;
			FMOD_RESULT result;
		};

	}
}