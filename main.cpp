/* 
This project creat for FOP finall project winter1402
authors:
    Matin amirpanah, Student No:40212358003
    Nima makhmali, Student No:40212358035
*/


/// libraries
#include <iostream>    // Interaction with terminal 
#include <stdlib.h>    // Interaction with the operating system
#include <ctime>       // Get system clock for Primary seed of rand
#include <fstream>     // Interaction with file
#include <conio.h>
#include<windows.h>    // for windows
//#include<unistd.h>   // for linux 


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
enum condition
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
    size_t heal = 3;// space ship's health
    unsigned int x;// condition of the spaceship
};

struct grandStruct
{
    unsigned int size;
    enemyStruct enemy;
    spaceShipStruct spaceShip;
    condition **map;
};

struct bollets
{
    int x;// row of the bollets
    int y;// column of the bollets
    char c = '^';// shot default character
};

/// function declaration
// Preliminary function
bool save(grandStruct &grand);
bool load(grandStruct &grand);
void newGame(grandStruct &grand);
// drawing grand functions
void horizontalLineDraw(size_t);
void grandDraw(grandStruct &grand);

// move and shoot functions
void move(grandStruct &grand);
void shoot(grandStruct &grand);

//menu functions
void menu(grandStruct &grand);
void gameSetting();

/// main function
int main() 
{
    srand(time(NULL));
    grandStruct grand;
    enemyStruct typesOfEnemys[4] =
    {
        {"Dart" , '*' , 1 , 1},
        {"Striker" ,'*' , 2 ,2},
        {"Wraith", '*' , 3 , 4},
        {"Banshee", '*' , 4 , 6},
    };
    menu(grand);
    while (grand.spaceShip.heal > 0)
    {
        grandDraw(grand);
        move(grand);
        save(grand);
    }
	system("pause");
    return 0;
}

/// function definition
bool save(grandStruct &grand)
{
    fstream saveFile("SaveFile.bin", ios::binary | ios::trunc | ios::out);
    if(saveFile.write((char *) &grand , sizeof(grand)))
    {
    	saveFile << flush;
    	return true;
	}
    else
        return false;
}

bool load(grandStruct &grand)
{
    unsigned int mapSize;
    fstream loadFile("SaveFile.bin", ios::binary | ios::in);
    loadFile.read((char *) &mapSize , sizeof(unsigned int));
    loadFile.close();
    grand.map = new condition*[mapSize];
        for (size_t i = 0; i < mapSize ; i++)
        {
            grand.map[i] = new condition[mapSize];
        }
        for (size_t i = 0; i < mapSize; i++)
        {
            for (size_t j = 0; j < mapSize; j++)
            {
                grand.map[i][j] = Null;
            }
        }
    loadFile.open("SaveFile.bin", ios::binary | ios::in);

    unsigned int sizeOfStruct = sizeof(unsigned int)+sizeof(enemyStruct)+sizeof(spaceShipStruct)+(sizeof(condition));
    if(loadFile.read((char *) &grand , sizeOfStruct))
    {
    	return true;
	}
    else
        return false;

}

void menu(grandStruct &grand)
{
	unsigned int marker;
    unsigned int choice = 1;
    do
    {
        system("cls");
        cout << Green << "========= Menu =========" << Reset << endl;
        switch (choice)
        {
        case 1:
            cout << Bold << Black <<  BackgroundGreen << "Continue Game" << Reset << endl;
            cout << "New Game" << Reset << endl;
            cout << "Game Settings" << Reset << endl;
            cout << "Quit Game" << Reset << endl;
            break;
        case 2:
            cout << "Continue Game" << Reset << endl;
            cout << Bold << Black << BackgroundGreen << "New Game" << Reset << endl;
            cout << "Game Settings" << Reset << endl;
            cout << "Quit Game" << Reset << endl;
            break;
        case 3:
            cout << "Continue Game" << Reset << endl;
            cout << "New Game" << Reset << endl;
            cout << Bold << Black <<  BackgroundGreen << "Game Settings" << Reset << endl;
            cout << "Quit Game" << Reset << endl;
            break;
        case 4:
            cout << "Continue Game" << Reset << endl;
            cout << "New Game" << Reset << endl;
            cout << "Game Settings" << Reset << endl;
            cout << Bold << Black <<  BackgroundGreen << "Quit Game" << Reset << endl;
            break;
        }
        cout << Green << "========================" << Reset << endl;
        marker = getch();

        switch (marker) 
        {
        case UP:
            if (choice <= 1)
                choice = 4;
            else
                choice--;
            break;
        case DOWN:
            if (choice >= 4)
                choice = 1;
            else
                choice++;
            break;
        case 13:// Enter
            bool flag = true;
            switch (choice)
            {
            case 1:
                system("cls");
                load(grand);
                return ;
                break;
            case 2:
                newGame(grand);
                return ;
                break;
            case 3:
                system("cls");
                gameSetting();
                break;
            case 4:
                system("cls");
                exit(0);
                break;
            }
            break;
        }
        
    } while (true);
}

void newGame(grandStruct &grand)
{
    bool flag = false;
    grand.map = NULL;
    system("cls");
    do
    {
        cout << BoldRed << "New Game" << Reset << endl;
        cout << "Please enter the map grand size you want:";
        cin >> grand.size;
        if (grand.size < 15)
        {
            system("cls");
            cout << "Undefiend!!"<< endl << "map grand size cannot be less than 15" << endl <<"please try again" << endl;
            flag = false;
            Sleep(5);
        }
        else
        {
            flag = true;
        }
    } while (flag == false);
    if (grand.size%2 == 0)
    {
        cout << "The map size cannot be even play start in grand size " << grand.size - 1 << endl;
        grand.size--;
        Sleep(5);
    }
    grand.map = new condition*[grand.size];
    for (size_t i = 0; i < grand.size ; i++)
    {
        grand.map[i] = new condition[grand.size];
    }
    for (size_t i = 0; i < grand.size; i++)
    {
        for (size_t j = 0; j < grand.size; j++)
        {
            grand.map[i][j] = Null;
        }
    }
    grand.spaceShip.x = ((grand.size - 1)/2);
    grand.map[grand.size - 1][grand.spaceShip.x] = SpaceShip;
}

void gameSetting()
{
    unsigned int marker = 1;
    bool menuSelected = false;

    do
    {
        system("cls");
        cout << Green << "========= Game Settings =========" << Reset << endl;

      
        if (marker == 1)
            cout << Bold << Black <<  BackgroundGreen;
        cout << "Change Spaceship Character" << Reset << endl;

        if (marker == 2)
            cout << Bold << Black <<  BackgroundGreen;
        cout << "Change Enemy Character" << Reset << endl;

        if (marker == 3)
            cout << Bold << Black <<  BackgroundGreen;
        cout << "Return to Main Menu" << Reset << endl;

       
        int key = getch();

       
        switch (key)
        {
        case UP:
            if (marker > 1)
                marker--;
            break;

        case DOWN:
            if (marker < 3)
                marker++;
            break;

        case 13:  
            if (marker == 1)
            {
               
                cout << "Enter new character for Spaceship: ";
               
            }
            else if (marker == 2)
            {
                cout << "Enter new character for Enemy: ";
               
            }
            else if (marker == 3)
            {
                menuSelected = true; 
            }
            break;
        }
    } while (!menuSelected);
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

void grandDraw(grandStruct &grand)
{
    system("cls");
    cout << "heal = " << Red << grand.spaceShip.heal << Reset << endl;
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

void move(grandStruct &grand)
{
    bool flag = true;
    do 
    {
        switch (getch())
        {
        case RIGHT:
            if (grand.spaceShip.x < grand.size - 1)
            {
                grand.map[grand.size - 1][grand.spaceShip.x] = Null;
                grand.spaceShip.x += 1;
                grand.map[grand.size - 1][grand.spaceShip.x] = SpaceShip;
            }
            else
            {
                grand.map[grand.size - 1][grand.spaceShip.x] = Null;
                grand.spaceShip.x = 0;
                grand.map[grand.size - 1][grand.spaceShip.x] = SpaceShip;
            }   
            flag = true;
            shoot(grand);
            break;
        case LEFT:
            if (grand.spaceShip.x > 0)
            {
                grand.map[grand.size - 1][grand.spaceShip.x] = Null;
                grand.spaceShip.x -= 1;
                grand.map[grand.size - 1][grand.spaceShip.x] = SpaceShip;
            }
            else
            {
                grand.map[grand.size - 1][grand.spaceShip.x] = Null;
                grand.spaceShip.x = (grand.size - 1);
                grand.map[grand.size - 1][grand.spaceShip.x] = SpaceShip;
            }
            shoot(grand);
            flag = true;
            break;
        case DOWN:
            shoot(grand);
            break;
        case UP:
            menu(grand);
            break;
        default:
            flag = false;
            break;
        }
    }while (flag == false);

}

void shoot(grandStruct &grand)
{
}