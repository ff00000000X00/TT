#include "Setts.h"
#include <fstream>
#include <iostream>

namespace setts {
const char separator = ':';
const char lineEnd = ';';
const int lineLimit = 100;
} // namespace setts
#define SEP setts::separator
#define END setts::lineEnd
#define LLM setts::lineLimit

Setts *Setts::m_setts = nullptr;

Setts::Setts() {}

Setts *Setts::Get() {
  if (m_setts == nullptr) {
    m_setts = new Setts;
  }
  return m_setts;
}

void Setts::setSetting(const std::string &str) {
  int pos = 0;
  auto setts = Get();
  auto paramName = getParamName(str, pos);
  if (paramName == "ThresholdValue") {
    setts->treshold = getParamsDoubleValue(str, pos);
  } else if (paramName == "ShutdownParams") {
    setts->shutdowndParams = getParamsStringValue(str, pos);
  }
}

bool Setts::readSetts(const std::string &str) {
  std::ifstream conf(str, std::ios::in);
  if (conf) {
    auto setts = Setts::Get();
    conf.seekg(std::ios::beg);
    for (std::string cache; std::getline(conf, cache);) {
      if (cache.empty() || *cache.data() == '#') {
        continue;
      }
      setts->setSetting(cache);
    }
    return true;
  }
  return false;
}

std::string Setts::getParamName(const std::string &str, int &pos) {

  auto c_str = str.data();
  int substringLengh = 0;
  while (*c_str != SEP || substringLengh == LLM) {
    ++substringLengh;
    ++c_str;
  }
  pos = substringLengh; // pos - позиция разделителя
  return str.substr(0, substringLengh);
}

double Setts::getParamsDoubleValue(const std::string &str, int pos) {
  ++pos;
  auto c_str = str.data() + pos;
  int substringLengh = 0;
  while (*c_str != END || substringLengh == LLM) {
    if (*c_str == ' ') {
      ++pos;
      ++c_str;
      continue;
    }
    ++c_str;
    ++substringLengh;
  }
  return std::stod(str.substr(pos, substringLengh));
}

std::string Setts::getParamsStringValue(const std::string &str, int pos) {
  ++pos;
  auto c_str = str.data() + pos;
  int substringLengh = 0;
  while (*c_str != END || substringLengh == LLM) {
    ++c_str;
    ++substringLengh;
  }
  return str.substr(pos, substringLengh);
}
