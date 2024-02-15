/* 
This project creat for FOP finall project winter1402
authors:
    Matin amirpanah, Student No:40212358003
    Nima makhmali, Student No:40212358035
*/


/// libraries
#include <iostream> // Interaction with terminal 
#include <stdlib.h> // Interaction with the operating system
#include <ctime> // Get system clock for Primary seed of rand
#include <fstream> // Interaction with file

/// defines
#define Reset   "\033[0m"
#define Black   "\033[30m"
#define Red     "\033[31m"
#define Green   "\033[32m"
#define Yellow  "\033[33m"
#define Blue    "\033[34m"
#define Magenta "\033[35m"
#define Cyan    "\033[36m"
#define White   "\033[37m"
#define BoldBlack   "\033[1m\033[30m"
#define BoldRed     "\033[1m\033[31m"
#define BoldGreen   "\033[1m\033[32m"
#define BoldYellow  "\033[1m\033[33m"
#define BoldBlue    "\033[1m\033[34m"
#define BoldMagenta "\033[1m\033[35m"
#define BoldCyan    "\033[1m\033[36m"
#define BoldWhite   "\033[1m\033[37m"      

#define BackgroundBlack     "\u001b[40m"
#define BackgroundRed       "\u001b[41m"
#define BackgroundGreen     "\u001b[42m"
#define BackgroundYellow    "\u001b[43m"
#define BackgroundBlue      "\u001b[44m"
#define BackgroundMagenta   "\u001b[45m"
#define BackgroundCyan      "\u001b[46m"
#define BackgroundWhite     "\u001b[47m"

#define Bold        "\u001b[1m"
#define Underline   "\u001b[4m"
#define Reversed    "\u001b[7m"

using namespace std;

///enums
enum Condition
{
    Null,
    Enemy,
    SpaceShip
};

/// structs
struct enemyStruct
{
    char name[8];// enemy name
    char c = '*';// enemy default character
    size_t size;// enemy size in map
    size_t heal; // enemy's health
};

struct spaceShipStruct
{
    char c = '#';// space ship default charater
    char shot = '^';// shot default character
    size_t heal; // space ship's health
};

/// function declaration
// Preliminary function
void save(Condition Map[]);

// menu functions
void menu(size_t mapSize, Condition Map[], spaceShipStruct spaceShip, enemyStruct enemy);

// drawing grand functions
void horizontalLineDraw(size_t mapSize);
void grandDraw(size_t mapSize, Condition Map[], spaceShipStruct spaceShip, enemyStruct enemy);

// move functions
void move();

// spaceship  functions
void spaceShip(size_t mapSize, Condition Map[], spaceShipStruct spaceShip, enemyStruct enemy);
/// main function
int main() 
{
    srand(time(NULL));

    size_t mapSize = 15;
    spaceShipStruct spaceShip;
    enemyStruct enemy;
    enemyStruct typesOfEnemys[4] =
    {
        {"Dart" , '*' , 1 , 1},
        {"Striker" ,'*' , 2 ,2},
        {"Wraith", '*' , 3 , 4},
        {"Banshee", '*' , 4 , 6},
    };


    
    Condition Map[mapSize][mapSize];
    for (size_t i = 0; i < mapSize; i++)
    {
        for (size_t j = 0; j < mapSize+1; j++)
        {
            Map[i][j] = Null;
        
        }
    }
    menu(mapSize, (Condition *)Map, spaceShip, enemy);
    grandDraw(mapSize, (Condition *)Map, spaceShip, enemy);
	system("pause");
    return 0;
}

/// function definition
void save(Condition Map[])
{

}

void menu(size_t mapSize, Condition Map[], spaceShipStruct spaceShip, enemyStruct enemy)
{
	int choice;
	bool gameStarted = false;
        cout << "======== Menu ========" << endl;
        cout << "1. Start Game" << endl;
        cout << "2. Pause Game" << endl;
        cout << "3. Quit Game" << endl;
        cout << "=======================" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
  

    // ...
    switch (choice) {
        case 1:
            if (!gameStarted) {
                // start
                cout << "Game started!" << endl;
                gameStarted = true;
                grandDraw(mapSize, (Condition *)Map, spaceShip, enemy);
            } else {
                cout << "Game is already started!" << endl;
            }
            break;
        case 2:
            if (gameStarted) {
                // stop
                cout << "Game paused!" << endl;
                gameStarted = false;
            } else {
                cout << "No game is currently running!" << endl;
            }
            break;
        case 3:
            // Exit
            cout << "Game exited!" << endl;
            return; // توقف اجرای تابع بعد از خروج از بازی
        default:
            cout << "Invalid choice! Please try again." << endl;
            break;
    }
    // ...


        cout << endl;
}

    




void horizontalLineDraw(size_t mapSize)
{
    for (size_t i = 0; i < mapSize; i++)
    {
        for (size_t j = 0; j < 4; j++)
        {
            cout << "-";
        }
    }
    cout << endl;
}

void grandDraw(size_t mapSize, Condition Map[], spaceShipStruct spaceShip, enemyStruct enemy)
{

    for (size_t i = 0; i < mapSize; i++)
    {
        horizontalLineDraw(mapSize);
        for (size_t j = 0; j < mapSize; j++)
        {
            cout << '|';
            switch (*((Map+i*mapSize) + j))
            {
            case Enemy:
                cout << ' ' << enemy.c << ' ';
                break;
            case SpaceShip:
	
                cout << ' ' << spaceShip.c << ' ';
                break;
            default:
                cout << "   ";
                break;
            }
        }
        cout << '|';
        cout << endl;
    }
    horizontalLineDraw(mapSize);
}

void SpaceShip(size_t mapSize, Condition Map[][15], spaceShipStruct& spaceShip)
{
    size_t position = mapSize / 2;
    Map[mapSize - 1][position] = SpaceShip;
}

void move(size_t mapSize, Condition Map[][15], spaceShipStruct& spaceShip)
{
    size_t position;
    for (size_t i = mapSize - 1; i > 0; i--)
    {
        for (size_t j = 0; j < mapSize; j++)
        {
            if (Map[i][j] == SpaceShip)
            {
                position = j;
                Map[i][j] = Null;
                Map[i - 1][j] = SpaceShip;
            }
        }
    }

    // Handle user input for spaceship movement
    char input;
    cout << "Enter L to move left or R to move right: ";
    cin >> input;

    if (input == 'L' || input == 'l')
    {
        if (position - 1 >= 0)
        {
            Map[mapSize - 1][position - 1] = SpaceShip;
        }
        else
        {
            cout << "Invalid move! Spaceship cannot go beyond the limits." << endl;
        }
    }
    else if (input == 'R' || input == 'r')
    {
        if (position + 1 < mapSize)
        {
            Map[mapSize - 1][position + 1] = SpaceShip;
        }
        else
        {
            cout << "Invalid move! Spaceship cannot go beyond the limits." << endl;
        }
    }
}