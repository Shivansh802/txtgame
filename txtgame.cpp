#include <iostream>
#include <string>
#include <map>

class Room {
private:
    std::string description;
    std::map<std::string, Room*> exits;

public:
    Room(std::string desc) : description(desc) {}

    void setExit(std::string direction, Room* neighbor) {
        exits[direction] = neighbor;
    }

    std::string getShortDescription() {
        return description;
    }

    std::string getLongDescription() {
        std::string longDesc = "You are " + description + ".\n";
        longDesc += "Exits:";
        for (auto exit : exits) {
            longDesc += " " + exit.first;
        }
        longDesc += "\n";
        return longDesc;
    }

    Room* getExit(std::string direction) {
        if (exits.find(direction) != exits.end()) {
            return exits[direction];
        } else {
            return nullptr;
        }
    }
};
#include <iostream>
#include <vector>
#include <string>

class Player {
private:
    Room* currentRoom;
    std::vector<std::string> inventory;

public:
    Player(Room* startRoom) : currentRoom(startRoom) {}

    void setCurrentRoom(Room* room) {
        currentRoom = room;
    }

    Room* getCurrentRoom() {
        return currentRoom;
    }

    void takeItem(std::string item) {
        inventory.push_back(item);
        std::cout << "You have taken " << item << "." << std::endl;
    }

    bool hasItem(std::string item) {
        for (auto& i : inventory) {
            if (i == item) {
                return true;
            }
        }
        return false;
    }
};
int main() {
    // Create rooms
    Room* room1 = new Room("in a small room");
    Room* room2 = new Room("in a large room");

    // Connect rooms
    room1->setExit("north", room2);
    room2->setExit("south", room1);

    // Create player and start them in room1
    Player player(room1);

    // Game loop
    while (true) {
        // Display current room description
        std::cout << player.getCurrentRoom()->getLongDescription() << std::endl;

        // Player input
        std::cout << "Enter a direction (or 'quit' to quit): ";
        std::string input;
        std::cin >> input;

        if (input == "quit") {
            break;
        }

        // Check if the input is a valid direction
        Room* nextRoom = player.getCurrentRoom()->getExit(input);
        if (nextRoom != nullptr) {
            // Move player to the next room
            player.setCurrentRoom(nextRoom);
        } else {
            std::cout << "Invalid direction. Try again." << std::endl;
        }
    }

    // Clean up
    delete room1;
    delete room2;

    return 0;
}