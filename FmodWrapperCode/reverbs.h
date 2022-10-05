#pragma once
#include <unordered_map>
#include "defines.h"
#include "reverb.h"

namespace FW {
	class reverbs {
	public:
		API reverb* create(REVERB preset);
		API void release(reverb* reverb);
		API void releaseAll();

	private:
		friend API reverbs& Reverbs();
		reverbs();

		std::unordered_map<int, reverb*> _map;
		int _counter;
	};

	API reverbs& Reverbs();
}