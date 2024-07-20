#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

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
void waitForKeyPress()
{
    cout << "Press any key to roll the dice...\n";
    cin.ignore();
    cin.get();
}

//enum for location - Thatcher
enum location {ENGINE_ROOM, HALLWAY, COCKPIT, STORAGE, MEDICAL_BAY, SLEEPING_QUARTERS};

//Class for player - Thatcher
class Player {
    public:
        //Constructor
        Player(bool key = false, bool enginePiece = false, location playerLocation = HALLWAY) {
            key = key;
            enginePiece = enginePiece;
            playerLocation = playerLocation;
        }

        //return value of key variable
        bool get_key() {
            return key;
        }

        //change value of key variable
        void set_key(bool val) {
            key = val;
        }

        //return value of engine piece variable
        bool get_enginePiece() {
            return enginePiece;
        }

        //change value of engine piece variable
        void set_enginePiece(bool val) {
            enginePiece = val;
        }

        //return value of player location variable
        location get_location() {
            return playerLocation;
        }

        //change value of player location variable
        void set_location(location val) {
            playerLocation = val;
        }
    private:
        bool key;
        bool enginePiece;
        location playerLocation;
};

//Class for Hallway - Thatcher
class Hallway {
	public:

        //output movement options for the player and get choice
		void move() {
            cout << "Choose an option:\n";
            cout << "A. Go to Cockpit\n";
            cout << "B. Go to Sleeping Quarters\n";
            cout << "C. Go to Medical Bay\n";
            cout << "D. Go to Storage Room\n";
            cout << "E. Go to Engine Room\n";

            cout << "\nWhere would you like to go?: ";
            cin >> choice;
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
        // Function to handle entering the engine room
        void enter(Copilot &copilot, Player &player) //added arguments as values from these classes should be checked
        {
            cout << readFromFile("engineroom_entry.txt") << endl;

            int choice;
            do {
                cout << "Choose an option:\n";
                cout << "1. Look at the engine\n";
                cout << "2. Leave the room\n";
                cout << "Enter your choice: ";
                cin >> choice;
                cout << "\n"; // Add a blank line after input

                switch (choice)
                {
                case 1:
                    lookAtEngine();
                    break;
                case 2:
                    cout << readFromFile("engineroom_leave.txt") << endl;
                    return;
                default:
                    cout << "Invalid choice. Please try again.\n\n"; // Double newline for clarity
                }
            } while (choice != 2);
        }

    private:
        bool enginePiece = false; // Assuming initially player doesn't have engine piece

        // Function to handle looking at the engine
        void lookAtEngine()
        {
            cout << readFromFile("engineroom_lookatengine.txt") << endl;

            int choice;
            do {
                cout << "\n"; // Add a blank line
                cout << "Choose an option:\n";
                cout << "1. Turn on the Engine\n";
                cout << "2. Step Away from the engine\n";
                cout << "Enter your choice: ";
                cin >> choice;
                cout << "\n"; // Add a blank line after input

                switch (choice)
                {
                case 1:
                    if (!enginePiece)
                    {
                        cout << "\n"; // Add a blank line
                        cout << readFromFile("engineroom_engineoff.txt") << endl;
                    }
                    else
                    {
                        cout << "\n"; // Add a blank line
                        cout << readFromFile("engineroom_engineon.txt") << endl;
                        engineRunningOptions();
                    }
                    break;
                case 2:
                    cout << "\n"; // Add a blank line
                    cout << readFromFile("engineroom_stepaway.txt") << endl;
                    return;
                default:
                    cout << "Invalid choice. Please try again.\n\n"; // Double newline for clarity
                }
            } while (true);
        }

        // Function to handle options when the engine is running
        void engineRunningOptions()
        {
            cout << readFromFile("engineroom_enginerunning.txt") << endl;

            int choice;
            do {
                cout << "Choose an option:\n";
                cout << "1. Step Away from the engine\n";
                cout << "Enter your choice: ";
                cin >> choice;
                cout << "\n"; // Add a blank line after input

                switch (choice)
                {
                case 1:
                    return;
                default:
                    cout << "Invalid choice. Please try again.\n\n"; // Double newline for clarity
                }
            } while (true);
        }
};


//Class for Cockpit - Thatcher
class Cockpit {
    public:
        void enter(Copilot &copilot, EngineRoom &engineRoom, Player &player) {
            cout << "In the cockpit" << endl;
        }


    private:

};

class SleepingQuarters {
    public:
        void enter(Copilot &copilot, EngineRoom &engineRoom, Player &player) {
            cout << "In the sleeping quarters" << endl;
        }

    private:
};

class MedicalBay {
    public:
        void enter(Copilot &copilot, EngineRoom &engineRoom, Player &player) {
                cout << "In the medical bay" << endl;
            }

    private:
};

class StorageRoom {
    public:
        void enter(Copilot &copilot, EngineRoom &engineRoom, Player &player) {
            cout << "In the storage room" << endl;
        }

    private:
};