#include "classes.cpp"
using namespace std;


int main() {


    // set working directory to text folder to read narrative
    char* dir = "text";
    char buffer[1024];

    if (_chdir(dir) == -1) {
        cout << "Path not changed\n";
    } else {
        _getcwd(buffer, 1024);
        cout << buffer << endl;
    }

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
    medicalBay.enter(copilot, player);

    // Main game loop
    while (true)
    {
        hallway.move();

        // Handle room entry based on player's choice
        switch (hallway.getChoice())
        {
            case '1':
                system("cls"); 
                player.set_location(COCKPIT);
                cockpit.enter(copilot, engineRoom);
                break;
            case '2':
                system("cls"); 
                player.set_location(SLEEPING_QUARTERS);
                sleepingQuarters.enter(copilot);
                break;
            case '3':
                system("cls"); 
                player.set_location(MEDICAL_BAY);
                medicalBay.enter(copilot, player);
                break;
            case '4':
                system("cls"); 
                player.set_location(STORAGE);
                storageRoom.enter(player, copilot);
                break;
            case '5':
                system("cls"); 
                player.set_location(ENGINE_ROOM);
                engineRoom.enter(player);
                break;
            default:
                system("cls"); 
                cout << "Invalid choice. Please try again.\n";
        }
    }
    return 0;
}
