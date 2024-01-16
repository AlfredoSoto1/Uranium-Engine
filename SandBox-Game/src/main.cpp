
//#include <iostream>
//#include <AL/al.h>
//#include <AL/alc.h>
//
//using namespace std;
//
//int main() {
//    // Initialize OpenAL
//    ALCdevice* device = alcOpenDevice(NULL);
//    ALCcontext* context = alcCreateContext(device, NULL);
//    alcMakeContextCurrent(context);
//
//    // Load sound file
//    ALuint buffer;
//    alGenBuffers(1, &buffer);
//    ALenum format;
//    ALsizei size;
//    ALvoid* data;
//    ALsizei freq;
//    ALboolean loop = AL_FALSE;
//    alutLoadWAVFile("sound.wav", &format, &data, &size, &freq, &loop);
//    alBufferData(buffer, format, data, size, freq);
//    alutUnloadWAV(format, data, size, freq);
//
//    // Set up source
//    ALuint source;
//    alGenSources(1, &source);
//    alSourcei(source, AL_BUFFER, buffer);
//    alSourcef(source, AL_GAIN, 1.0f);
//
//    // Play sound
//    alSourcePlay(source);
//
//    // Wait for sound to finish playing
//    ALint state;
//    do {
//        alGetSourcei(source, AL_SOURCE_STATE, &state);
//    } while (state == AL_PLAYING);
//
//    // Clean up
//    alDeleteSources(1, &source);
//    alDeleteBuffers(1, &buffer);
//    alcDestroyContext(context);
//    alcCloseDevice(device);
//
//    return 0;
//}

#include "Core/Application.h"

using namespace Uranium::Core;

class GameApplication : public Application {
public:

	GameApplication() noexcept:
		Application()
	{
		// Initialize any member
	}

	~GameApplication() {
		// Delete any member
	}

	/*std::unique_ptr<Window> createWindow() override {
		return nullptr;
	}*/
};

std::unique_ptr<Application> createApplication() {
	/*
	* Create a unique application
	*/
	return std::make_unique<GameApplication>();
}
