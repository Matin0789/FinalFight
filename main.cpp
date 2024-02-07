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
    char c = '*';// space ship default charater
    char shot = '\'';// shot default character
    size_t heal; // space ship's health
};

/// function declaration
// Preliminary function
void gameRun(size_t mapSize,spaceShipStruct spaceShip,);
void save(size_t mapSize, int *map, enemyStruct enemy, spaceShipStruct spaceShip);

// menu functions
void menu();

// drawing grand functions
void horizontalDraw();
void grandDraw();

// move functions
void move();

/// main function
int main() 
{
    srand(time(NULL));
    do
    {
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

        gameRun();
        Condition map[mapSize][mapSize];

        while(spaceShip.heal > 0)
        {
            grandDraw();
            move();
        }

    } while (/* condition */);
    
    
    
    
    return 0;
}

/// function definition
void gameRun()
{

}

void save()
{

}

void menu()
{

}



void horizontalDraw()
{

}

void grandDraw()
{
    

}

void move()
{
    int position = 2; 
    int direction = 1; 

    while (true) {
        system("cls"); 
        GrandDraw();

        char move;
        cout << "Please enter 'l' to move left, 'r' to move right, or 'q' to quit: ";
        cin >> move;

        switch (move) {

                cout << "Invalid input! Please try again." << endl;
        }

      
        system("cls"); 
      

        cout << "|";
        for (int i = 0; i < 5; i++) {
            if (i == position) {
                cout << " # ";
            }
            else {
                cout << "   ";
            }

            cout << "|";
        }

        cout << endl;
        cout << " --------------------" << endl;
    }
}