#include <iostream>
#include <vector>

#include "entity.cpp"

template <typename T>
class GameManager {
   private:
    std::vector<T> entities;

   public:
    void addEntity(const T& entity) {
        if (entity->getHealth() <= 0) {
            throw std::invalid_argument("Entity has invalid health");
        }
        entities.push_back(entity);
    }
};

int main() {
    try {
        GameManager<Entity*> manager;
        manager.addEntity(new Player("Hero", -100, 0));  // Вызовет исключение
    } catch (const std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
