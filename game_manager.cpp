#include <iostream>
#include <vector>

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

    void displayAll() const {
        std::cout << "GameManager content:" << std::endl;
        for (int i = 0; i < entities.size(); i++) {
            entities[i]->displayInfo();
        }
    }

    std::string saveAll() const {
        std::string state = std::to_string(entities.size()) + "\n";
        for (int i = 0; i < entities.size(); i++) {
            state += entities[i]->save() + "\n";
        }
        return state;
    }
};