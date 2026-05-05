#ifndef BESTIARYENTRY_H
#define BESTIARYENTRY_H

#include <string>

class BestiaryEntry {
private:
    std::string name;
    std::string category;
    int hpMax;
    int atk;
    int def;
    bool killed;

public:
    BestiaryEntry(const std::string& name, const std::string& category,
                  int hpMax, int atk, int def, bool killed)
        : name(name), category(category), hpMax(hpMax), atk(atk), def(def), killed(killed) {}

    const std::string& getName() const { return this->name; }
    const std::string& getCategory() const { return this->category; }
    int getHpMax() const { return this->hpMax; }
    int getAtk() const { return this->atk; }
    int getDef() const { return this->def; }
    bool wasKilled() const { return this->killed; }
};

#endif
