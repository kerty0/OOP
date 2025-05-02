#include <iostream>
#include <string>

class Character {
   private:
    std::string name;
    int health;
    int attack;
    int defense;

   public:
    Character(const std::string& n, int h, int a, int d)
        : name(n), health(h), attack(a), defense(d) {}

    // Перегрузка оператора ==
    bool operator==(const Character& other) const {
        return name == other.name && health == other.health;
    }

    // Перегрузка оператора <<
    friend std::ostream& operator<<(std::ostream& os, const Character& character) {
        os << "Character: " << character.name << ", HP: " << character.health
           << ", Attack: " << character.attack << ", Defense: " << character.defense;
        return os;
    }
};

class Weapon {
   private:
    std::string name;
    int attack;
    int weight;

   public:
    Weapon(const std::string& n, int a, int w)
        : name(n), attack(a), weight(w) {}

    void displayInfo() const {
        std::cout << "Weapon name: " << name << ", Attack: " << attack << ", Weight: " << weight << std::endl;
    }

    Weapon operator+(const Weapon& other) {
        return Weapon(name, attack + other.attack, weight);
    }

    bool operator>(const Weapon& other) const {
        return attack > other.attack;
    }
    bool operator<(const Weapon& other) const {
        return attack < other.attack;
    }
    bool operator==(const Weapon& other) const {
        return attack == other.attack;
    }
};

int main() {
    Character hero1("Hero", 100, 20, 10);
    Character hero2("Hero", 100, 20, 10);
    Character hero3("Warrior", 150, 25, 15);

    if (hero1 == hero2) {
        std::cout << "Hero1 and Hero2 are the same!\n";
    }
    if (!(hero1 == hero3)) {
        std::cout << "Hero1 and Hero3 are different!\n";
    }

    std::cout << hero1 << std::endl;  // Вывод информации о персонаже

    Weapon sword("Sword", 100, 10);
    Weapon dagger("Dagger", 10, 1);

    if (sword > dagger) {
        std::cout << "Sword more powerfull that dagger" << std::endl;
    }

    Weapon new_sword = sword + dagger;
    new_sword.displayInfo();

    if (sword < new_sword) {
        std::cout << "New sword more powerfull that old sword" << std::endl;
    }

    return 0;
}
