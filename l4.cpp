#include <memory>
#include <vector>

#include "entity.cpp"

class Inventory {
   private:
    std::vector<std::unique_ptr<std::string>> items;

   public:
    void addItem(const std::string& item) {
        items.push_back(std::make_unique<std::string>(item));
    }

    void displayInventory() const {
        std::cout << "Inventory content:" << std::endl;
        for (const auto& item : items) {
            std::cout << *item << std::endl;
        }
    }
};

int main() {
    // Массив умных указателей на базовый класс
    std::unique_ptr<Entity> entities[] = {
        std::make_unique<Player>("Hero", 100, 0),
        std::make_unique<Enemy>("Goblin", 50, "Goblin"),
    };

    // Полиморфизм и автоматическое управление памятью
    for (const auto& entity : entities) {
        entity->displayInfo();
    }

    Inventory inventory;
    inventory.addItem("Sword");
    inventory.addItem("Shield");
    inventory.addItem("Health potion");

    inventory.displayInventory();

    return 0;
}