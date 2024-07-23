#include "classes.cpp"
using namespace std;


int main() {

    Copilot copilot; 
    Cockpit cockpit;
    SleepingQuarters sleepingQuarters;
    MedicalBay medicalBay;
    StorageRoom storageRoom;
    EngineRoom engineRoom;
    Hallway hallway;
    Player player;

    srand(static_cast<unsigned int>(time(0))); // Seed the random number generator

    // Display welcome message and introduction
    cout << "Welcome to the Untitled RPG game!\n";
    cout << readFromFile("introduction.txt");

    // Start the game in the Medical Bay
    medicalBay.enter(copilot, engineRoom, player);

    //test cases - Thatcher
    engineRoom.on = true;
    copilot.injured = false;
    copilot.obtained = true;
    player.set_key(true);

    // Main game loop
    while (true)
    {
        hallway.move();

        // Handle room entry based on player's choice
        switch (hallway.getChoice())
        {
            case 'A':
            case 'a':
                player.set_location(COCKPIT);
                cockpit.enter(copilot, engineRoom, player);
                break;
            case 'B':
            case 'b':
                player.set_location(SLEEPING_QUARTERS);
                sleepingQuarters.enter(copilot, engineRoom, player);
                break;
            case 'C':
            case 'c':
                player.set_location(MEDICAL_BAY);
                medicalBay.enter(copilot, engineRoom, player);
                break;
            case 'D':
            case 'd':
                player.set_location(STORAGE);
                storageRoom.enter(copilot, engineRoom, player);
                break;
            case 'E':
            case 'e':
                player.set_location(ENGINE_ROOM);
                engineRoom.enter(copilot, player);
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }
    return 0;
}
