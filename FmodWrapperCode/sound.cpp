#include "sound.h"
#include "sound_internal.h"
#include <channel.h>

namespace FW {
	 
	sound::sound(const std::string & filename, bool loop, float volume, bool streaming, int key, channel * parent) : key(key) {
		internal_sound = new INTERNAL::sound(filename, loop, volume, streaming, parent != nullptr ? parent->internal_channel : nullptr);
	}

	sound::~sound() {
		if (internal_sound != nullptr) {
			delete internal_sound;
		}
	}

	sound& sound::looping(bool value) {
		internal_sound->looping(value);
		return *this;
	}

	bool sound::looping() const {
		return internal_sound->looping();
	}

	sound& sound::play() {
		internal_sound->play();
		return *this;
	}

	bool sound::isPlaying() {
		return internal_sound->isPlaying();
	}

	sound& sound::pause() {
		internal_sound->pause();
		return *this;
	}

	bool sound::isPaused() {
		return internal_sound->isPaused();
	}

	sound& sound::stop() {
		internal_sound->stop();
		return *this;
	}

	bool sound::isStopped() {
		return internal_sound->isStopped();
	}

	sound& sound::toggle() {
		internal_sound->toggle();
		return *this;
	}

	sound& sound::restart() {
		internal_sound->restart();
		return *this;
	}

	unsigned int sound::length() const {
		return internal_sound->length();
	}

	unsigned int sound::time() const {
		return internal_sound->time();
	}

	sound& sound::time(unsigned int value) {
		internal_sound->time(value);
		return *this;
	}

	bool sound::isValid() const {
		return internal_sound->isValid();
	}

	sound& sound::pos(const Vector& pos) {
		_pos = pos;
		return *this;
	}

	const Vector& sound::pos() const {
		return internal_sound->pos();
	}

	void sound::update() {
		internal_sound->pos(_pos);
	}

	sound& sound::speed(float value) {
		internal_sound->speed(value);
		return *this;
	}

	float sound::speed() const {
		return internal_sound->speed();
	}

	sound& sound::size(float value) {
		internal_sound->size(value);
		return *this;
	}

	float sound::size() const {
		return internal_sound->size();
	}

	sound& sound::volume(float value, unsigned int time) {
		if (value < 0) value = 0;
		internal_sound->volume(value, time);
		return *this;
	}

	float sound::volume() const {
		return internal_sound->volume();
	}

	sound& sound::relative(bool value) {
		internal_sound->relative(value);
		return *this;
	}

	bool sound::relative() const {
		return internal_sound->relative();
	}

	sound& sound::doppler(float value) {
		internal_sound->doppler(value);
		return *this;
	}

	float sound::doppler() const {
		return internal_sound->doppler();
	}

}

