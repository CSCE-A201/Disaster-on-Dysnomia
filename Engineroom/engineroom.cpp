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

// Class for the Engine Room
class EngineRoom
{
public:
    // Function to handle entering the engine room
    void enter()
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

int main()
{
    srand(static_cast<unsigned int>(time(0))); // Seed the random number generator

    EngineRoom engineRoom;

    // Player enters the engine room
    engineRoom.enter();

    return 0;
}

