#ifndef ACTACTION_H
#define ACTACTION_H

#include <string>
#include <map>

struct ActAction {
    std::string id;
    std::string text;
    int mercyImpact;
};

inline std::map<std::string, ActAction> createActCatalog() {
    std::map<std::string, ActAction> catalog;
    catalog["JOKE"]        = {"JOKE",        "* You tell a bad joke. They laugh anyway!", 15};
    catalog["COMPLIMENT"]  = {"COMPLIMENT",  "* You say they're the best brawler. They blush!", 20};
    catalog["INSULT"]      = {"INSULT",      "* You call them a noob. They rage!", -15};
    catalog["COMFORT"]     = {"COMFORT",     "* You give them a hug. Unexpected but nice.", 25};
    catalog["PET"]         = {"PET",         "* You pat their head. They wag... wait, what?", 20};
    catalog["OFFER_SNACK"] = {"OFFER_SNACK", "* You share your energy drink. They chug it!", 30};
    catalog["STARE"]       = {"STARE",       "* You stare them down. They feel judged.", -10};
    catalog["OBSERVE"]     = {"OBSERVE",     "* You study their moves. They strike a pose.", 10};
    catalog["DANCE"]       = {"DANCE",       "* You hit the default dance. They join in!", 15};
    catalog["REASON"]      = {"REASON",      "* You suggest teaming. They consider it...", 20};
    return catalog;
}

#endif
