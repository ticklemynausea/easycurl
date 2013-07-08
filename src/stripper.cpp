// Copyright 2013 Hugo Peixoto (hugopeixoto.net)
#include "stripper.h"

std::string stripWhitespace (const std::string& str)
{
  size_t p_ld = str.find_first_not_of(" \t\n\r");
  size_t p_tl = str.find_last_not_of(" \t\n\r");
  std::string result = str.substr(p_ld, p_tl-p_ld+1);

  size_t j = 1;
  for (size_t i = 1; i < result.size(); ++i) {
    if (!isspace(result[i]) || !isspace(result[j - 1])) {
      result[j++] = result[i];
    }
  }

  result.resize(j);
  return result;
}

