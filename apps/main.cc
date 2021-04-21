#include <core/synthesizer.h>
#include <unistd.h>

int main() {
  scalepiegraph::Synthesizer synthesizer;
  synthesizer.Play(440.0);
  synthesizer.SetFilter(440.0);

  const size_t kSecond = 1000000;
  usleep(1 * kSecond);

  synthesizer.SetWaveform(ci::audio::WaveformType::SAWTOOTH);
  usleep(kSecond);
  synthesizer.SetWaveform(ci::audio::WaveformType::SQUARE);
  usleep(kSecond);
  synthesizer.SetWaveform(ci::audio::WaveformType::TRIANGLE);
  usleep(kSecond);

  synthesizer.Stop();
  return 0;
}
