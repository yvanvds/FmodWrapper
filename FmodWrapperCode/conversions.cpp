#include "conversions.h"

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

		FMOD_REVERB_PROPERTIES ToFMOD(FW::REVERB reverb) {
			switch (reverb) {
			case R_OFF: return FMOD_PRESET_OFF; 
			case R_GENERIC: return FMOD_PRESET_GENERIC; 
			case R_PADDEDCELL: return FMOD_PRESET_PADDEDCELL;
			case R_ROOM: return FMOD_PRESET_ROOM; 
			case R_BATHROOM: return FMOD_PRESET_BATHROOM; 
			case R_LIVINGROOM: return FMOD_PRESET_LIVINGROOM; 
			case R_STONEROOM: return FMOD_PRESET_STONEROOM;
			case R_AUDITORIUM: return FMOD_PRESET_AUDITORIUM; 
			case R_CONCERTHALL: return FMOD_PRESET_CONCERTHALL; 
			case R_CAVE: return FMOD_PRESET_CAVE; 
			case R_ARENA: return FMOD_PRESET_ARENA; 
			case R_HANGAR: return FMOD_PRESET_HANGAR; 
			case R_CARPETTEDHALLWAY: return FMOD_PRESET_CARPETTEDHALLWAY;
			case R_HALLWAY: return FMOD_PRESET_HALLWAY; 
			case R_STONECORRIDOR: return FMOD_PRESET_STONECORRIDOR;
			case R_ALLEY: return FMOD_PRESET_ALLEY;
			case R_FOREST: return FMOD_PRESET_FOREST;
			case R_CITY: return FMOD_PRESET_CITY;
			case R_MOUNTAINS: return FMOD_PRESET_MOUNTAINS;
			case R_QUARRY: return FMOD_PRESET_QUARRY; 
			case R_PLAIN: return FMOD_PRESET_PLAIN;
			case R_PARKINGLOT: return FMOD_PRESET_PARKINGLOT;
			case R_SEWERPIPE: return FMOD_PRESET_SEWERPIPE;
			case R_UNDERWATER: return FMOD_PRESET_UNDERWATER;
			default: return FMOD_PRESET_OFF;
			}
		}
	}
}