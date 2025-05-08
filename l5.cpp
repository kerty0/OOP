#include <iostream>
#include <vector>

#include "entity.cpp"
#include "game_manager.cpp"

template <typename T>
class Queue {
   private:
    std::vector<T> items;

   public:
    void push(const T& item) {
        items.push_back(item);
    }

    T pop() {
        T pop = items[0];
        items.erase(items.begin());
        return pop;
    }
};

int main() {
    GameManager<Entity*> manager;
    manager.addEntity(new Player("Hero", 100, 0));
    manager.addEntity(new Enemy("Goblin", 50, "Goblin"));
    manager.displayAll();

    Queue<int> queue;
    queue.push(1);
    queue.push(2);
    queue.push(3);
    queue.push(4);
    queue.push(5);
    std::cout << queue.pop() << std::endl;
    std::cout << queue.pop() << std::endl;
    std::cout << queue.pop() << std::endl;
    std::cout << queue.pop() << std::endl;
    std::cout << queue.pop() << std::endl;

    Queue<std::string> str_queue;
    str_queue.push("1");
    str_queue.push("2");
    str_queue.push("3");
    std::cout << str_queue.pop() << std::endl;
    std::cout << str_queue.pop() << std::endl;
    str_queue.push("4");
    std::cout << str_queue.pop() << std::endl;
    str_queue.push("5");
    std::cout << str_queue.pop() << std::endl;
    std::cout << str_queue.pop() << std::endl;

    return 0;
}