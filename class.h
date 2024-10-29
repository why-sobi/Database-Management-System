#include <iostream>
#include "header.h"

template <typename T>
class Array
{
    T *arr;
    int size;
    int index;

    void increaseSize(int newSize)
    {
        T *newArr = new T[newSize];
        for (int i = 0; i < this->size; i++)
        {
            newArr[i] = this->arr[i];
        }
        delete[] this->arr;
        this->arr = newArr;
        this->size = newSize;
    }

    void allocate(int Size, bool keepValue = false)
    {
        if (keepValue)
        {
            increaseSize(Size);
            return;
        }
        if (arr)
        {
            delete[] arr;
        }
        arr = new T[Size];
        size = Size;
        index = 0;
    }

public:
    Array() : size(0), index(0), arr(nullptr) {}

    ~Array()
    {
        if (arr)
        {
            delete[] arr;
            arr = nullptr;
        }
    }

    // Fixed copy constructor
    Array(const Array &other) : size(other.size), index(other.index), arr(nullptr)
    {
        std::cout << "Copy Constructor Called\n";
        if (other.arr)
        {
            arr = new T[size];
            for (int i = 0; i < size; i++)
            { // Copy all elements up to size
                arr[i] = other.arr[i];
            }
        }
    }

    // Methods
    void add(const T &value)
    {
        if (size == 0)
        {
            allocate(1);
        }
        if (index >= size)
        { // if we need to resize
            allocate(size * 2, true);
        }
        arr[index++] = value;
    }

    T pop(int pos = -1)
    {

        if (pos == -1)
        {
            pos = index - 1;
        }
        T value = arr[pos];
        for (int i = pos; i < index - 1; i++)
        {
            arr[i] = arr[i + 1];
        }
        index--;
        return value;
    }

    Array &operator=(const Array &other)
    {
        if (this != &other)
        {
            if (arr)
            {
                delete[] arr;
            }
            size = other.size;
            index = other.index;
            arr = new T[size];
            for (int i = 0; i < size; i++)
            {
                arr[i] = other.arr[i];
            }
        }
        return *this;
    }

    const T &operator[](int i) const
    {
        return arr[i];
    }

    T &operator[](int i)
    {
        return arr[i];
    }

    int getSize() const { return index; }
    int getCapacity() const { return size; }
};

class GamesPlayedNode
{
private:
    std::string ID;
    float hrsPlayed;
    int achievements;

public:
    GamesPlayedNode() : ID(""), hrsPlayed(0.0f), achievements(0) {}

    std::string getID() const { return ID; }
    void setID(const std::string &id) { ID = id; }

    float getHrsPlayed() const { return hrsPlayed; }
    void setHrsPlayed(float hours) { hrsPlayed = hours; }

    int getAchievements() const { return achievements; }
    void setAchievements(int ach) { achievements = ach; }


    friend std::ostream &operator<<(std::ostream &out, GamesPlayedNode &obj)
    {
        out << "ID: " << obj.ID << '\n';
        out << "Hours Played: " << obj.hrsPlayed << '\n';
        out << "Acheivements Unlocked: " << obj.achievements << '\n';
        out << '\n';
        return out;
    }
};

class Player
{
private:
    std::string ID;
    std::string name;
    std::string number;
    std::string email;
    std::string password;
    BST<GamesPlayedNode> gamesPlayed;

public:
    Player() : ID(""), name(""), number(""), email(""), password("") {}

    // Getters and Setters
    std::string getID() const { return ID; }
    void setID(const std::string &id) { ID = id; }

    std::string getName() const { return name; }
    void setName(const std::string &playerName) { name = playerName; }

    std::string getNumber() const { return number; }
    void setNumber(const std::string &playerNumber) { number = playerNumber; }

    std::string getEmail() const { return email; }
    void setEmail(const std::string &playerEmail) { email = playerEmail; }

    std::string getPassword() const { return password; }
    void setPassword(const std::string &playerPassword) { password = playerPassword; }

    // Methods
    bool edit()
    {
        std::cout << "What do you want to edit: ";
        std::cout << "1. ID\n";
        std::cout << "2. Name\n";
        std::cout << "3. Number\n";
        std::cout << "4. Email\n";
        std::cout << "5. Password\n";
        std::cout << "6. Specific Game\n";
        std::cout << "Enter Choice: ";
        char choice;
        std::cin >> choice;

        switch (choice)
        {
        case '1':
            std::cout << "Enter new ID: ";
            std::cin >> ID;
            break;
        case '2':
            std::cout << "Enter new Name: ";
            std::cin >> name;
            break;
        case '3':
            std::cout << "Enter new Number: ";
            std::cin >> number;
            break;
        case '4':
            std::cout << "Enter new Email: ";
            std::cin >> email;
            break;
        case '5':
            std::cout << "Enter new Password: ";
            std::cin >> password;
            break;
        case '6':
            std::string gameID;
            std::cout << "Enter Game ID: ";
            std::cin >> gameID;
        }
        return choice == '1';
    }

    // Operator overload
    bool operator<(const Player &other)
    {
        return this->ID < other.ID;
    }

    bool operator>(const Player &other)
    {
        return this->ID > other.ID;
    }

    bool operator==(const Player &other)
    {
        return this->ID == other.ID;
    }

    bool operator<(const std::string &other)
    {
        return this->ID < other;
    }

    bool operator>(const std::string &other)
    {
        return this->ID > other;
    }

    bool operator==(const std::string &other)
    {
        return this->ID == other;
    }

    void operator = (Player& obj) {
        *this = obj;
        this->gamesPlayed.moveOwnerShip(obj.gamesPlayed);
    }

    friend std::ostream &operator<<(std::ostream &out, Player &obj)
    {
        out << "------------ " << obj.name << " has the following details------------";
        out << "ID: " << obj.ID << '\n';
        out << "Contact Number: " << obj.number << '\n';
        out << "Email: " << obj.email << '\n';
        out << "Password: " << obj.password << '\n';
        out << "Games played: " << obj.gamesPlayed << '\n';
        out << '\n';
        return out;
    }
};

class Game
{
private:
    std::string ID;
    std::string name;
    std::string developer;
    std::string publisher;
    float sizeInGBs;
    int downloads;

public:
    Game(const std::string &id, const std::string &name, const std::string &developer, const std::string &publisher, float size, int downloads)
        : ID(id), name(name), developer(developer), publisher(publisher), sizeInGBs(size), downloads(downloads) {}

    std::string getID() const { return ID; }
    void setID(const std::string &id) { ID = id; }

    std::string getName() const { return name; }
    void setName(const std::string &name) { this->name = name; }

    std::string getDeveloper() const { return developer; }
    void setDeveloper(const std::string &developer) { this->developer = developer; }

    std::string getPublisher() const { return publisher; }
    void setPublisher(const std::string &publisher) { this->publisher = publisher; }

    float getSizeInGBs() const { return sizeInGBs; }
    void setSizeInGBs(float size) { sizeInGBs = size; }

    int getDownloads() const { return downloads; }
    void setDownloads(int downloads) { this->downloads = downloads; }

    bool operator<(const Game &other)
    {
        return this->ID < other.ID;
    }

    bool operator==(const Game &other)
    {
        return this->ID == other.ID;
    }

    bool operator>(const Game &other)
    {
        return this->ID > other.ID;
    }

    bool operator<(const std::string &other)
    {
        return this->ID < other;
    }

    bool operator>(const std::string &other)
    {
        return this->ID > other;
    }

    bool operator==(const std::string &other)
    {
        return this->ID == other;
    }

    friend std::ostream &operator<<(std::ostream &out, const Game &obj)
    {
        out << "------------ " << obj.name << " has the following details------------";
        out << "ID: " << obj.ID << '\n';
        out << "Developer: " << obj.developer << '\n';
        out << "Pusblisher: " << obj.publisher << '\n';
        out << "Size(GBs): " << obj.sizeInGBs << '\n';
        out << "Downloads: " << obj.downloads << '\n';
        out << '\n';
        return out;
    }
};