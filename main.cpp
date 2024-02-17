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
#include <vector>

/// defines

// color define
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


// arrow ascii codes
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77

using namespace std;

/// enums
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
    char shoot = '^';// shot default character
    size_t heal; // space ship's health
    unsigned int x;
};

struct grandStruct
{
    unsigned int size;
    enemyStruct enemy;
    spaceShipStruct spaceShip;
    vector<vector <int>> map; 

};
/// function declaration
// Preliminary function

bool save(grandStruct grand);
bool load(grandStruct &grand);

// drawing grand functions
void horizontalLineDraw(size_t);
void grandDraw(grandStruct);

// move and shoot functions
void move(grandStruct grand);
void shoot(grandStruct grand);

//menu functions
void pauseMenu();
void startMenu(grandStruct &grand);

/// main function
int main() 
{
    srand(time(NULL));

    grandStruct grand;
    grand.size = 15;
    enemyStruct typesOfEnemys[4] =
    {
        {"Dart" , '*' , 1 , 1},
        {"Striker" ,'*' , 2 ,2},
        {"Wraith", '*' , 3 , 4},
        {"Banshee", '*' , 4 , 6},
    };

    for (size_t i = 0; i < grand.size; i++)
    {
        for (size_t j = 0; j < grand.size+1; j++)
        {
            grand.map[i][j] = Null;
        }
    }
    startMenu(grand);
    grandDraw(grand);
    //spaceShip();
	system("pause");
    return 0;
}

/// function definition
bool save(grandStruct grand)
{

    fstream saveFile("SaveFile.bin", ios::binary | ios::trunc);
    if(saveFile.write((char *) &grand , sizeof(grand)))
    {
    	saveFile << flush;
    	return true;
	}
    else
        return false;
}

void startMenu(grandStruct &grand)
{
	int choice;
	bool gameStarted = false;
        cout << "======== Menu ========" << endl;
        cout << "1. Continue Game" << endl;
        cout << "2. New Game" << endl;
        cout << "3. Game Settings" << endl;
        cout << "4. Quit Game" << endl;
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
                grandDraw(grand);
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

void horizontalLineDraw(size_t size)
{
    for (size_t i = 0; i < size; i++)
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
}

void move(grandStruct grand)
{
    char m;
    m = getchar();
    bool flag = true;
    do 
    {
        switch (m) 
        {
        case RIGHT:
            grand.map[grand.spaceShip.x][grand.size - 1] = Null;
            grand.spaceShip.x += 1;
            grand.map[grand.spaceShip.x][grand.size - 1] = SpaceShip;
            flag = true;
            shoot(grand);
            break;
        case LEFT:
            grand.map[grand.spaceShip.x][grand.size - 1] = Null;
            grand.spaceShip.x -= 1;
            grand.map[grand.spaceShip.x][grand.size - 1] = SpaceShip;
            shoot(grand);
            flag = true;
            break;
        case DOWN:
            shoot(grand);
            break;
        default:
            flag = false;
            break;
        }
    }while (flag == false);
    
}