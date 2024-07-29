# Disaster on Dysnomia
Disaster on Dysnomia is a CLI text-based adventure game. You wake up on a ship in the medical bay, unsure of what has just occurred. No one else is around you, and you need to find out what is going on.

## How to Play
Download the game files folder
- This folder includes the source code and the necessary text files

- Compile the code
  - Open the Game Files folder
  - Right-click inside the folder, select open in terminal if available
      - If unavailable. open a terminal separately and navigate to the Game Files folder
  - In the terminal copy or type:
    ```c++
    g++ -o Dysnomia "source code/main.cpp"
    ```
  - You will now have an EXE in the Game Files folder labeled Dysnomia
  - If it does not compile, check your installation of C++
  - [Here](https://www.freecodecamp.org/news/how-to-install-c-and-cpp-compiler-on-windows/) is a link to a helpful guide on installing C++

## Game Development
### Classes
- Player
  - Tracks the player's items and location
- Copilot
  - Tracks the copilot's status
- EngineRoom
  - Tracks the engine room's status
  - Allows the player to enter and interact with items in the engine room
- Cockpit
  - Tracks the cockpit's status
  - Allows the player to enter and interact with items in the cockpit
- MedicalBay
  - Allows the player to enter and interact with items in the medical bay
- StorageRoom
  - Allows the player to enter and interact with items in the storage room
- SleepingQuarters
  - Allows the player to enter and interact with items in the sleeping quarters
- Hallway
  - ALlows the player to move between rooms

### Functions
- waitForKeyPress(string message = "", bool clear = false)
  - This functions allows the game to pause and the player to press a key to continue an action
  - Used for combat
  - Has optional fields to clear the screen after key press and display a message before key press
- getchar()
  - validates user input, allows only single characters to be read
- map()
  - Outputs a map onto the screen which shows where the player is on the ship
- readFromFile()
  - Reads text from the text files and outputs them into the CLI
 
### Further Development
Game Features
- Could add health for player and copilot
- Map could be a class and could add more functionality
- Game loop itself may be a class and simplify the main function call
- Add weapons and more complex combat
- Add more rooms
- Add more characters
- Use a GUI rather than the CLI
