#include <iostream>

template <typename T>
class Array {
    T* arr;
    int size;
    int index;

    void increaseSize(int newSize) {
        T* newArr = new T[newSize];
        for (int i = 0; i < this->size; i++) {
            newArr[i] = this->arr[i];
        }
        delete[] this->arr; 
        this->arr = newArr;
        this->size = newSize;
    }

    void allocate(int Size, bool keepValue = false) {
        if (keepValue) {
            increaseSize(Size);
            return;
        }
        if (arr) {
            delete[] arr;
        }
        arr = new T[Size];
        size = Size;
        index = 0;
    }

public:
    Array() : size(0), index(0), arr(nullptr) {}
    
    ~Array() {
        if (arr) {
            delete[] arr;  
            arr = nullptr;
        }
    }
    
    // Fixed copy constructor
    Array(const Array& other) : size(other.size), index(other.index), arr(nullptr) {
        std::cout << "Copy Constructor Called\n";
        if (other.arr) {
            arr = new T[size];
            for (int i = 0; i < size; i++) {  // Copy all elements up to size
                arr[i] = other.arr[i];
            }
        }
    }

    // Methods
    void add(const T& value) {
        if (size == 0) {
            allocate(1);
        }
        if (index >= size) {  // if we need to resize
            allocate(size * 2, true);
        }
        arr[index++] = value;
    }

    T pop(int pos = -1) {
        
        if (pos == -1) {
            pos = index - 1;
        }
        T value = arr[pos];
        for (int i = pos; i < index - 1; i++) {
            arr[i] = arr[i + 1];
        }
        index--;
        return value;
    }

    Array& operator=(const Array& other) {
        if (this != &other) { 
            if (arr) {
                delete[] arr;
            }
            size = other.size;
            index = other.index;
            arr = new T[size];
            for (int i = 0; i < size; i++) {
                arr[i] = other.arr[i];
            }
        }
        return *this; 
    }

    const T& operator[](int i) const { 
        return arr[i];
    }

    T& operator[](int i) { 
        return arr[i];
    }

    int getSize() const { return index; }
    int getCapacity() const { return size; }
};

class GamesPlayedNode {
private:
    std::string ID;
    float hrsPlayed;
    int achievements;

public:
    GamesPlayedNode() : ID(""), hrsPlayed(0.0f), achievements(0) {}

    std::string getID() const { return ID; }
    void setID(const std::string& id) { ID = id; }

    float getHrsPlayed() const { return hrsPlayed; }
    void setHrsPlayed(float hours) { hrsPlayed = hours; }

    int getAchievements() const { return achievements; }
    void setAchievements(int ach) { achievements = ach; }
};

class Player {
private:
    std::string ID;
    std::string name;
    std::string number;
    std::string email;
    std::string password;
    Array<GamesPlayedNode> gamesPlayed;

public:
    Player() : ID(""), name(""), number(""), email(""), password("") {}

    std::string getID() const { return ID; }
    void setID(const std::string& id) { ID = id; }

    std::string getName() const { return name; }
    void setName(const std::string& playerName) { name = playerName; }

    std::string getNumber() const { return number; }
    void setNumber(const std::string& playerNumber) { number = playerNumber; }

    std::string getEmail() const { return email; }
    void setEmail(const std::string& playerEmail) { email = playerEmail; }

    std::string getPassword() const { return password; }
    void setPassword(const std::string& playerPassword) { password = playerPassword; }

    GamesPlayedNode& operator [] (int index) {
        return gamesPlayed[index];
    }

    const GamesPlayedNode& operator [] (int index) const {
        return gamesPlayed[index];
    }
};


class Game {
private:
    std::string ID;
    std::string name;
    std::string developer;
    std::string publisher;
    float sizeInGBs;
    int downloads;

public:
    Game(const std::string& id, const std::string& name, const std::string& developer, const std::string& publisher, float size, int downloads)
        : ID(id), name(name), developer(developer), publisher(publisher), sizeInGBs(size), downloads(downloads) {}

    std::string getID() const { return ID; }
    void setID(const std::string& id) { ID = id; }

    std::string getName() const { return name; }
    void setName(const std::string& name) { this->name = name; }

    std::string getDeveloper() const { return developer; }
    void setDeveloper(const std::string& developer) { this->developer = developer; }

    std::string getPublisher() const { return publisher; }
    void setPublisher(const std::string& publisher) { this->publisher = publisher; }

    float getSizeInGBs() const { return sizeInGBs; }
    void setSizeInGBs(float size) { sizeInGBs = size; }

    int getDownloads() const { return downloads; }
    void setDownloads(int downloads) { this->downloads = downloads; }
};