#include "class.h"
#include <string>
#include <random>
#include <ctime>

void getGamesContent(GameTree &arr)
{
    std::ifstream file("Games.txt");
    std::string id, name, dev, publish, sizeGBs, downloads;
    int rollNo = 230056;

    while (std::getline(file, id, '\n'))
    {
        int temp = rand() % 1001;
        if (temp >= (56 * 10 + 100))
        {
            std::string curr, ID, name, dev, pub, size;
            int commas = 0;
            for (char ch : id)
            {
                if (ch == ',')
                {
                    if (commas == 0)
                        ID = curr;
                    else if (commas == 1)
                        name = curr;
                    else if (commas == 2)
                        dev = curr;
                    else if (commas == 3)
                        pub = curr;
                    else if (commas == 4)
                        size = curr;

                    commas++;
                    curr = "";
                }
                else
                    curr += ch;
            }
            Game game(ID, name, dev, pub, std::stof(size), std::stol(curr));
            arr.insert(game);
        }
    }

    file.close();
}

void setupPlayerGames(Player &player, std::string &games)
{
    int commas = 0;
    std::string curr, id;
    float hrs;
    int ach;
    for (char c : games)
    {
        if (c == ',')
        {
            if (commas % 3 == 0)
            {
                id = curr;
            }
            else if (commas % 3 == 1)
                hrs = std::stof(curr);
            else if (commas % 3 == 2)
            {
                ach = std::stoi(curr);
                GamesPlayedNode game(id, hrs, ach);
                player.insertGame(game);
            }
            curr = "";
            commas++;
        }
        else
        {
            curr += c;
        }
    }
}
void getPlayersContent(PlayerBST &players)
{
    std::ifstream file("Players.txt");
    std::string id, name, number, email, password, line, curr;
    while (std::getline(file, line, '\n'))
    {
        int temp = rand() % 1001;
        if (temp >= (56 * 10 + 100))
        {
        int commas = 0;
        for (char c : line)
        {
            if (c == ',')
            {
                if (commas == 0)
                    id = curr;
                else if (commas == 1)
                    name = curr;
                else if (commas == 2)
                    number = curr;
                else if (commas == 3)
                    email = curr;
                else if (commas == 4)
                    password = curr;
                commas++;
                if (commas <= 5)
                {
                    curr = "";
                    continue;
                }
            }
            curr += c;
        }
        // std::cout << "ID: " << curr << '\n';
        Player player(id, name, number, email, password);
        setupPlayerGames(player, curr);
        curr = "";
        // std::cout << player << '\n';
        players.insert(player);
        }
    }
    file.close();
}

int main() {
    PlayerBST playerTree;
    GameTree gameTree;

    // Load initial data (you might want to implement this separately)
    getPlayersContent(playerTree);
    getGamesContent(gameTree);

    while (true) {
        std::cout << "\n--- Game Management System ---\n";
        std::cout << "1. Insert Player/Game\n";
        std::cout << "2. Search and Retrieve\n";
        std::cout << "3. Delete Entry\n";
        std::cout << "4. Save Data to CSV\n";
        std::cout << "5. Show N Layers\n";
        std::cout << "6. Show Layer Number\n";
        std::cout << "7. Show Path\n";
        std::cout << "8. Edit Entry\n";
        std::cout << "9. Top N Players\n";
        std::cout << "10. Show Player Details\n";
        std::cout << "11. Check if Player Has Played Game\n";
        std::cout << "0. Exit\n";
        std::cout << "Enter your choice: ";

        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1: {
                std::cout << "Insert (P)layer or (G)ame? ";
                char type;
                std::cin >> type;
                if (type == 'P' || type == 'p') {
                    Player newPlayer;
                    // Implement input for player details
                    if (playerTree.search(newPlayer.getID()) == nullptr) {
                        playerTree.insert(newPlayer);
                        std::cout << "Player inserted successfully.\n";
                    } else {
                        std::cout << "Error: Player ID already exists.\n";
                    }
                } else if (type == 'G' || type == 'g') {
                    Game newGame;
                    // Implement input for game details
                    if (gameTree.search(newGame.getID()) == nullptr) {
                        gameTree.insert(newGame);
                        std::cout << "Game inserted successfully.\n";
                    } else {
                        std::cout << "Error: Game ID already exists.\n";
                    }
                }
                break;
            }
            case 2: {
                std::cout << "Search (P)layer or (G)ame? ";
                char type;
                std::cin >> type;
                std::string id;
                std::cout << "Enter ID: ";
                std::cin >> id;
                if (type == 'P' || type == 'p') {
                    TreeNode<Player>* result = playerTree.search(id);
                    if (result) std::cout << result->data;
                    else std::cout << "Player not found.\n";
                } else if (type == 'G' || type == 'g') {
                    TreeNode<Game>* result = gameTree.search(id);
                    if (result) std::cout << result->data;
                    else std::cout << "Game not found.\n";
                }
                break;
            }
            case 3: {
                std::cout << "Delete (P)layer or (G)ame? ";
                char type;
                std::cin >> type;
                std::string id;
                std::cout << "Enter ID to delete: ";
                std::cin >> id;
                if (type == 'P' || type == 'p') {
                    playerTree.deleteTreeNode(id);
                } else if (type == 'G' || type == 'g') {
                    gameTree.deleteTreeNode(id);
                }
                std::cout << "Deletion completed.\n";
                break;
            }
            case 4: {
                playerTree.writeInCSV();
                // Implement similar function for gameTree if needed
                std::cout << "Data saved to CSV.\n";
                break;
            }
            case 5: {
                int n;
                std::cout << "Enter number of layers to show: ";
                std::cin >> n;
                std::cout << "Players:\n";
                playerTree.showNlayers(n);
                std::cout << "Games:\n";
                gameTree.showNlayers(n);
                break;
            }
            case 6: {
                // Implement show layer number functionality
                // This might require adding a new method to your BST classes
                break;
            }
            case 7: {
                // Implement show path functionality
                // This might require adding a new method to your BST classes
                break;
            }
            case 8: {
                std::cout << "Edit (P)layer or (G)ame? ";
                char type;
                std::cin >> type;
                std::string id;
                std::cout << "Enter ID to edit: ";
                std::cin >> id;
                if (type == 'P' || type == 'p') {
                    playerTree.findAndEdit(id);
                } else if (type == 'G' || type == 'g') {
                    // Implement similar function for games
                }
                break;
            }
            case 9: {
                int n;
                std::cout << "Enter N for top players: ";
                std::cin >> n;
                playerTree.showTopNPlayers(n);
                break;
            }
            case 10: {
                std::string id;
                std::cout << "Enter Player ID: ";
                std::cin >> id;
                TreeNode<Player>* player = playerTree.search(id);
                if (player) {
                    std::cout << player->data;
                    // Implement showing details of games played by this player
                } else {
                    std::cout << "Player not found.\n";
                }
                break;
            }
            case 11: {
                std::string playerId, gameId;
                std::cout << "Enter Player ID: ";
                std::cin >> playerId;
                std::cout << "Enter Game ID: ";
                std::cin >> gameId;
                bool hasPlayed = playerTree.hasPlayed(playerId, gameId);
                std::cout << "Player " << (hasPlayed ? "has" : "has not") << " played this game.\n";
                break;
            }
            case 0:
                std::cout << "Exiting program.\n";
                return 0;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}