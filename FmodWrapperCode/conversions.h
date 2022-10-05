#pragma once
#include "vector.h"
#include "enums.h"
#include "fmod.hpp"

namespace FW {
	namespace INTERNAL {
		FMOD_VECTOR ToFMOD(FW::Vector vector);
		FW::Vector ToFW(FMOD_VECTOR vector);

		FMOD_REVERB_PROPERTIES ToFMOD(FW::REVERB reverb);
	}
}


