#include <iostream>

class Entity {
   protected:
    std::string name;
    int health;

   public:
    Entity(const std::string& n, int h) : name(n), health(h) {}

    int getHealth() const {
        return health;
    }

    void setHealth(int new_health) {
        health = std::max(new_health, 0);
    }

    virtual void displayInfo() const {
        std::cout << "Name: " << name << ", HP: " << health << std::endl;
    }

    virtual std::string save() const {
        return "Entity " + name + " " + std::to_string(health);
    }

    virtual ~Entity() {}
};

class Player : public Entity {
   private:
    int experience;

   public:
    Player(const std::string& n, int h, int exp)
        : Entity(n, h), experience(exp) {}

    void displayInfo() const override {
        Entity::displayInfo();
        std::cout << "Experience: " << experience << std::endl;
    }

    std::string save() const override {
        return "Player " + name + " " + std::to_string(health) + " " + std::to_string(experience);
    }
};

class Enemy : public Entity {
   private:
    std::string type;

   public:
    Enemy(const std::string& n, int h, const std::string& t)
        : Entity(n, h), type(t) {}

    void displayInfo() const override {
        Entity::displayInfo();
        std::cout << "Type: " << type << std::endl;
    }

    std::string save() const override {
        return "Enemy " + name + " " + std::to_string(health) + " " + type;
    }
};
