#include <chrono>
#include <cstdlib>
#include <mutex>
#include <thread>
#include <vector>

#include "entity.cpp"

std::vector<Enemy> monsters;
std::mutex monstersMutex;

void generateMonsters() {
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(3));  // Новый монстр каждые 3 секунды
        std::lock_guard<std::mutex> lock(monstersMutex);
        monsters.push_back(Enemy("Weak Goblin", 50, "Goblin"));
        std::cout << "New monster generated!" << std::endl;
    }
}

int main() {
    std::thread monsterGenerator(generateMonsters);
    monsterGenerator.detach();  // Отсоединяем поток

    Player hero("Hero", 100, 0);

    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));

        std::lock_guard<std::mutex> lock(monstersMutex);
        for (auto& monster : monsters) {
            monster.displayInfo();
        }
    }

    return 0;
}