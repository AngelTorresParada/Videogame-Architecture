#include "AudioSource.h"
#include "AudioBuffer.h"
#include "../SuperMarioInvaders/lib/alc.h"
#include "../SuperMarioInvaders/lib/al.h"

AudioSource::AudioSource(AudioBuffer * _buffer) {
	buffer = _buffer;

	alGenSources(1, &source);

	pitch = 1;
	gain = 1;
	loop = false;
	posX = posY = posZ = 0;
	speedX = speedY = speedZ = 0;

	alSourcei(source, AL_BUFFER, buffer->getAlBuffer());
	setPitch(pitch);
	setGain(gain);
	setLooping(loop);
	setPosition(posX, posY, posZ);
	setVelocity(speedX, speedY, speedZ);
}


void AudioSource::setPitch(float _pitch) {
	alSourcef(source, AL_PITCH, _pitch);
}


void AudioSource::setGain(float _gain) {
	alSourcef(source, AL_GAIN, _gain);
}


void AudioSource::setLooping(bool _loop) {
	alSourcei(source, AL_LOOPING, static_cast<int>(_loop));
}


void AudioSource::setPosition(float _x, float _y, float _z) {
	alSource3f(source, AL_POSITION, _x, _y, _z);
}


void AudioSource::setVelocity(float _x, float _y, float _z) {
	alSource3f(source, AL_VELOCITY, _x, _y, _z);
}


void AudioSource::play() {
	alSourcePlay(source);
}


void AudioSource::stop() {
	alSourceStop(source);
}


void AudioSource::pause() {
	alSourcePause(source);
}


bool AudioSource::isPlaying() const {
	bool isPlaying = false;
	alGetSourcei(source, AL_SOURCE_STATE, reinterpret_cast<int *>(&isPlaying));

	return isPlaying == AL_PLAYING;
}







