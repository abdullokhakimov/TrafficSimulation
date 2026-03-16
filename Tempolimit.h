#ifndef TEMPOLIMIT_H_
#define TEMPOLIMIT_H_
#include <limits>

enum class Tempolimit {
    Innerorts = 50,
    Landstrasse = 100,
    Autobahn = std::numeric_limits<int>::max()
};


#endif
