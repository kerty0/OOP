#include <iostream>
#include <string>

class Entity {
   protected:
   public:
    std::string name;
    int health;
    int defense;
    int damage;

    Entity(const std::string& n, int h, int a, int d)
        : name(n), health(h), damage(a), defense(d) {}

    // Виртуальный метод для атаки
    virtual void attack(Entity& target) {
        int damage = damage - target.defense;
        if (damage > 0) {
            target.health -= damage;
            std::cout << name << " attacks " << target.name << " for " << damage << " damage!\n";
        } else {
            std::cout << name << " attacks " << target.name << ", but it has no effect!\n";
        }
    }

    // Виртуальный метод для вывода информации
    virtual void displayInfo() const {
        std::cout << "Name: " << name << ", HP: " << health
                  << ", Attack: " << damage << ", Defense: " << defense << std::endl;
    }

    // Виртуальный деструктор
    virtual ~Entity() {}
};

class Character : public Entity {
   public:
    Character(const std::string& n, int h, int a, int d)
        : Entity(n, h, a, d) {}

    // Переопределение метода attack
    void attack(Entity& target) override {
        int target_damage = damage - target.defense;
        if (target_damage > 0) {
            // Шанс на критический удар (20%)
            if (rand() % 100 < 20) {
                target_damage *= 2;
                std::cout << "Critical hit! ";
            }
            target.health -= target_damage;
            std::cout << name << " attacks " << target.name << " for " << target_damage << " damage!\n";
        } else {
            std::cout << name << " attacks " << target.name << ", but it has no effect!\n";
        }
    }

    // Переопределение метода displayInfo
    void displayInfo() const override {
        std::cout << "Character: " << name << ", HP: " << health
                  << ", Attack: " << damage << ", Defense: " << defense << std::endl;
    }
};

class Monster : public Entity {
   public:
    Monster(const std::string& n, int h, int a, int d)
        : Entity(n, h, a, d) {}

    // Переопределение метода attack
    void attack(Entity& target) override {
        int target_damage = damage - target.defense;
        if (target_damage > 0) {
            // Шанс на ядовитую атаку (30%)
            if (rand() % 100 < 30) {
                target_damage += 5;  // Дополнительный урон от яда
                std::cout << "Poisonous attack! ";
            }
            target.health -= target_damage;
            std::cout << name << " attacks " << target.name << " for " << target_damage << " damage!\n";
        } else {
            std::cout << name << " attacks " << target.name << ", but it has no effect!\n";
        }
    }

    // Переопределение метода displayInfo
    void displayInfo() const override {
        std::cout << "Monster: " << name << ", HP: " << health
                  << ", Attack: " << damage << ", Defense: " << defense << std::endl;
    }
};

int main() {
    srand(static_cast<unsigned>(time(0)));  // Инициализация генератора случайных чисел

    // Создание объектов
    Character hero("Hero", 100, 20, 10);
    Monster goblin("Goblin", 50, 15, 5);
    Monster dragon("Dragon", 150, 25, 20);

    // Массив указателей на базовый класс
    Entity* entities[] = {&hero, &goblin, &dragon};

    // Полиморфное поведение
    for (auto& entity : entities) {
        entity->displayInfo();  // Вывод информации о сущности
    }

    // Бой между персонажем и монстрами
    hero.attack(goblin);
    goblin.attack(hero);
    dragon.attack(hero);

    return 0;
}