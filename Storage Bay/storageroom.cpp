#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

// Function to read text from a file and append a newline
string readFromFile(const string& filename)
{
    ifstream file(filename);
    if (!file)
    {
        cerr << "Error: Could not open file " << filename << endl;
        return "";
    }
    string content;
    getline(file, content, '\0'); // Read entire file content into string
    file.close();
    content += "\n"; // Append a newline to the content
    return content;
}

// Copilot class
class Copilot {
public:
    bool obtained; // Indicates if the copilot has been found
    bool injured;  // Indicates if the copilot is injured

    // Constructor to initialize copilot state
    Copilot() : obtained(false), injured(false) {}
};

// Player class
class Player
{
public:
    enum Location { ENGINE_ROOM, COCKPIT, HALLWAY, STORAGE_ROOM, MEDICAL_BAY, SLEEPING_QUARTERS };

private:
    string name;
    bool key;
    Copilot copilot;
    bool puzzlePiece;
    Location location;

public:
    Player() : key(false), puzzlePiece(false), location(ENGINE_ROOM) {}

    void setName(const string& n) { name = n; }
    string getName() const { return name; }

    void setKey(bool k) { key = k; }
    bool getKey() const { return key; }

    Copilot& getCopilot() { return copilot; }
    const Copilot& getCopilot() const { return copilot; }

    void setPuzzlePiece(bool p) { puzzlePiece = p; }
    bool getPuzzlePiece() const { return puzzlePiece; }

    void setLocation(Location l) { location = l; }
    Location getLocation() const { return location; }
};

// StorageRoom class
class StorageRoom
{
private:
    bool status;
    bool enemy;
    bool pirateEncountered; // Track if pirate has been encountered

public:
    StorageRoom() : status(false), enemy(true), pirateEncountered(false) {}

    void setStatus(bool s) { status = s; }
    bool getStatus() const { return status; }

    void setEnemy(bool e) { enemy = e; }
    bool getEnemy() const { return enemy; }

    void enter(Player& player)
    {
        if (!player.getCopilot().obtained)
        {
            cout << "You need to find the copilot first before entering the storage room.\n";
            return;
        }

        if (!pirateEncountered)
        {
            cout << readFromFile("storageroom_entry.txt") << endl;

            // Choice of weapon
            int choice;
            int buff = 0;
            do {
                cout << "Choose an option:\n";
                cout << "1. Pick up a wrench\n";
                cout << "2. Pick up a fire extinguisher\n";
                cout << "3. Fist fight the pirate\n";
                cout << "Enter your choice: ";
                cin >> choice;
                cout << "\n"; // Add a blank line after input

                switch (choice)
                {
                case 1:
                    cout << "You picked up a wrench. It is a bit rusty.\n";
                    buff = 4; // Small buff for wrench
                    break;
                case 2:
                    cout << "You picked up a fire extinguisher. It is unwieldy but bulky.\n";
                    buff = 2; // Small buff for fire extinguisher
                    break;
                case 3:
                    cout << "You decided to fist fight the pirate.\n";
                    buff = -2; // Small debuff for fist fighting
                    break;
                default:
                    cout << "Invalid choice. Please try again.\n\n"; // Double newline for clarity
                    continue;
                }
                break;
            } while (true);

            // Trigger narrative text before rolls
            cout << readFromFile("storageroom_roll.txt") << endl;

            // Enemy encounter
            int total = 0;
            for (int i = 0; i < 3; ++i)
            {
                int roll = rand() % 20 + 1 + buff;
                total += roll;
                cout << "Roll " << i + 1 << ": " << roll << "\n";
            }

            if (total >= 25)
            {
                cout << "You successfully defeated the pirate.\n";
            }
            else
            {
                cout << "You defeated the pirate, but the copilot is injured and will require medical assistance.\n";
                player.getCopilot().injured = true;
            }

            pirateEncountered = true; // Mark that the pirate has been encountered
        }
        else
        {
            cout << readFromFile("storageroom_entry_no_pirate.txt") << endl;
        }

        // After encounter options
        int choice;
        do {
            cout << "Choose an option:\n";
            cout << "1. Search the room\n";
            cout << "2. Leave the room\n";
            cout << "Enter your choice: ";
            cin >> choice;
            cout << "\n"; // Add a blank line after input

            switch (choice)
            {
            case 1:
                cout << "You found a collector coil!\n";
                player.setPuzzlePiece(true);
                break;
            case 2:
                cout << readFromFile("storageroom_leave.txt") << endl;
                return;
            default:
                cout << "Invalid choice. Please try again.\n\n"; // Double newline for clarity
            }
        } while (choice != 2);
    }
};

int main()
{
    srand(static_cast<unsigned int>(time(0))); // Seed the random number generator

    Player player;
    StorageRoom storageRoom;

    // Example of setting player's copilot status to FOUND
    player.getCopilot().obtained = true;

    // Player enters the storage room
    storageRoom.enter(player);

    return 0;
}
