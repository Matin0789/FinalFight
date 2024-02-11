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
    Null,// The position is empty
    Enemy,// the position is occupied by the enemy
    SpaceShip// the position is occupied by our spaceship
};



/// structs
struct enemyStruct
{
    char name[8];// enemy name
    char c = '*';// enemy default character
    unsigned int size;// enemy size in map
    unsigned int heal; // enemy's health
};

struct spaceShipStruct
{
    char c = '*';// space ship default charater
    char shot = '\'';// shot default character
    unsigned int heal; // space ship's health
};

struct grandStruct
{
    unsigned int size;
    enemyStruct enemy;
    spaceShipStruct spaceShip;
    Condition map = new Condition [size*size];
    
};

/// function declaration
// Preliminary function
bool save(grandStruct grand);
bool load(grandStruct &grand);

// menu functions
void pauseMenu();
void startMenu();

// drawing grand functions
void horizontalLineDraw(unsigned int mapSize);
void grandDraw(grandStruct grand);

// move functions
void move();

/// main function
int main() 
{
    srand(time(NULL));

    unsigned int mapSize = 15;
    grandStruct grand;
    enemyStruct typesOfEnemys[4] =
    {
        {"Dart" , '*' , 1 , 1},
        {"Striker" ,'*' , 2 ,2},
        {"Wraith", '*' , 3 , 4},
        {"Banshee", '*' , 4 , 6},
    };

    for (size_t i = 0; i < grand.size; i++)
    {
        for (size_t j = 0; j < mapSize; j++)
        {
            grand.map[i][j] = Null;
        }
    }

    grandDraw(grand);
    system("pause");
    return 0;
}

/// function definition
bool save(grandStruct grand)
{
    fstream saveFile("SaveFile.bin", ios::out | ios::binary | ios::trunc);
    if (!saveFile)
        return false;
    
    if(saveFile.write((char *) &grand , sizeof(grand)))
    {
        saveFile.close();
        return true;
    }
    else
    {
        saveFile.close();
        return false;
    }
        
}

bool load(grandStruct &grand)
{
    fstream saveFile("SaveFile.bin", ios::in | ios::binary);
    if (!saveFile)
        return false;
    unsigned int size;
    saveFile.read(reinterpret_cast<char*> (&size), sizeof(unsigned int));
    saveFile.close();
    saveFile.open("SaveFile.bin", ios::in | ios::binary);
    if (!saveFile)
        return false;
    saveFile.read(reinterpret_cast<char*> (&grand), sizeof(unsigned int)+sizeof(enemyStruct)+sizeof(spaceShipStruct)+(sizeof(Condition)*size*size));
    

}

void horizontalLineDraw(unsigned int mapSize)
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

void grandDraw(grandStruct grand)
{
    for (size_t i = 0; i < grand.size; i++)
    {
        horizontalLineDraw(grand.size);
        for (size_t j = 0; j < grand.size; j++)
        {
            cout << '|';
            switch (grand.map[i][j])
            {
            case Enemy:
                cout << ' ' << grand.enemy.c << ' ';
                break;
            case SpaceShip:
                cout << ' ' << grand.spaceShip.c << ' ';
                break;
            default:
                cout << "   ";
                break;
            }
        }
        cout << '|';
        cout << endl;
    }
    horizontalLineDraw(grand.size);
    save(grand);
}

void move()
{

}