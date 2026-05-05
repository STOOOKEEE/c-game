#ifndef BESTIARYENTRY_H
#define BESTIARYENTRY_H

#include <string>

struct BestiaryEntry {
    std::string name;
    std::string category;
    int hpMax;
    int atk;
    int def;
    bool killed;
};

#endif
