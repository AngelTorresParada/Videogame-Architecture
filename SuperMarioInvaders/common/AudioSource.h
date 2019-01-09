#pragma once
#include <cstdint>
class AudioBuffer;

class AudioSource {
	AudioBuffer * buffer;
	uint32_t source;
	float pitch;
	float gain;
	bool loop;
	float posX; float posY; float posZ;
	float speedX; float speedY; float speedZ;

	public:
		AudioSource(AudioBuffer*);
		void setPitch(float);
		void setGain(float);
		void setLooping(bool);
		void setPosition(float, float, float);
		void setVelocity(float, float, float);
		void play();
		void stop();
		void pause();
		bool isPlaying() const;

};