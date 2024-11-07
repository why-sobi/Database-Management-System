#include <iostream>
#include "header.h"



class Player
{
private:
    std::string ID;
    std::string name;
    std::string number;
    std::string email;
    std::string password;
    GamesPlayedBST gamesPlayed;

public:
    Player(std::string id = "", std::string n = "", std::string num = "",
           std::string mail = "", std::string pass = "") : ID(id), name(n), number(num), email(mail), password(pass)
    {
    }
    Player(GamesPlayedBST &games, std::string id = "", std::string n = "", std::string num = "",
           std::string mail = "", std::string pass = "") : ID(id), name(n), number(num), email(mail), password(pass)
    {
        gamesPlayed.moveOwnerShip(games);
    }

    Player(Player& obj) {
        this->ID = obj.ID;
        this->name = obj.name;
        this->number = obj.number;
        this->email = obj.email;
        this->password = obj.password;

        this->gamesPlayed.moveOwnerShip(obj.gamesPlayed);
    }

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

    int getGamesPlayed() const { return gamesPlayed.getGamesPlayed(); }

    void insertGame(GamesPlayedNode &game)
    {
        gamesPlayed.insert(game);
    }

    TreeNode<GamesPlayedNode> *search(std::string GameID)
    {
        return gamesPlayed.search(GameID);
    }

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
    void writePlayer(std::ofstream& file) {
        file << ID << "," << name << "," << number << "," << email << "," << password << ',';
        gamesPlayed.writeGames(file);
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

    void operator=(Player &obj)
    {
        *this = obj;
        this->gamesPlayed.moveOwnerShip(obj.gamesPlayed);
    }

    friend std::ostream &operator<<(std::ostream &out, Player &obj)
    {
        // std::cout << "Hello\n\n";
        out << "------------ " << obj.name << " has the following details------------\n";
        out << "ID: " << obj.ID << '\n';
        out << "Contact Number: " << obj.number << '\n';
        out << "Email: " << obj.email << '\n';
        out << "Password: " << obj.password << '\n';
        out << "Games Played: " << obj.gamesPlayed.getGamesPlayed() << '\n';
        // out << "Games played: " << obj.gamesPlayed << '\n';
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
    long int downloads;

public:
    Game() {}
    Game(const std::string &id, const std::string &name, const std::string &developer, const std::string &publisher, float size, long int downloads)
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

    long int getDownloads() const { return downloads; }
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

    bool operator<(std::string &other)
    {
        return this->ID < other;
    }

    bool operator>(std::string &other)
    {
        return this->ID > other;
    }

    bool operator==(std::string &other)
    {
        return this->ID == other;
    }

    friend std::ostream &operator<<(std::ostream &out, const Game &obj)
    {
        out << "------------ " << obj.name << " has the following details------------\n";
        out << "ID: " << obj.ID << '\n';
        out << "Developer: " << obj.developer << '\n';
        out << "Pusblisher: " << obj.publisher << '\n';
        out << "Size(GBs): " << obj.sizeInGBs << '\n';
        out << "Downloads: " << obj.downloads << '\n';
        out << '\n';
        return out;
    }
};

struct PersonalDetails
{
    std::string ID;
    std::string name;
    std::string number;
    std::string email;
    std::string password;
    int gamesPlayed;

    PersonalDetails operator = (Player& obj) {
        this->ID = obj.getID();
        this->name = obj.getName();
        this->number = obj.getNumber();
        this->email = obj.getEmail();
        this->password = obj.getPassword();
        this->gamesPlayed = obj.getGamesPlayed();
        return *this;
    }

    bool operator < (PersonalDetails &obj) {
        return gamesPlayed < obj.gamesPlayed;
    }

    bool operator > (PersonalDetails &obj) {
        return gamesPlayed > obj.gamesPlayed;
    }

    bool operator == (PersonalDetails &obj) {
        return gamesPlayed == obj.gamesPlayed;
    }

    friend std::ostream& operator << (std::ostream& out, PersonalDetails &obj) {
        std::cout << "----------------- " << obj.name << " has the following details-----------------\n";
        std::cout << "ID: " << obj.ID << '\n';
        std::cout << "Number: " << obj.number << '\n';
        std::cout << "Email: " << obj.email << '\n';
        std::cout << "Password: " << obj.password << '\n';
        std::cout << "Games Played: " << obj.gamesPlayed << '\n';
        std::cout << '\n';
        return out;
    }
};

class PlayerBST : public BST<Player>
{

    void pushIntoTempTree(TreeNode<Player> *root, BST<PersonalDetails> &temp)
    {
        if (root == nullptr)
            return;
        PersonalDetails player;
        player = root->data;
        temp.insert(player);
        pushIntoTempTree(root->left, temp);
        pushIntoTempTree(root->right, temp);
    }
    void writeInCSV(TreeNode<Player> *root, std::ofstream& file) {
        if (root != nullptr) {
            root->data.writePlayer(file);
            writeInCSV(root->left, file);
            writeInCSV(root->right, file);
        }
    }

public:
    PlayerBST() : BST<Player>() {}
    void showTopNPlayers(int n)
    {
        BST<PersonalDetails> temporary;
        pushIntoTempTree(root, temporary);

        temporary.TopKElements(n);
    }
    bool hasPlayed(std::string PlayerID, std::string GameID)
    {
        TreeNode<Player> *player = BST::search(PlayerID);
        if (player)
        {
            TreeNode<GamesPlayedNode> *game = player->data.search(GameID);
            if (game)
            {
                return true;
            }
            return false;
        }
        return false;
    }
    void writeInCSV() {
        std::ofstream file("PlayerData.csv");
        if (file.is_open()) {
            writeInCSV(root, file);
        }
        file.close();
    }
};

class GameTree : public BST<Game>
{
public:
};