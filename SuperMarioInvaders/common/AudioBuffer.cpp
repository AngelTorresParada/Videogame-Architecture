#include "AudioBuffer.h"
#include "../SuperMarioInvaders/lib/alc.h"
#include "../SuperMarioInvaders/lib/al.h"
#include <cstdio>
#include <vector>

AudioBuffer::AudioBuffer() {
}


AudioBuffer::~AudioBuffer()
{
}

AudioBuffer * AudioBuffer::load(const char * _filename) {
	AudioBuffer *aBuffer = new AudioBuffer();
	FILE *f = fopen(_filename, "r");

	if (!f) return nullptr;

	fseek(f, 0, SEEK_END);
	const size_t size = ftell(f);
	fseek(f, 0, SEEK_SET);

	uint8_t *buf = new uint8_t[size];

	fread(buf, 1, size, f);
	fclose(f);

	bool verified = false;
	uint8_t counter = 0;

	//comprobar CHUNK ID
	if (buf[counter++] != 'R' || buf[counter++] != 'I' || buf[counter++] != 'F' || buf[counter++] != 'F')
		return nullptr;

	counter = 4;
	//no comprobar RIFFCHUNKSIZE
	counter += 4;

	//comprobar FORMAT
	if (buf[counter] != 'W' || buf[counter+1] != 'A' || buf[counter+2] != 'V' || buf[counter+3] != 'E')
		return nullptr;

	counter += 4;
	//comprobar SUBCHUNK ID
	if (buf[counter] != 'f' || buf[counter + 1] != 'm' || buf[counter + 2] != 't' || buf[counter + 3] != ' ')
		return nullptr;

	counter += 4;
	//comprobar FMTCHUNKSIZE
	unsigned char jumpBytes = 0;
	unsigned int fmtChunkSize = *(reinterpret_cast<unsigned int *>(&buf[counter]));
	jumpBytes = fmtChunkSize - 16;

	counter += 4;
	//comprobar AUDIOFORMAT
	uint16_t audioFormat = *(reinterpret_cast<uint16_t *>(&buf[counter]));
	if (audioFormat != 1) 
		return nullptr;

	counter += 2;
	//comprobar CHANNELS
	uint16_t channels = *(reinterpret_cast<uint16_t *>(&buf[counter]));

	counter += 2;
	//comprobar SAMPLERATE
	uint32_t  sampleRate = *(reinterpret_cast<uint32_t *>(&buf[counter]));

	counter += 4;
	//comprobar BYTERATE
	uint32_t  byteRate = *(reinterpret_cast<uint32_t *>(&buf[counter]));

	counter += 4;
	//comprobar BLOCKALIGN
	uint16_t blockAlign = *(reinterpret_cast<uint16_t *>(&buf[counter]));

	counter += 2;
	//comprobar BITSPERSAMPLE
	uint16_t bitsPerSample = *(reinterpret_cast<uint16_t *>(&buf[counter]));

	counter += 2;
	counter += jumpBytes;
	//comprobar "DATA"
	bool isData = false;
	while (!isData) {
		printf("%c%c%c%c", buf[counter], buf[counter + 1], buf[counter + 2], buf[counter + 3]);
		if (buf[counter] == 'd' && buf[counter + 1] == 'a' && buf[counter + 2] == 't' && buf[counter + 3] == 'a')
			isData = true;
		counter += 4;
	}

	//comprobar DATASIZE
	uint32_t dataSize = *(reinterpret_cast<uint32_t *>(&buf[counter]));
	uint8_t *data = new uint8_t[dataSize];
	counter += 4;

	for (int i = 0; i < dataSize; ++i) {
		data[i] = buf[i + counter];
	}


	//recibir format
	ALenum format;
	if (bitsPerSample == 8) {
		if (channels == 1) format = AL_FORMAT_MONO8;
		else format = AL_FORMAT_STEREO8;
	}
	else if (bitsPerSample == 16) {
		if (channels == 1) format = AL_FORMAT_MONO16;
		else format = AL_FORMAT_STEREO16;
	}

	alGenBuffers(1, &aBuffer->buffer);
	alBufferData(aBuffer->buffer, format, data, dataSize, sampleRate);

	return aBuffer;
}


uint32_t AudioBuffer::getAlBuffer() const { return buffer; }
