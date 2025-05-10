#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

class Logger {
   private:
    std::ofstream logFile;

   public:
    Logger(const std::string& filename) {
        logFile.open(filename, std::ios_base::app);
        if (!logFile.is_open()) {
            std::cerr << "Error: Could not open log file: " << filename << std::endl;
        }
    }

    ~Logger() {
        if (logFile.is_open()) {
            logFile.close();
        }
    }

    void log(const std::string& message) {
        std::cout << message << std::endl;
        if (logFile.is_open()) {
            logFile << message << std::endl;
        }
    }
};

class Monster {
   private:
    std::string name;
    int health;
    int attack;
    int defense;

   public:
    Monster(const std::string& n, int h, int a, int d)
        : name(n), health(h), attack(a), defense(d) {}

    void takeDamage(int damage) {
        health -= damage;
        if (health <= 0) throw std::runtime_error(name + " has been defeated!");
    }

    void displayInfo() const {
        std::cout << name
                  << ", HP: " << health
                  << ", Attack: " << attack
                  << ", Defense: " << defense
                  << std::endl;
    }

    std::string getName() const { return name; }
    int getHealth() const { return health; }
    int getAttack() const { return attack; }
    int getDefense() const { return defense; }
};

class Goblin : public Monster {
   public:
    Goblin() : Monster("Goblin", 30, 8, 2) {}
};

class Skeleton : public Monster {
   public:
    Skeleton() : Monster("Skeleton", 40, 10, 5) {}
};

class Dragon : public Monster {
   public:
    Dragon() : Monster("Dragon", 100, 20, 10) {}
};

class Character {
   private:
    std::string name;
    int health;
    int attack;
    int defense;
    int level;
    int experience;

   public:
    Character(const std::string& n, int h, int a, int d)
        : name(n), health(h), attack(a), defense(d), level(1), experience(0) {
        if (name.empty()) throw std::runtime_error("Name shouldn't be empty!");
        if (health <= 0) throw std::runtime_error(name + " should have positive health!");
        if (attack <= 0) throw std::runtime_error(name + " should have positive attack!");
        if (defense <= 0) throw std::runtime_error(name + " should have positive defense!");
    }

    Character(const std::string& n, int h, int a, int d, int l, int e)
        : name(n), health(h), attack(a), defense(d), level(l), experience(e) {
        if (name.empty()) throw std::runtime_error("Name shouldn't be empty!");
        if (health <= 0) throw std::runtime_error(name + " should have positive health!");
        if (attack <= 0) throw std::runtime_error(name + " should have positive attack!");
        if (defense <= 0) throw std::runtime_error(name + " should have positive defense!");
        if (level <= 0) throw std::runtime_error(name + " should have positive level!");
        if (experience < 0) throw std::runtime_error(name + " should't have negative experience!");
    }

    void attackEnemy(Monster& enemy) {
        int damage = attack - enemy.getDefense();
        if (damage > 0) {
            enemy.takeDamage(damage);
            std::cout << name << " attacks " << enemy.getName() << " for " << damage << " damage!" << std::endl;
        } else {
            std::cout << name << " attacks " << enemy.getName() << ", but it has no effect!" << std::endl;
        }
    }

    void takeDamage(Monster& enemy) {
        int damage = enemy.getAttack() - defense;
        if (damage > 0) {
            health -= damage;
            if (health <= 0) throw std::runtime_error(name + " has been defeated!");
        }
    }

    void heal(int amount) {
        health += amount;
        if (health > 100) health = 100;
        std::cout << name << " heals for " << amount << " HP!" << std::endl;
    }

    void gainExperience(int exp) {
        experience += exp;
        if (experience >= 100 && level < 100) {
            experience -= 100;
            level++;
            attack++;
            defense++;
            health = 100;
            std::cout << name << " leveled up to level " << level << "!" << std::endl;
        }
    }

    void setDamage(int amount) {
        attack = amount;
        if (attack > 100) attack = 100;
        std::cout << name << " now has attack " << attack << "!" << std::endl;
    }

    void setDefense(int amount) {
        defense = amount;
        if (defense > 100) defense = 100;
        std::cout << name << " now has defense " << defense << "!" << std::endl;
    }

    void setName(std::string new_name) {
        if (new_name.empty()) throw std::runtime_error("Empty name!");
        name = new_name;
    }

    void displayInfo() const {
        std::cout << "Name: " << name
                  << ", HP: " << health
                  << ", Attack: " << attack
                  << ", Defense: " << defense
                  << ", Level: " << level
                  << ", Experience: " << experience
                  << std::endl;
    }

    std::string save() const {
        return name + "\n" +
               std::to_string(health) + " " +
               std::to_string(attack) + " " +
               std::to_string(defense) + " " +
               std::to_string(level) + " " +
               std::to_string(experience);
    }

    std::string getName() const { return name; }
    int getHealth() const { return health; }
    int getAttack() const { return attack; }
    int getDefense() const { return defense; }
};

class Item {
   private:
    std::string name;
    std::string description;

   public:
    Item(const std::string& n, const std::string& desc) : name(n), description(desc) {}

    virtual void use(Character& character) const {};

    virtual std::string getInfo() const {
        return name + ": " + description;
    };

    virtual std::string save() const = 0;
};

class Weapon : public Item {
   private:
    int attack;

   public:
    Weapon(const std::string& n, const std::string& desc, int amount)
        : Item(n, desc), attack(amount) {}

    void use(Character& character) const override {
        character.setDamage(attack);
    }

    std::string getInfo() const override {
        return Item::getInfo() + " (Attack " + std::to_string(attack) + ")";
    }

    std::string save() const override {
        return "Weapon " + std::to_string(attack);
    }
};

class Armor : public Item {
   private:
    int defense;

   public:
    Armor(const std::string& n, const std::string& desc, int amount)
        : Item(n, desc), defense(amount) {}

    void use(Character& character) const override {
        character.setDefense(defense);
    }

    std::string getInfo() const override {
        return Item::getInfo() + " (Defense " + std::to_string(defense) + ")";
    }

    std::string save() const override {
        return "Armor " + std::to_string(defense);
    }
};

class Potion : public Item {
   private:
    int healAmount;

   public:
    Potion(const std::string& n, const std::string& desc, int heal)
        : Item(n, desc), healAmount(heal) {}

    void use(Character& character) const override {
        character.heal(healAmount);
    };

    std::string getInfo() const override {
        return Item::getInfo() + " (Heals " + std::to_string(healAmount) + " HP)";
    }

    std::string save() const override {
        return "Potion " + std::to_string(healAmount);
    }
};

class Inventory {
   private:
    std::vector<std::unique_ptr<Item>> items;

   public:
    int size() const {
        return items.size();
    }

    void addItem(std::unique_ptr<Item> item) {
        items.push_back(std::move(item));
    }

    void removeItem(int index) {
        if (index < 0 || index >= items.size()) throw std::out_of_range("Invalid item index");
        items.erase(items.begin() + index);
    }

    Item* getItem(int index) {
        if (index < 0 || index >= items.size()) throw std::out_of_range("Invalid item index");
        return items[index].get();
    }

    void display() const {
        if (items.empty()) {
            std::cout << "Inventory is empty." << std::endl;
        } else {
            std::cout << "Inventory:" << std::endl;
            for (int i = 0; i < items.size(); i++) {
                std::cout << i + 1 << ". " << items[i]->getInfo() << std::endl;
            }
        }
    }

    std::string save() const {
        std::string output = std::to_string(size());
        for (int i = 0; i < size(); i++) {
            output += "\n" + items[i]->save();
        }
        return output;
    }
};

class Game {
   private:
    Character player;
    Inventory inventory;
    std::unique_ptr<Monster> currentEnemy;
    Logger logger;
    bool gameRunning;

    int input(std::string message) {
        std::string input;
        std::cout << message;
        std::cin >> input;
        std::cout << std::endl;
        try {
            return std::stoi(input);
        } catch (const std::invalid_argument& e) {
            return 0;
        }
    }

    void createRandomEnemy() {
        int choice = rand() % 3;
        switch (choice) {
            case 0:
                currentEnemy = std::make_unique<Goblin>();
                break;
            case 1:
                currentEnemy = std::make_unique<Skeleton>();
                break;
            case 2:
                currentEnemy = std::make_unique<Dragon>();
                break;
        }
        logger.log("A " + currentEnemy->getName() + " appears!");
    }

    void battle() {
        while (true) {
            std::cout << "\n";
            logger.log("Player's turn:");
            player.displayInfo();
            currentEnemy->displayInfo();
            int choice = input("1. Attack\n2. Use item\n3. Flee\nChoice: ");
            try {
                if (choice == 1) {
                    player.attackEnemy(*currentEnemy);
                } else if (choice == 2) {
                    useItem();
                    continue;
                } else if (choice == 3) {
                    logger.log(player.getName() + " flees from battle!");
                    return;
                } else {
                    logger.log("Invalid choice!");
                    continue;
                }

                logger.log(currentEnemy->getName() + "'s turn:");
                player.takeDamage(*currentEnemy);
                logger.log(currentEnemy->getName() + " attacks " + player.getName() + "!");
            } catch (const std::runtime_error& e) {
                logger.log(e.what());

                if (player.getHealth() <= 0) {
                    gameRunning = false;
                    return;
                }

                if (currentEnemy->getHealth() <= 0) {
                    int exp = 30 + rand() % 20;
                    player.gainExperience(exp);
                    std::cout << player.getName() << " defeated " << currentEnemy->getName() << " and gained " << exp << " experience!" << std::endl;

                    if (rand() % 100 < 30) {
                        addRandomItem();
                    }

                    return;
                }

                return;
            }
        }
    }

    void useItem() {
        inventory.display();
        if (inventory.size() == 0) return;

        int choice = input("Select item to use (0 to cancel): ");
        if (choice-- == 0) return;
        if (choice < 0 || choice >= inventory.size()) {
            logger.log("Invalid item choice!");
            return;
        }

        Item* item = inventory.getItem(choice);
        logger.log("Used " + item->getInfo());
        item->use(player);
        inventory.removeItem(choice);
    }

    void addRandomItem() {
        int itemType = rand() % 3;
        std::unique_ptr<Item> item;

        if (itemType == 0) {
            int heal = 20 + rand() % 30;
            item = std::make_unique<Potion>("Health Potion", "Restores health", heal);
        } else if (itemType == 1) {
            int defense = 5 + rand() % 25;
            item = std::make_unique<Armor>("Armor", "A shining armor", defense);
        } else {
            int attack = 10 + rand() % 20;
            item = std::make_unique<Weapon>("Sword", "A sharp weapon", attack);
        }

        logger.log("Found " + item->getInfo() + " and added to inventory!");
        inventory.addItem(std::move(item));
    }

    void mainMenu() {
        bool startScreen = true;
        while (startScreen) {
            int choice = input("\nStart Menu:\n1. New game\n2. Load game\n3. Exit\nChoice: ");

            std::string name;
            try {
                switch (choice) {
                    case 1:
                        std::cout << "Your name: ";
                        std::cin >> name;
                        player.setName(name);
                        startScreen = false;
                        break;
                    case 2:
                        loadFromFile("save.txt");
                        logger.log("Game loaded successfully!");
                        startScreen = false;
                        break;
                    case 3:
                        startScreen = false;
                        gameRunning = false;
                        break;
                    default:
                        logger.log("Invalid choice!");
                }
            } catch (const std::exception& e) {
                logger.log("Error: " + std::string(e.what()));
            }
        }

        while (gameRunning) {
            int choice = input("\nMain Menu:\n1. Explore\n2. Use item\n3. Save game\n4. Exit\nChoice: ");
            try {
                switch (choice) {
                    case 1:
                        createRandomEnemy();
                        battle();
                        break;
                    case 2:
                        useItem();
                        break;
                    case 3:
                        saveToFile("save.txt");
                        logger.log("Game saved successfully!");
                        break;
                    case 4:
                        gameRunning = false;
                        break;
                    default:
                        logger.log("Invalid choice!");
                }
            } catch (const std::exception& e) {
                logger.log("Error: " + std::string(e.what()));
            }
        }
    }

    void saveToFile(std::string filename) {
        std::ofstream file(filename);
        if (!file) throw std::runtime_error("Failed to open file for writing.");

        file << player.save();
        file << "\n";
        file << inventory.save();
    };

    void loadFromFile(std::string filename) {
        std::ifstream file(filename);
        if (!file) throw std::runtime_error("Failed to open file for reading.");

        std::string name;
        int health;
        int attack;
        int defense;
        int level;
        int exp;

        std::getline(file, name);
        file >> health;
        file >> attack;
        file >> defense;
        file >> level;
        file >> exp;

        player = Character(name, health, attack, defense, level, exp);

        std::string str;
        file >> str;
        int i = std::stoi(str);
        while (i-- > 0) {
            std::string id;
            int stat;

            file >> id;
            file >> stat;

            if (id == "Potion") {
                inventory.addItem(std::make_unique<Potion>("Health Potion", "Restores health", stat));
            } else if (id == "Armor") {
                inventory.addItem(std::make_unique<Armor>("Armor", "A shining armor", stat));
            } else if (id == "Weapon") {
                inventory.addItem(std::make_unique<Weapon>("Sword", "A sharp weapon", stat));
            } else {
                throw std::runtime_error("Malformed save file.");
            }
        }
    };

   public:
    Game() : player("Hero", 100, 10, 5), logger("game_log.txt"), gameRunning(true) {}

    void start() {
        logger.log("Game started! Welcome, " + player.getName() + "!");
        mainMenu();
        logger.log("Game over! Thanks for playing!");
    }
};

int main() {
    try {
        Game game;
        game.start();
    } catch (const std::exception& e) {
        std::cerr << "Fatal error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
