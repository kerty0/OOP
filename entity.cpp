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

    virtual void displayInfo() const {
        std::cout << "Name: " << name << ", HP: " << health << std::endl;
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
};
