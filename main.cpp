// Matin amirpanah ------->40212358003
// Nima makhmali  -------->40212358035
// This project creat for FOP finall project

//libraries
#include <iostream>
#include <stdlib.h>
#include <ctime>

//defines
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

// structs
struct enemyStruct
{
    char c = '*';
    size_t size;
    size_t heal; 
};

struct spaceShipStruct
{
    char c = '*';
    char shot = '\'';
    size_t heal;
};

// function declaration
void horizontalDraw();
void GrandDraw();

// main function
int main() 
{
    
    size_t mapSize = 15;


    int condition[mapSize][mapSize];
    spaceShipStruct spaceShip;
    enemyStruct enemy;
    enemyStruct Dart{ '*' , 1 , 1};
    enemyStruct Striker{ '*' , 2 ,2};
    enemyStruct Wraith{ '*' , 3 , 4};
    enemyStruct Banshee{ '*' , 4 , 6};
    

    return 0;
}

// function definition
void horizontalDraw()
{

}

void GrandDraw()
{

}