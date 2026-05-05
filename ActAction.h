#ifndef ACTACTION_H
#define ACTACTION_H

#include <string>
#include <map>

class ActAction {
private:
    std::string id;
    std::string text;
    int mercyImpact;

public:
    ActAction(const std::string& id, const std::string& text, int mercyImpact)
        : id(id), text(text), mercyImpact(mercyImpact) {}

    const std::string& getId() const { return this->id; }
    const std::string& getText() const { return this->text; }
    int getMercyImpact() const { return this->mercyImpact; }
};

inline std::map<std::string, ActAction> createActCatalog() {
    std::map<std::string, ActAction> catalog;
    catalog.emplace("JOKE",        ActAction("JOKE",        "* You tell a bad joke. They laugh anyway!", 15));
    catalog.emplace("COMPLIMENT",  ActAction("COMPLIMENT",  "* You say they're the best brawler. They blush!", 20));
    catalog.emplace("INSULT",      ActAction("INSULT",      "* You call them a noob. They rage!", -15));
    catalog.emplace("COMFORT",     ActAction("COMFORT",     "* You give them a hug. Unexpected but nice.", 25));
    catalog.emplace("PET",         ActAction("PET",         "* You pat their head. They wag... wait, what?", 20));
    catalog.emplace("OFFER_SNACK", ActAction("OFFER_SNACK", "* You share your energy drink. They chug it!", 30));
    catalog.emplace("STARE",       ActAction("STARE",       "* You stare them down. They feel judged.", -10));
    catalog.emplace("OBSERVE",     ActAction("OBSERVE",     "* You study their moves. They strike a pose.", 10));
    catalog.emplace("DANCE",       ActAction("DANCE",       "* You hit the default dance. They join in!", 15));
    catalog.emplace("REASON",      ActAction("REASON",      "* You suggest teaming. They consider it...", 20));
    return catalog;
}

#endif
