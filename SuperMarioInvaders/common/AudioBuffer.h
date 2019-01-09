#pragma once
#include <cstdint>

class AudioBuffer {
	private:
		AudioBuffer();

		uint32_t buffer;

		~AudioBuffer();

	public:
		static AudioBuffer*	load(const char*);
		uint32_t getAlBuffer() const;
};