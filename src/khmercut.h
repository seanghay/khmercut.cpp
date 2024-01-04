#pragma once

#include <string>
#include <vector>
#include "utf8.h"
#include "crfsuite_api.hpp"

namespace khmercut
{

  struct ClusterValue
  {
    std::string value;
    std::string type;
    int length;
    utf8::utfchar32_t codepoint;
    double ns_value();
  };

  bool iskcc(const utf8::utfchar32_t &c);
  bool isns(const utf8::utfchar32_t &c);
  const char *get_type(const utf8::utfchar32_t &c);
  void set_kcc_type(ClusterValue &g);
  const std::vector<ClusterValue> graphemes(const std::string &value);
  CRFSuite::Item create_item(std::vector<ClusterValue> &kccs, const size_t &i);
  CRFSuite::ItemSequence create_seq(std::vector<ClusterValue> &kccs);
  std::vector<std::string> tokenize(CRFSuite::Tagger &tagger, const std::string &text);
}