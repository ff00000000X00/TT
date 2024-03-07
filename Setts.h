#ifndef SETTS_H
#define SETTS_H

#include <string>

class Setts {
public:
  static Setts *Get();
  double treshold = 0.5;
  std::string shutdowndParams = {};
  void setSetting(const std::string &str);
  static bool readSetts(const std::string &str);

protected:
  Setts();
  Setts(Setts &other) = delete;
  static Setts *m_setts;
  std::string getParamName(const std::string &str, int &pos);
  double getParamsDoubleValue(const std::string &str, int pos);
  std::string getParamsStringValue(const std::string &str, int pos);
};

#endif // SETTS_H
