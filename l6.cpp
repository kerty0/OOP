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

template <typename T>
class Queue {
   private:
    std::vector<T> items;

   public:
    void push(const T& item) {
        items.push_back(item);
    }

    T pop() {
        if (items.empty()) {
            throw std::out_of_range("pop() called on empty queue");
        }

        T pop = items[0];
        items.erase(items.begin());
        return pop;
    }
};

int main() {
    try {
        GameManager<Entity*> manager;
        manager.addEntity(new Player("Hero", -100, 0));  // Вызовет исключение
    } catch (const std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    try {
        Queue<int> queue;
        queue.pop();  // Вызовет исключение
    } catch (const std::out_of_range& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
