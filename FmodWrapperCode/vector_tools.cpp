#include "vector_tools.h"

namespace FW {
	namespace INTERNAL {
		FMOD_VECTOR ToFMOD(FW::Vector vector) {
			FMOD_VECTOR result;
			result.x = vector.x;
			result.y = vector.y;
			result.z = vector.z;
			return result;
		}

		FW::Vector ToFW(FMOD_VECTOR vector) {
			return FW::Vector(vector.x, vector.y, vector.z);
		}
	}
}