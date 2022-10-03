#include "sound_internal.h"
#include "system_internal.h"
#include <string>
#include "error.h"
#include "vector_tools.h"
#include <fwtime.h>
#include <listener_internal.h>
#include <log.h>

namespace FW {
	namespace INTERNAL {

		sound::sound(std::string fileName, bool loop, float volume, bool streaming) : fmod_sound(nullptr), _volume(volume), loop(loop) {
			result = System().get().createSound(fileName.c_str(), FMOD_3D, 0, &fmod_sound);
			ERRCHECK(result);
			if (fmod_sound != nullptr) {
				result = fmod_sound->setMode(loop ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF);
				ERRCHECK(result);
				result = fmod_sound->set3DMinMaxDistance(0.5f * System().distanceFactor(), 5000.f * System().distanceFactor());
				ERRCHECK(result);

				int priority;
				result = fmod_sound->getDefaults(&_frequency, &priority);
				ERRCHECK(result);
			}
		}

		sound::~sound() {
			if (fmod_sound != nullptr) {
				result = fmod_sound->release();
				ERRCHECK(result);
			}
		}

		bool sound::isValid() const {
			return fmod_sound != nullptr;
		}


		void sound::looping(bool value)
		{
			if (fmod_sound != nullptr) {
				fmod_sound->setMode(value ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF);
				loop = value;
			}
		}

		bool sound::looping() const
		{
			return loop;
		}

		void sound::play()
		{
			switch (intent) {
			case SI_PLAY: return;
			case SI_PAUSE:
				result = fmod_channel->setVolume(_volume);
				ERRCHECK(result);
				break;
			case SI_STOP:
				result = fmod_channel->setPosition(0, FMOD_TIMEUNIT_MS);
				ERRCHECK(result);
				result = fmod_channel->setVolume(_volume);
				ERRCHECK(result);
				break;
			case SI_NONE:
				result = System().get().playSound(fmod_sound, 0, false, &fmod_channel);
				ERRCHECK(result);
				// sound is really starting, so set all channel properties
				volume(_volume, _volumeRamp);
				pos(_newPos);
				doppler(_doppler);
				speed(_speed);
			}
			intent = SI_PLAY;
		}

		bool sound::isPlaying() const
		{
			return intent == SI_PLAY;
			
		}

		void sound::pause()
		{
			if (fmod_channel == nullptr) {
				FW::Log().sendWarning("Cannot pause a sound that has not started yet.");
				return;
			}
			result = fmod_channel->setVolume(0.f);
			ERRCHECK(result);
			intent = SI_PAUSE;
		}

		bool sound::isPaused() const
		{
			return intent == SI_PAUSE;
		}

		void sound::stop()
		{
			if (fmod_channel == nullptr) {
				FW::Log().sendWarning("Cannot stop a sound that has not started yet.");
				return;
			}
			result = fmod_channel->setVolume(0.f);
			ERRCHECK(result);
			intent = SI_STOP;
		}

		bool sound::isStopped() const
		{
			return intent == SI_STOP;
		}

		void sound::toggle()
		{
			if (isPlaying()) {
				pause();
			}
			else {
				play();
			}
		}

		void sound::restart()
		{
			if (fmod_channel == nullptr) {
				FW::Log().sendWarning("Cannot restart a sound before it's being played.");
				return;
			}
			result = fmod_channel->setPosition(0, FMOD_TIMEUNIT_MS);
			ERRCHECK(result);
		}

		unsigned int sound::length() const {
			unsigned int value;
			FMOD_RESULT result = fmod_sound->getLength(&value, FMOD_TIMEUNIT_PCM);
			ERRCHECK(result);
			return value;
		}

		unsigned int sound::time() const {
			if (fmod_channel == nullptr) return 0;
			unsigned int value;
			FMOD_RESULT result = fmod_channel->getPosition(&value, FMOD_TIMEUNIT_PCM);
			ERRCHECK(result);
			return value;
		}

		void sound::time(unsigned int value) {
			if (fmod_channel == nullptr) {
				FW::Log().sendWarning("Time must be set after a sound started playing");
				return;
			}
			result = fmod_channel->setPosition(value, FMOD_TIMEUNIT_PCM);
			ERRCHECK(result);
		}

		void sound::pos(const Vector& pos) {
			if (fmod_channel != nullptr) {
				_newPos = pos * System().distanceFactor();
				if (_isRelative) {
					_newPos += Listener().position();
				}
				_velocity = (_newPos - _lastPos) * (1.f / Time().delta());
				_lastPos = _newPos;
				auto position = ToFMOD(pos);
				auto velocity = ToFMOD(_velocity);
				result = fmod_channel->set3DAttributes(&position, &velocity);
				ERRCHECK(result);
			}
			else {
				_newPos = _lastPos = pos;
				_velocity.zero();
			}
		}

		const Vector& sound::pos() const {
			return _lastPos;
		}

		void sound::speed(float value) {
			_speed = value;

			if (fmod_channel != nullptr) {
				result = fmod_channel->setFrequency(_frequency * _speed);
				ERRCHECK(result);
			}
		}

		float sound::speed() const {
			return _speed;
		}

		void sound::size(float value) {
			_size = value;
			float min = value >= 1 ? 0.5f : value * 0.5f;
			result = fmod_sound->set3DMinMaxDistance(min * System().distanceFactor(), value * System().distanceFactor());
			ERRCHECK(result);
		}

		float sound::size() const {
			return _size;
		}

		void sound::volume(float value, unsigned int time) {
			_volume = value;
			_volumeRamp = time;

			if (fmod_channel == nullptr) {
				return;
			}
			else if (time == 0) {
				result = fmod_channel->setVolume(value);
				ERRCHECK(result);
			}
			else {
				int rate;
				unsigned long long dspclock;

				result = System().get().getSoftwareFormat(&rate, 0, 0);
				ERRCHECK(result);
				result = fmod_channel->getDSPClock(0, &dspclock);
				ERRCHECK(result);

				result = fmod_channel->addFadePoint(dspclock + (rate * time), value);
				ERRCHECK(result);
			}
		}

		float sound::volume() const {
			return _volume;
		}

		void sound::relative(bool value) {
			_isRelative = value;
		}

		bool sound::relative() const {
			return _isRelative;
		}

		void sound::doppler(float value) {
			_doppler = value;
			if (fmod_channel != nullptr) {
				result = fmod_channel->set3DDopplerLevel(value);
				ERRCHECK(result);
			}
		}

		float sound::doppler() const {
			return _doppler;
		}
	}
}
