#include <iostream>
#include <string>

class Character {
   private:
    std::string name;
    int health;
    int attack;
    int defense;

   public:
    // Конструктор
    Character(const std::string& n, int h, int a, int d)
        : name(n), health(h), attack(a), defense(d) {
        std::cout << "Character " << name << " created!\n";
    }

    // Деструктор
    ~Character() {
        std::cout << "Character " << name << " destroyed!\n";
    }

    void displayInfo() const {
        std::cout << "Name: " << name << ", HP: " << health
                  << ", Attack: " << attack << ", Defense: " << defense << std::endl;
    }
};

class Monster {
   private:
    std::string name;
    int health;
    int attack;
    int defense;

   public:
    // Конструктор
    Monster(const std::string& n, int h, int a, int d)
        : name(n), health(h), attack(a), defense(d) {
        std::cout << "Monster " << name << " created!\n";
    }

    // Деструктор
    ~Monster() {
        std::cout << "Monster " << name << " destroyed!\n";
    }

    void displayInfo() const {
        std::cout << "Name: " << name << ", HP: " << health
                  << ", Attack: " << attack << ", Defense: " << defense << std::endl;
    }
};

class Weapon {
   private:
    std::string name;
    int attack;
    int weight;

   public:
    // Конструктор
    Weapon(const std::string& n, int a, int w)
        : name(n), attack(a), weight(w) {
        std::cout << "Weapon " << name << " created!\n";
    }

    // Деструктор
    ~Weapon() {
        std::cout << "Weapon " << name << " destroyed!\n";
    }

    void displayInfo() const {
        std::cout << "Weapon name: " << name << ", Attack: " << attack << ", Weight: " << weight << std::endl;
    }
};

int main() {
    Character hero("Hero", 100, 20, 10);
    Weapon sword("Great sword", 100, 50);
    Monster goblin("Goblin", 50, 15, 5);
    Weapon dagger("Small dagger", 1, 1);
    hero.displayInfo();
    sword.displayInfo();
    goblin.displayInfo();
    dagger.displayInfo();
    return 0;
}