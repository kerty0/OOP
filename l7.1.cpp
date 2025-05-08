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
    file << manager.saveAll();
}

void loadFromFile(GameManager<Entity*>& manager, const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        throw std::runtime_error("Failed to open file for reading.");
    }
    // Чтение данных из файла
    std::string str;
    file >> str;
    int i = std::stoi(str);
    while (i-- > 0) {
        file >> str;

        std::string name;
        std::string health;
        file >> name;
        file >> health;

        if (str == "Entity") {
            manager.addEntity(new Entity(name, std::stoi(health)));
        } else if (str == "Player") {
            std::string exp;
            file >> exp;
            manager.addEntity(new Player(name, std::stoi(health), std::stoi(exp)));
        } else if (str == "Enemy") {
            std::string type;
            file >> type;
            manager.addEntity(new Enemy(name, std::stoi(health), type));
        } else {
            throw std::runtime_error("Malformed save file.");
        }
    }
}

int main() {
    GameManager<Entity*> manager;
    manager.addEntity(new Entity("Chest", 1));
    manager.addEntity(new Player("Hero", 100, 0));
    manager.addEntity(new Enemy("Goblin", 10, "Goblin"));
    manager.displayAll();
    saveToFile(manager, "game_save.txt");

    GameManager<Entity*> loadedManager;
    loadFromFile(loadedManager, "game_save.txt");
    loadedManager.displayAll();

    return 0;
}