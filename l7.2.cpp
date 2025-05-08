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
        std::cout << "New monster generated!" << std::endl
                  << std::endl;
    }
}

void battleMonsters() {
    Player hero("Hero", 10, 0);

    while (hero.getHealth() > 0) {
        std::this_thread::sleep_for(std::chrono::seconds(5));
        std::lock_guard<std::mutex> lock(monstersMutex);

        if (!monsters.empty()) {
            hero.setHealth(hero.getHealth() - monsters[0].getHealth() / 10);
            monsters.erase(monsters.begin());
            std::cout << "Monster slayed!" << std::endl;
            std::cout << "Current hero health: " << hero.getHealth() << std::endl
                      << std::endl;
        }
    }
    std::cout << "Hero slayed!" << std::endl
              << std::endl;
}

int main() {
    std::thread monsterGenerator(generateMonsters);
    monsterGenerator.detach();  // Отсоединяем поток

    std::thread battleThread(battleMonsters);
    battleThread.detach();

    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));

        std::lock_guard<std::mutex> lock(monstersMutex);
        std::cout << "Alive monsters:" << std::endl;
        for (auto& monster : monsters) {
            monster.displayInfo();
        }
        std::cout << std::endl;
    }

    return 0;
}