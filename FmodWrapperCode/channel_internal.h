#pragma once
#include <string>
#include "fmod.hpp"

namespace FW {
	namespace INTERNAL {

		class sound;

		class channel {
		public:
			channel();
			channel(const std::string & name, channel* parent);
			~channel();

			void canGoVirtual(bool value);
			void volume(float value);
			void moveTo(channel& parent);
			void reverb(float wet);

			bool isValid() const;

		private:
			friend class sound;
			bool _isMaster;
			bool _canGoVirtual;
			FMOD::ChannelGroup* fmod_channelgroup = nullptr;
			FMOD_RESULT result;
		};
	}
}