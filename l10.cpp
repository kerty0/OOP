#include <algorithm>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

class User {
   protected:
    std::string name;
    int id;
    int accessLevel;

   public:
    User(const std::string& name, int id, int accessLevel)
        : name(name), id(id), accessLevel(accessLevel) {
        if (name.empty()) throw std::invalid_argument("Name can't be empty!");
        if (id < 0) throw std::invalid_argument("ID can't be negative!");
        if (accessLevel < 0) throw std::invalid_argument("Access level can't be negative!");
    }

    std::string getName() const { return name; }
    int getId() const { return id; }
    int getAccessLevel() const { return accessLevel; }

    void setName(const std::string& newName) {
        if (newName.empty()) throw std::invalid_argument("Name can't be empty!");
        name = newName;
    }

    void setAccessLevel(int newLevel) {
        if (newLevel < 0) throw std::invalid_argument("Access level can't be negative!");
        accessLevel = newLevel;
    }

    virtual void displayInfo() const {
        std::cout << "Имя: " << name << ", ID: " << id << ", Уровень доступа: " << accessLevel;
    }

    virtual std::string save() const {
        return name + "\n" + std::to_string(id) + "\n" + std::to_string(accessLevel) + "\n";
    }
};

bool cmpUserId(std::shared_ptr<User> a, std::shared_ptr<User> b) {
    return a->getId() < b->getId();
}

bool cmpUserAccess(std::shared_ptr<User> a, std::shared_ptr<User> b) {
    return a->getAccessLevel() < b->getAccessLevel() ||
           a->getAccessLevel() == b->getAccessLevel() && cmpUserId(a, b);
}

class Student : public User {
   private:
    std::string group;

   public:
    Student(const std::string& name, int id, int accessLevel, const std::string& group)
        : User(name, id, accessLevel), group(group) {
        if (group.empty()) throw std::invalid_argument("Group can't be empty!");
    }

    std::string getGroup() const { return group; }

    void setGroup(const std::string& newGroup) {
        if (group.empty()) throw std::invalid_argument("Group can't be empty!");
        group = newGroup;
    }

    void displayInfo() const override {
        std::cout << "(Студент) ";
        User::displayInfo();
        std::cout << ", Группа: " << group << std::endl;
    }

    std::string save() const override {
        return "Student\n" + User::save() + group + "\n";
    }
};

class Teacher : public User {
   private:
    std::string department;

   public:
    Teacher(const std::string& name, int id, int accessLevel, const std::string& department)
        : User(name, id, accessLevel), department(department) {
        if (department.empty()) throw std::invalid_argument("Department can't be empty!");
    }

    std::string getDepartment() const { return department; }

    void setDepartment(const std::string& newDepartment) {
        if (department.empty()) throw std::invalid_argument("Department can't be empty!");
        department = newDepartment;
    }

    void displayInfo() const override {
        std::cout << "(Преподаватель) ";
        User::displayInfo();
        std::cout << ", Кафедра: " << department << std::endl;
    }

    std::string save() const override {
        return "Teacher\n" + User::save() + department + "\n";
    }
};

class Administrator : public User {
   private:
    std::string position;

   public:
    Administrator(const std::string& name, int id, int accessLevel, const std::string& position)
        : User(name, id, accessLevel), position(position) {
        if (position.empty()) throw std::invalid_argument("Position can't be empty!");
    }

    std::string getPosition() const { return position; }

    void setPosition(const std::string& newPosition) {
        if (position.empty()) throw std::invalid_argument("Position can't be empty!");
        position = newPosition;
    }

    void displayInfo() const override {
        std::cout << "(Администратор) ";
        User::displayInfo();
        std::cout << ", Должность: " << position << std::endl;
    }

    std::string save() const override {
        return "Administrator\n" + User::save() + position + "\n";
    }
};

class Resource {
   private:
    std::string name;
    int requiredAccessLevel;

   public:
    Resource(const std::string& name, int requiredAccessLevel)
        : name(name), requiredAccessLevel(requiredAccessLevel) {
        if (name.empty()) throw std::invalid_argument("Name can't be empty!");
        if (requiredAccessLevel < 0) throw std::invalid_argument("Access level can't be negative!");
    }

    std::string getName() const { return name; }

    int getRequiredAccessLevel() const { return requiredAccessLevel; }

    void setName(const std::string& newName) {
        if (newName.empty()) throw std::invalid_argument("Name can't be empty!");
        name = newName;
    }

    void setRequiredAccessLevel(int newLevel) {
        if (requiredAccessLevel < 0) throw std::invalid_argument("Access level can't be negative!");
        requiredAccessLevel = newLevel;
    }

    bool checkAccess(const User& user) const {
        return requiredAccessLevel <= user.getAccessLevel();
    }

    void displayInfo() const {
        std::cout << "Ресурс: " << name << ", Уровень доступа: " << requiredAccessLevel << std::endl;
    }

    std::string save() const {
        return name + "\n" + std::to_string(requiredAccessLevel) + "\n";
    }

    Resource(std::ifstream& in) {
        std::getline(in, name);
        in >> requiredAccessLevel;
        in.ignore();
    }
};

template <typename T>
class AccessControlSystem {
   private:
    std::vector<std::shared_ptr<User>> users;
    std::vector<std::shared_ptr<T>> resources;

   public:
    void addUser(std::shared_ptr<User> user) {
        users.push_back(user);
    }

    void addResource(std::shared_ptr<T> resource) {
        resources.push_back(resource);
    }

    std::vector<std::shared_ptr<User>> findUsersByName(const std::string& name) const {
        std::vector<std::shared_ptr<User>> result;
        for (const auto& user : users) {
            if (user->getName() == name) {
                result.push_back(user);
            }
        }
        return result;
    }

    std::shared_ptr<User> findUserById(int id) const {
        for (const auto& user : users) {
            if (user->getId() == id) {
                return user;
            }
        }
        return nullptr;
    }

    bool checkAccess(int userId, const std::string& resourceName) const {
        auto user = findUserById(userId);
        if (user) {
            for (const auto& resource : resources) {
                if (resource->getName() == resourceName) {
                    return resource->checkAccess(*user);
                }
            }
        }
        return false;
    }

    void displayUsers() const {
        for (const auto& user : users) {
            user->displayInfo();
        }
    }

    void displayResourses() const {
        for (const auto& resource : resources) {
            resource->displayInfo();
        }
    }

    void sortUsersById() {
        std::sort(users.begin(), users.end(), cmpUserId);
    }

    void sortUsersByAccessLevel() {
        std::sort(users.begin(), users.end(), cmpUserAccess);
    }

    void saveToFile(const std::string& filename) const {
        std::ofstream output(filename);
        if (!output) throw std::runtime_error("Couldn't open save file!");

        output << users.size() << "\n";
        for (const auto& user : users) {
            output << user->save();
        }

        output << resources.size() << "\n";
        for (const auto& resource : resources) {
            output << resource->save();
        }
    }

    void loadFromFile(const std::string& filename) {
        std::ifstream input(filename);
        if (!input) throw std::runtime_error("Couldn't open save file!");

        users.clear();
        resources.clear();

        int userCount;
        input >> userCount;
        input.ignore();

        for (int i = 0; i < userCount; ++i) {
            std::string userType;
            std::string name;
            int id;
            int accessLevel;
            std::string field;

            std::getline(input, userType);
            std::getline(input, name);
            input >> id;
            input >> accessLevel;
            input.ignore();
            std::getline(input, field);

            std::shared_ptr<User> user;
            if (userType == "Student") {
                user = std::make_shared<Student>(name, id, accessLevel, field);
            } else if (userType == "Teacher") {
                user = std::make_shared<Teacher>(name, id, accessLevel, field);
            } else if (userType == "Administrator") {
                user = std::make_shared<Administrator>(name, id, accessLevel, field);
            } else {
                throw std::runtime_error("Malformed save file!");
            }
            users.push_back(user);
        }

        int resourceCount;
        input >> resourceCount;
        input.ignore();

        for (int i = 0; i < resourceCount; ++i) {
            resources.push_back(std::make_shared<T>(input));
        }
    }
};

int main() {
    try {
        AccessControlSystem<Resource> system;

        system.addUser(std::make_shared<Teacher>("T3", 1, 3, "Department 1"));
        system.addUser(std::make_shared<Teacher>("T4", 2, 4, "Department 2"));
        system.addUser(std::make_shared<Administrator>("A6", 3, 6, "Position B"));
        system.addUser(std::make_shared<Administrator>("A5", 4, 5, "Position A"));
        system.addUser(std::make_shared<Student>("S1", 8, 1, "Group 101"));
        system.addUser(std::make_shared<Student>("S1", 5, 1, "Group 101"));
        system.addUser(std::make_shared<Student>("S2", 6, 2, "Group 201"));
        system.addUser(std::make_shared<Student>("S1", 7, 1, "Group 101"));

        std::cout << "Все пользователи:" << std::endl;
        system.displayUsers();

        system.addResource(std::make_shared<Resource>("Аудитория 101", 1));
        system.addResource(std::make_shared<Resource>("Библиотека", 2));
        system.addResource(std::make_shared<Resource>("Лаборатория физики", 3));
        system.addResource(std::make_shared<Resource>("Серверная", 5));

        std::cout << "Все ресурсы:" << std::endl;
        system.displayResourses();

        std::cout << "\nПроверка доступа:" << std::endl;
        std::cout << "S1 в аудитории 101: "
                  << (system.checkAccess(5, "Аудитория 101") ? "Доступ разрешен" : "Доступ запрещен") << std::endl;
        std::cout << "S1 в лаборатории: "
                  << (system.checkAccess(5, "Лаборатория физики") ? "Доступ разрешен" : "Доступ запрещен") << std::endl;
        std::cout << "S2 в библиотеку: "
                  << (system.checkAccess(6, "Библиотека") ? "Доступ разрешен" : "Доступ запрещен") << std::endl;
        std::cout << "S2 в лаборатории: "
                  << (system.checkAccess(6, "Лаборатория физики") ? "Доступ разрешен" : "Доступ запрещен") << std::endl;
        std::cout << "T3 в лаборатории: "
                  << (system.checkAccess(1, "Лаборатория физики") ? "Доступ разрешен" : "Доступ запрещен") << std::endl;
        std::cout << "T3 в серверной: "
                  << (system.checkAccess(1, "Серверная") ? "Доступ разрешен" : "Доступ запрещен") << std::endl;
        std::cout << "A6 в серверной: "
                  << (system.checkAccess(3, "Серверная") ? "Доступ разрешен" : "Доступ запрещен") << std::endl;

        std::cout << "\nПоиск пользователя по ID 2:" << std::endl;
        auto user = system.findUserById(2);
        if (user) {
            user->displayInfo();
        }

        system.saveToFile("university_data.txt");
        system.loadFromFile("university_data.txt");

        std::cout << "\nДанные после загрузки из файла:" << std::endl;
        system.displayUsers();
        system.displayResourses();

        system.sortUsersByAccessLevel();
        std::cout << "\nПользователи после сортировки по уровню доступа:" << std::endl;
        system.displayUsers();

        system.sortUsersById();
        std::cout << "\nПользователи после сортировки по Id:" << std::endl;
        system.displayUsers();

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}