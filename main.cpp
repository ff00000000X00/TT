#include "Setts.h"
#include <iostream>
#include <math.h>
#include <portaudio.h>

//#define DEBUG

static int audioCallback(const void *inputBuffer, void *outputBuffer,
                         unsigned long framesPerBuffer,
                         const PaStreamCallbackTimeInfo *timeInfo,
                         PaStreamCallbackFlags statusFlags, void *userData) {
  float *input = (float *)inputBuffer;
  double volume = 0.0;
  for (unsigned int i = 0; i < framesPerBuffer; i++) {
    volume += input[i] * input[i];
  }

  volume = sqrt(volume / framesPerBuffer);

  auto setts = Setts::Get();

  if (volume > setts->treshold) {
    if (!setts->shutdowndParams.empty()) {
      std::string shutter("shutdown " + setts->shutdowndParams);
      system(shutter.c_str());
    }
  }

  return paContinue;
}

int main() {

  PaError err;
  err = Pa_Initialize();
  if (err != paNoError) {
    std::cerr << "PortAudio error: " << Pa_GetErrorText(err) << std::endl;
    return 1;
  }

  PaStream *stream;
  err = Pa_OpenDefaultStream(&stream, 1, 0, paFloat32, 48000,
                             paFramesPerBufferUnspecified, audioCallback, NULL);
  if (err != paNoError) {
    err =
        Pa_OpenDefaultStream(&stream, 1, 0, paFloat32, 44100,
                             paFramesPerBufferUnspecified, audioCallback, NULL);
    if (err != paNoError) {
      return 1;
    }
  }

  err = Pa_StartStream(stream);
  if (err != paNoError) {
    return 1;
  }

  std::cin.get();

  err = Pa_StopStream(stream);
  if (err != paNoError) {
    return 1;
  }

  err = Pa_CloseStream(stream);
  if (err != paNoError) {
    return 1;
  }

  Pa_Terminate();

  return 0;
}
