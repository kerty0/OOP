#include <fstream>
#include <string>

#include "entity.cpp"
#include "game_manager.cpp"

void saveToFile(const GameManager<Entity*>& manager, const std::string& filename) {
    std::ofstream file(filename);
    if (!file) {
        throw std::runtime_error("Failed to open file for writing.");
    }
    // Запись данных в файл
}

void loadFromFile(GameManager<Entity*>& manager, const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        throw std::runtime_error("Failed to open file for reading.");
    }
    // Чтение данных из файла
}

int main() {
    GameManager<Entity*> manager;
    manager.addEntity(new Player("Hero", 100, 0));
    manager.displayAll();
    saveToFile(manager, "game_save.txt");

    GameManager<Entity*> loadedManager;
    loadFromFile(loadedManager, "game_save.txt");
    loadedManager.displayAll();

    return 0;
}