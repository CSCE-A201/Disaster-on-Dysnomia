#ifndef CLASSES_H
#define CLASSES_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <stdio.h>
#include <direct.h> 
#include <limits>
#include <conio.h>
using namespace std;

// Function to validate input
char get_char() {
    char ch;

    while (!(cin >> ch) || cin.peek() != '\n') {
        cin.clear(); // Clear error flags
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
        cout << "Invalid input. Please enter a valid option: ";
    }

    return ch;
}

// Function to read text from a file
// Takes a filename as an argument and returns the file's content as a string
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

// Function to wait for any key press
// Pauses the game until the player presses a key
// An optional variable to add a prompt
// An optional variable to clear the screen after key press
void waitForKeyPress(string msg = "", bool clear = false)
{
    if (msg != "") {
        cout << msg << endl;
    }
    getch();

    if (clear) {
        system("cls");
    }
}


//enum for location - Thatcher
enum location {ENGINE_ROOM, HALLWAY, COCKPIT, STORAGE, MEDICAL_BAY, SLEEPING_QUARTERS};

//Class for player - Thatcher
class Player {
public:
    //Constructor
    Player(bool cabinetKey = false, bool enginePiece = false, location playerLocation = HALLWAY) {
        cabinetKey = cabinetKey;
        enginePiece = enginePiece;
        playerLocation = playerLocation;
    }

    // Return value of cabinet key variable
    bool hasCabinetKey() const {
        return cabinetKey;
    }

    // Change value of cabinet key variable
    void setCabinetKey(bool val) {
        cabinetKey = val;
    }

    //return value of engine piece variable
    bool get_enginePiece() const {
        return enginePiece;
    }

    //change value of engine piece variable
    void set_enginePiece(bool val) {
        enginePiece = val;
    }

    //return value of player location variable
    location get_location() const {
        return playerLocation;
    }

    //change value of player location variable
    void set_location(location val) {
        playerLocation = val;
    }
private:
    bool cabinetKey = false;
    bool enginePiece = false;
    location playerLocation;
};

// Function to display map
void map(Player &player) {

    char cockpit, medical, storage, sleeping, hallway, engine;
    cockpit = medical = storage = sleeping = hallway = engine = '-';

    if (player.get_location() == MEDICAL_BAY) {
        medical = 'X';
        cockpit = storage = sleeping = hallway = engine = '-';
    } else if (player.get_location() == ENGINE_ROOM) {
        engine = 'X';
        cockpit = medical = storage = sleeping = hallway = '-';
    } else if (player.get_location() == COCKPIT) {
        cockpit = 'X';
        medical = storage = sleeping = hallway = engine = '-';
    } else if (player.get_location() == STORAGE) {
        storage = 'X';
        cockpit = medical = sleeping = hallway = engine = '-';
    } else if (player.get_location() == SLEEPING_QUARTERS) {
        sleeping = 'X';
        cockpit = medical = storage = hallway = engine = '-';
    } else {
        hallway = 'X';
        cockpit = medical = storage = sleeping = engine = '-';
    }
    
    cout << endl;
    cout << "         |---------|         \n";
    cout << "         | Cockpit |         \n";
    cout << "         |    " << cockpit << "    |\n";
    cout << "|--------|---------|----------|\n";
    cout << "|        |         |  Medical |\n";
    cout << "|        |         |     " << medical << "    |\n";
    cout << "|Storage | Hallway |          |\n";
    cout << "|    " << storage << "   |    " << hallway << "    |          |\n";
    cout << "|        |         |----------|\n";
    cout << "|        |         | Sleeping |\n";
    cout << "|        |         |     " << sleeping << "    |\n";
    cout << "|--------|---------|----------|\n";
    cout << "         | Engine  |         \n";
    cout << "         |    " << engine << "    |\n";
    cout << "         |---------|         \n";
    cout << endl;
}

//Class for Hallway - Thatcher
class Hallway {
	public:

        //output movement options for the player and get choice
		void move(Player &player) {
            player.set_location(HALLWAY);
            map(player);
            cout << endl;
            cout << "\nWhere would you like to go?: \n";
            cout << "1. Go to Cockpit\n";
            cout << "2. Go to Sleeping Quarters\n";
            cout << "3. Go to Medical Bay\n";
            cout << "4. Go to Storage Room\n";
            cout << "5. Go to Engine Room\n";
            cout << "Enter your choice: ";
            
            choice = get_char();
        };

        //return the value of choice
        char getChoice() const {
            return choice;
        };
	
	private:
		char choice;
};


//Class for copilot - Jared
class Copilot {
public:
    bool obtained; // Indicates if the copilot has been found
    bool injured;  // Indicates if the copilot is injured

    // Constructor to initialize copilot state
    Copilot() : obtained(false), injured(false) {}
};

// Class for the Engine Room - Austin
class EngineRoom {
public:
    bool on;

    EngineRoom() : on(false) {};

    // Function to handle entering the engine room
    void enter(Player &player) //added arguments as values from these classes should be checked
    {
        player.set_location(ENGINE_ROOM);
        cout << readFromFile("engineroom_entry.txt") << endl;

        char choice;
        do {
            map(player);
            cout << "Choose an option:\n";
            cout << "1. Look at the engine\n";
            cout << "2. Leave the room\n";
            cout << "Enter your choice: ";
            choice = get_char();
            cout << "\n"; // Add a blank line after input

            switch (choice)
            {
            case '1':
                system("cls"); 
                lookAtEngine(player);
                break;
            case '2':
                system("cls"); 
                cout << readFromFile("engineroom_leave.txt") << endl;
                return;
            default:
                system("cls"); 
                cout << "Invalid choice. Please try again.\n\n"; // Double newline for clarity
            }
        } while (choice != '2');
    }

private:
    // Function to handle looking at the engine
    void lookAtEngine(Player &player)
    {
        cout << readFromFile("engineroom_lookatengine.txt") << endl;

        char choice;
        do {
            cout << "\n"; // Add a blank line
            cout << "Choose an option:\n";
            cout << "1. Turn on the Engine\n";
            cout << "2. Step Away from the engine\n";
            cout << "Enter your choice: ";
            choice = get_char();
            cout << "\n"; // Add a blank line after input

            switch (choice)
            {
            case '1':
                if (!player.get_enginePiece())
                {
                    system("cls"); 
                    cout << "\n"; // Add a blank line
                    cout << readFromFile("engineroom_engineoff.txt") << endl;
                }
                else
                {
                    system("cls"); 
                    cout << "\n"; // Add a blank line
                    cout << readFromFile("engineroom_engineon.txt") << endl;
                    on = true; // track that engine is on
                    engineRunningOptions();
                }
                break;
            case '2':
                system("cls"); 
                cout << "\n"; // Add a blank line
                cout << readFromFile("engineroom_stepaway.txt") << endl;
                return;
            default:
                system("cls"); 
                cout << "Invalid choice. Please try again.\n\n"; // Double newline for clarity
            }
        } while (true);
    }

    // Function to handle options when the engine is running
    void engineRunningOptions()
    {
        cout << readFromFile("engineroom_enginerunning.txt") << endl;

        char choice;
        do {
            cout << "Choose an option:\n";
            cout << "1. Step Away from the engine\n";
            cout << "Enter your choice: ";
            choice = get_char();
            cout << "\n"; // Add a blank line after input

            switch (choice)
            {
            case '1':
                system("cls"); 
                return;
            default:
                system("cls"); 
                cout << "Invalid choice. Please try again.\n\n"; // Double newline for clarity
            }
        } while (true);
    }
};

// Class for Sleeping Quarters - Jared
class SleepingQuarters {
public:
    void enter(Copilot &copilot, Player &player) {
        player.set_location(SLEEPING_QUARTERS);
        cout << readFromFile("sleeping_quarters_intro.txt") << endl;

        char choice;
        do {
            displayChoices(player);
            choice = get_char();
            cout << endl;

            handleChoice(choice, copilot);
        } while (choice != '4'); // Continue until the player chooses to leave the room
    }

private:
    // Display options for sleeping quarters
    void displayChoices(Player &player) const {
        map(player);
        cout << "You are in the Sleeping Quarters. What would you like to do?" << endl;
        cout << "1. Search the room" << endl;
        cout << "2. Search the lockers" << endl;
        cout << "3. Search scattered belongings" << endl;
        cout << "4. Enter Hallway" << endl;
        cout << "Enter your choice: ";
    }
    
    // Handle options within sleeping quarters
    void handleChoice(int choice, Copilot &copilot) {
        switch (choice) {
            case '1':
                system("cls"); 
                searchRoom(copilot);
                break;
            case '2':
                system("cls"); 
                searchLockers();
                break;
            case '3':
                system("cls"); 
                searchBelongings();
                break;
            case '4':
                system("cls"); 
                cout << "You leave the sleeping quarters and enter into the main hallway." << endl;
                break;
            default:
                system("cls"); 
                cout << "Invalid choice. Please choose a valid option." << endl;
                break;
        }
    }

    // Search room function for copilot
    void searchRoom(Copilot &copilot) {
        system("cls"); 
        cout << readFromFile("sq_search.txt") << endl;

        if (!copilot.obtained) {
            cout << readFromFile("sq_found_copilot.txt") << endl;
            copilot.obtained = true; // The copilot is now found
            displayDialogOptions();
            system("cls");
        } else {
            cout << readFromFile("sq_no_copilot.txt") << endl; // If player returns and copilot is already found
        }
    }

    void searchLockers() const {
        system("cls"); 
        cout << readFromFile("sq_lockers.txt") << endl;
    }

    void searchBelongings() {
        system("cls"); 
        cout << readFromFile("sq_belongings.txt") << endl;
    }

    // Dialog options with copilot
    void displayDialogOptions() const {
        char dialogChoice;
        do {
            cout << "What would you like to ask?" << endl;
            cout << "1. What happened to the ship?" << endl;
            cout << "2. Where did everybody go?" << endl;
            cout << "3. What should we do next?" << endl;
            cout << "4. How did you end up in the sleeping quarters?" << endl;
            cout << "5. Leave the conversation" << endl;
            cout << "Enter your choice: ";
            dialogChoice = get_char();
            cout << endl;

            if (dialogChoice != '5') {
                handleDialogChoice(dialogChoice);
            }
        } while (dialogChoice != '5'); // Continue until the player chooses to leave
    }

    void handleDialogChoice(char choice) const {
        switch (choice) {
            case '1':
                system("cls"); 
                cout << readFromFile("sq_dialog_ship.txt") << endl;
                break;
            case '2':
                system("cls"); 
                cout << readFromFile("sq_dialog_everybody.txt") << endl;
                break;
            case '3':
                system("cls"); 
                cout << readFromFile("sq_dialog_next.txt") << endl;
                break;
            case '4':
                system("cls"); 
                cout << readFromFile("sq_dialog_copilot_background.txt") << endl;
                break;
            default:
                system("cls"); 
                cout << "Invalid choice. Please choose a valid option." << endl;
                break;
        }
    }
};

//Class for Medical Bay - Jared
class MedicalBay
{
public:
    void enter(Copilot &copilot, Player &player)
    {
        player.set_location(MEDICAL_BAY);
        cout << readFromFile("medical_bay.txt") << endl; // intro to medical bay

        char choice;
        do {
            displayChoices(player);
            choice = get_char();
            cout << endl;

            handleChoice(choice, copilot, player);
        } while (choice != '4'); // Continue until the player chooses to enter the hallway
    }

private:
    const int deskCode = 3575; // Code for desk to find key for the cabinet

    void displayChoices(Player &player) const
    {
        map(player);
        cout << "You are in the Medical Bay. What would you like to do?" << endl;
        cout << "1. Look inside the medical cabinets" << endl;
        cout << "2. Inspect the medical equipment" << endl;
        cout << "3. Inspect office desk" << endl;
        cout << "4. Enter Hallway" << endl;
        cout << "Enter your choice: ";
    }

    void handleChoice(char choice, Copilot &copilot, Player &player)
    {
        switch (choice)
        {
            case '1':
                system("cls"); 
                handleCabinet(copilot, player); // medical supplies for copilot, needs key
                break;
            case '2':
                system("cls"); 
                cout << readFromFile("mb_equipment_nothing.txt") << endl; // no important gameplay mechanics
                break;
            case '3':
                system("cls"); 
                handleDesk(player); // where key is found, requires code
                break;
            case '4':
                system("cls"); 
                cout << "You leave the medical bay and enter into the main hallway." << endl; // enter hallway
                break;
            default:
                system("cls"); 
                cout << "Invalid choice. Please choose a valid option." << endl;
                break;
        }
    }

    // Function for cabinet
    void handleCabinet(Copilot &copilot, Player &player)
    {
        system("cls"); 
        if (player.hasCabinetKey()) // checks if player has key
        {
            if (copilot.obtained && copilot.injured) // checks if copilot is injured
            {
                system("cls"); 
                cout << readFromFile("mb_cabinet_heal.txt") << endl;
                copilot.injured = false; // Heal the copilot
            }
            else
            {
                system("cls"); 
                cout << readFromFile("mb_cabinet_locked.txt") << endl;
            }
        }
        else
        {
            system("cls"); 
            cout << readFromFile("mb_cabinet_nothing_locked.txt") << endl;
        }
    }

    void handleDesk(Player &player)
    {
        system("cls"); 
        int userCode;
        char knowCode;

        cout << readFromFile("mb_desk.txt") << endl; // Display desk info

        cout << "Do you know the 4-digit code? (Y/N): ";
        knowCode = get_char();
        cout << endl;

        if (knowCode == 'Y' || knowCode == 'y')
        {
            cout << "Enter 4-digit code to unlock the desk drawer: ";
            cin >> userCode;

            if (userCode == deskCode)
            {
                system("cls"); 
                cout << readFromFile("mb_desk_unlock.txt") << endl;
                player.setCabinetKey(true); // Player finds the cabinet key
            }
            else
            {
                system("cls"); 
                cout << "Invalid Code. The desk drawer remains locked.\n" << endl;
            }
        }
        else if (knowCode == 'N' || knowCode == 'n')
        {
            system("cls"); 
            cout << readFromFile("mb_leave_desk.txt") << endl;
        }
        else
        {
            system("cls"); 
            cout << "Invalid Input. Please enter Y or N.\n" << endl;
        }
    }
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

    void enter(Player& player, Copilot& copilot)
    {
        if (!copilot.obtained)
        {   
            system("cls"); 
            cout << "You need to find the copilot first before entering the storage room.\n";
            return;
        }

        player.set_location(STORAGE);

        if (!pirateEncountered)
        {
            system("cls"); 
            cout << readFromFile("storageroom_entry.txt") << endl;
            
            // Choice of weapon
            char choice;
            int buff = 0;
            do {
                map(player);
                cout << "Choose an option:\n";
                cout << "1. Pick up a wrench\n";
                cout << "2. Pick up a fire extinguisher\n";
                cout << "3. Fist fight the pirate\n";
                cout << "Enter your choice: ";
                choice = get_char();
                cout << "\n"; // Add a blank line after input

                switch (choice)
                {
                case '1':
                    system("cls"); 
                    cout << "You picked up a wrench. It is a bit rusty.\n";
                    buff = 4; // Small buff for wrench
                    break;
                case '2':
                    system("cls"); 
                    cout << "You picked up a fire extinguisher. It is unwieldy but bulky.\n";
                    buff = 2; // Small buff for fire extinguisher
                    break;
                case '3':
                    system("cls"); 
                    cout << "You decided to fist fight the pirate.\n";
                    buff = -2; // Small debuff for fist fighting
                    break;
                default:
                    system("cls"); 
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
                waitForKeyPress("Press enter to roll: ");
                cout << "Roll " << i + 1 << ": " << roll << endl;
            }

            cout << endl;

            if (total >= 25)
            {
                cout << "You successfully defeated the pirate.\n";
            }
            else
            {
                cout << "You defeated the pirate, but the copilot is injured and will require medical assistance.\n";
                copilot.injured = true;
            }

            pirateEncountered = true; // Mark that the pirate has been encountered
            waitForKeyPress("Press enter to continue: ", true); // Wait for key press so player can see combat result
        }
        else
        {
            system("cls"); 
            cout << readFromFile("storageroom_entry_no_pirate.txt") << endl;
        }

        // After encounter options
        char choice;
        do {
            system("cls"); 
            map(player);
            cout << "Choose an option:\n";
            cout << "1. Search the room\n";
            cout << "2. Leave the room\n";
            cout << "Enter your choice: ";
            choice = get_char();
            cout << "\n"; // Add a blank line after input

            switch (choice)
            {
            case '1':
                if (player.get_enginePiece()) {
                    system("cls"); 
                    cout << "There is nothing more to find here.\n";
                    waitForKeyPress("Press enter to continue: ", true);
                } else {
                    system("cls"); 
                    cout << "You found a collector coil!\n";
                    waitForKeyPress("Press enter to continue: ", true);
                    player.set_enginePiece(true);
                }
                break;
            case '2':
                system("cls"); 
                cout << readFromFile("storageroom_leave.txt") << endl;
                return;
            default:
                system("cls"); 
                cout << "Invalid choice. Please try again.\n\n"; // Double newline for clarity
            }
        } while (choice != '2');
    }
};

//Class for Cockpit - Thatcher
class Cockpit {
public:
    Cockpit () : unlocked(false) {};

    void enter(Copilot &copilot, EngineRoom &engineRoom, Player &player) {
        if (!copilot.obtained) { //copilot provides key for cockpit
            system("cls"); 
            cout << endl << readFromFile("cockpitLocked.txt");
            return;
        } else {
            player.set_location(COCKPIT);
            if (unlocked) {
                cout << endl << readFromFile("enterCockpit.txt");
            } else {
                cout << endl << readFromFile("cockpitUnlocked.txt");
                unlocked = true; //changed dialogue option after first unlocked
            }
            char choice;
            do {
                map(player);
                cout << "\nChoose an option: \n";
                cout << "1. Look at the control board\n";
                cout << "2. Look out the window\n";
                cout << "3. Return to the Hallway\n";
                cout << "Enter your choice: ";
                choice = get_char();

                switch (choice) {
                    case '1':
                        system("cls"); 
                        controlBoard(copilot, engineRoom);
                        break;
                    case '2':
                        system("cls"); 
                        cout << endl << readFromFile("window.txt");
                        break;
                    case '3':
                        system("cls"); 
                        cout << endl << readFromFile("exitCockpit.txt");
                        return;
                    default:
                        system("cls"); 
                        cout << "Invalid option. Please select a valid choice.\n";
                }

            } while(true);
        }
    }

private:
    void controlBoard(Copilot& copilot, EngineRoom& engineRoom) {
        if (!engineRoom.on && !copilot.obtained) {
            system("cls"); 
            cout << endl << readFromFile("engineOff.txt");
            return;
        } else if (!engineRoom.on && copilot.obtained) {
            system("cls"); 
            cout << endl << readFromFile("noCopilot.txt");
        } else if (engineRoom.on && copilot.injured && copilot.obtained) {
            system("cls"); 
            cout << endl << readFromFile("copilotInjuredCockpit.txt");
        } else if (engineRoom.on && !copilot.injured && copilot.obtained) { //need engine room variable and get function
            system("cls"); 
            char choice;
            cout << endl << readFromFile("engineOn.txt");
            cout << "\nWhat would you like to do:\n";
            cout << "1. Press the button\n";
            cout << "2. Do nothing\n";
            cout << "Enter your choice: ";
            choice = get_char();

            do {
                switch (choice) {
                    case '1':
                        system("cls"); 
                        cout << endl << readFromFile("gameWin.txt");
                        cout << "Press any key to exit.";
                        waitForKeyPress();
                        exit(0);
                        break;
                    case '2':
                        system("cls"); 
                        cout << endl << readFromFile("noWin.txt");
                        return;
                    default:
                        system("cls"); 
                        cout << "Invalid option. Please select a valid choice.\n";
                        break;
                }
            } while(true);
        } 
    }

    bool unlocked = false;
};

#endif