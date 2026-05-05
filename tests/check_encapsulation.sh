#!/bin/sh
set -eu

repo_root="$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)"
tmp_dir="$(mktemp -d)"
trap 'rm -rf "$tmp_dir"' EXIT
failures=0

expect_compile_failure() {
    source_file="$1"
    object_file="$tmp_dir/$(basename "$source_file" .cpp).o"
    error_file="$tmp_dir/$(basename "$source_file" .cpp).err"
    message="$2"

    if g++ -std=c++17 -I "$repo_root" -c "$source_file" -o "$object_file" 2> "$error_file"; then
        echo "FAIL: $message"
        failures=1
    fi
}

cat > "$tmp_dir/entity_probe.cpp" <<'CPP'
#include "Entity.h"

class EntityProbe : public Entity {
public:
    EntityProbe() : Entity("probe", 1, 1, 1) {}
    int leakHp() const { return hp; }
    void displayStats() const override {}
};

int main() {
    EntityProbe probe;
    return probe.leakHp();
}
CPP

expect_compile_failure "$tmp_dir/entity_probe.cpp" \
    "Entity internals are accessible from a derived class; expected private attributes."

cat > "$tmp_dir/monster_probe.cpp" <<'CPP'
#include "Monster.h"

class MonsterProbe : public Monster {
public:
    MonsterProbe()
        : Monster("probe", 1, 1, 1, MonsterCategory::NORMAL, 100, {}) {}

    int getMaxActs() const override { return 0; }
    Monster* clone() const override { return nullptr; }

    int leakMercy() const {
        return mercy + mercyGoal + static_cast<int>(actIds.size()) + killed + spared;
    }
};

int main() {
    MonsterProbe probe;
    return probe.leakMercy();
}
CPP

expect_compile_failure "$tmp_dir/monster_probe.cpp" \
    "Monster internals are accessible from a derived class; expected private attributes."

cat > "$tmp_dir/act_action_probe.cpp" <<'CPP'
#include "ActAction.h"

int main() {
    ActAction action{"TEST", "text", 1};
    return action.mercyImpact;
}
CPP

expect_compile_failure "$tmp_dir/act_action_probe.cpp" \
    "ActAction internals are public; expected private attributes with getters."

cat > "$tmp_dir/bestiary_entry_probe.cpp" <<'CPP'
#include "BestiaryEntry.h"

int main() {
    BestiaryEntry entry{"name", "NORMAL", 10, 2, 1, false};
    return entry.hpMax;
}
CPP

expect_compile_failure "$tmp_dir/bestiary_entry_probe.cpp" \
    "BestiaryEntry internals are public; expected private attributes with getters."

if [ "$failures" -ne 0 ]; then
    exit 1
fi

echo "OK: checked classes expose behavior through methods, not public/protected attributes."
