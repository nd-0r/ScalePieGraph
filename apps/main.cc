#include <core/synthesizer.h>
#include <core/scale.h>
#include <unistd.h>
#include <iostream>
#include <jsoncpp/json.h>
#include <fstream>

void showcase_synthesizer() {
  const size_t kSecond = 1000000;
  const float kBaseFrequency = 440.0;

  scalepiegraph::Synthesizer synthesizer;
  scalepiegraph::Scale scale(12);

  synthesizer.Start(kBaseFrequency);
  synthesizer.SetFilter(kBaseFrequency);

  synthesizer.SetWaveform(ci::audio::WaveformType::SAWTOOTH);
  usleep(kSecond);
  synthesizer.SetFrequency(scale.CalculateNoteFrequency(kBaseFrequency, 2));
  synthesizer.SetWaveform(ci::audio::WaveformType::SQUARE);
  usleep(kSecond);
  synthesizer.SetFrequency(scale.CalculateNoteFrequency(kBaseFrequency, 4));
  synthesizer.SetWaveform(ci::audio::WaveformType::TRIANGLE);
  usleep(kSecond);

  synthesizer.Stop();
}

void showcase_json_library(std::ifstream& json_file) {
  Json::Value root;
  json_file >> root;

  std::cout << root.get("encoding", "UTF-8" ).asString() << std::endl;

  const Json::Value plugins = root["plug-ins"];

  for (const Json::Value& plugin : plugins) {
    std::cout << plugin.asString() << std::endl;
  }
}

int main(int argc, char* argv[]) {
  std::ifstream test_json_file;

  try {
    test_json_file.open(argv[1]);
  } catch (std::ios_base::failure&) {
    std::cerr << "Cannot open provided files";
    return 1;
  }

  showcase_json_library(test_json_file);
  showcase_synthesizer();

  return 0;
}
