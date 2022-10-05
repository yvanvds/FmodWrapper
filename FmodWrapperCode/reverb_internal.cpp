#include "reverb_internal.h"
#include "conversions.h"
#include "error.h"
#include "system_internal.h"

namespace FW {
	namespace INTERNAL {
		reverb::reverb(REVERB preset) {
			result = System().get().createReverb3D(&fmod_reverb);
			ERRCHECK(result);
			setProperties(preset);
		}

		reverb::~reverb() {
			if (fmod_reverb != nullptr) {
				result = fmod_reverb->release();
				ERRCHECK(result);
				fmod_reverb = nullptr;
			}
		}

		void reverb::setProperties(REVERB prop) {
			auto preset = ToFMOD(prop);
			result = fmod_reverb->setProperties(&preset);
			ERRCHECK(result);
		}

		void reverb::set3DAttributes(const Vector& pos, float min, float max) {
			FMOD_VECTOR position = ToFMOD(pos);
			result = fmod_reverb->set3DAttributes(&position, min, max);
			ERRCHECK(result);
		}

		bool reverb::isValid() const {
			return fmod_reverb != nullptr;
		}

		void reverb::setActive(bool value) {
			result = fmod_reverb->setActive(value);
			ERRCHECK(result);
		}
	}
}