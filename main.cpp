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
#include <vector>
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
    SpaceShip,
    Bullet
};

/// structs
struct enemyStruct
{
    char name[8];// enemy name
    char c = '*';// enemy default character
    size_t size;// enemy size in map
    size_t heal; // enemy's health
    bool exist = false;
    unsigned int y; // row of the enemy
    unsigned int x;// column of enemy
};

struct spaceShipStruct
{
    char c = '#';// space ship default charater
    size_t heal = 3;// space ship's health
    unsigned int x;// condition of the spaceship
    unsigned int point = 0;// 
};

struct bullets
{
    int x;// column of the bollets
    int y;// row of the bollets
    char c = '^';// shot default character
};

struct grandStruct
{
    unsigned int size;// size of grand
    unsigned int endPoint = 0;
    enemyStruct enemy;// 
    spaceShipStruct spaceShip;
    condition **map;
    vector<bullets> bullet;
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
void gameSetting(grandStruct &grand);

/// main function
int main()
{
    srand(time(NULL));
    grandStruct grand;
    grand.enemy.exist = false;
    enemyStruct typesOfEnemys[4] =
    {
        {"Dart", '*', 1, 1, false , 0, 0},
        {"Striker", '*', 2, 2, false, 0, 0},
        {"Wraith", '*', 3, 4, false, 0, 0},
        {"Banshee", '*', 4, 6, false, 0, 0},
    };
    menu(grand);
    while (grand.spaceShip.heal > 0 && grand.spaceShip.point < grand.endPoint)
    {
        if(grand.enemy.heal == 0)
        {
            grand.enemy.exist = false;
        }
        if (grand.enemy.exist == false)
        {
            grand.enemy = typesOfEnemys[rand()%4];
            grand.enemy.y = 0;
            grand.enemy.x = rand() % (grand.size - (grand.enemy.size - 1));
            grand.enemy.exist = true;
            for (size_t i = grand.enemy.x; i < grand.enemy.size + grand.enemy.x; i++)
                for (size_t j = grand.enemy.y; j < grand.enemy.y + grand.enemy.size; j++)
                    if (j >= 0)
                        grand.map[j][i] = Enemy;
        }
        grandDraw(grand);
        for (size_t i = 0; i < grand.bullet.size(); i++)
        {
            if (grand.bullet[i].y == 0)
            {
                grand.map[grand.bullet[i].y][grand.bullet[i].x] = Null;
                grand.bullet.erase(grand.bullet.begin() + i);
            }
            if (grand.map[grand.bullet[i].y - 1][grand.bullet[i].x] == Enemy)
            {
                grand.map[grand.bullet[i].y][grand.bullet[i].x] = Null;
                grand.bullet.erase(grand.bullet.begin() + i);
                grand.enemy.heal--;
            }
            grand.map[grand.bullet[i].y][grand.bullet[i].x] = Null;
            grand.bullet[i].y--;
            grand.map[grand.bullet[i].y][grand.bullet[i].x] = Bullet;
        }
        move(grand);
        for (size_t i = grand.enemy.x; i < grand.enemy.x + grand.enemy.size; i++)
        {
            for (size_t j = grand.enemy.y; j < grand.enemy.y + grand.enemy.size; j++)
            {
                grand.map[j][i] = Null;
            }
        }
        if (grand.enemy.heal == 0)
        {
            grand.spaceShip.point += 2 * (grand.enemy.size * grand.enemy.size);
            grand.enemy.exist = false;
            save(grand);
            continue;
        }
        if(grand.enemy.y + grand.enemy.size < grand.size)
        {
            grand.enemy.y++;
            for (size_t i = grand.enemy.x; i < grand.enemy.x + grand.enemy.size; i++)
            {
                for (size_t j = grand.enemy.y; j < grand.enemy.y + grand.enemy.size; j++)
                {
                    grand.map[j][i] = Enemy;
                }
            }
        }
        else
        {
            grand.enemy.exist = false;
            grand.spaceShip.heal--;
        }
        save(grand);
    }
    system("cls");
    for (size_t i = 0; i < grand.size - 3; i++)
        cout << Magenta << "/\\" << Reset;
    if (grand.spaceShip.heal == 0)
        cout << BoldRed << "Game Over";
    else
        cout << BoldGreen << "You Win";
    for (size_t i = 0; i < grand.size - 3; i++)
        cout << Magenta << "/\\" << Reset;
    cout << endl;
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
    fstream loadFile;
    loadFile.open("SaveFile.bin", ios::binary | ios::in);
    if(loadFile.is_open())
    {
        loadFile.read((char *) &mapSize , sizeof(unsigned int));
        loadFile.close();
        grand.map = new condition*[mapSize];
        for (size_t i = 0; i < mapSize ; i++)
            grand.map[i] = new condition[mapSize];
        for (size_t i = 0; i < mapSize; i++)
            for (size_t j = 0; j < mapSize; j++)
                grand.map[i][j] = Null;
        loadFile.open("SaveFile.bin", ios::binary | ios::in);
        unsigned int sizeOfStruct = sizeof(unsigned int)+sizeof(enemyStruct)+sizeof(spaceShipStruct)+(sizeof(condition));
        if(loadFile.read((char *) &grand, sizeOfStruct))
        {
            bullets bullet;
            while(loadFile.read((char *) &bullet, sizeof(bullets)))
                grand.bullet.push_back(bullet);
        	return true;
	    }
        else
            return false;
    }
    else
        newGame(grand);
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
        if (choice == 1)
            cout << "->" << Bold << Green;
        else
            cout << "  ";
        cout << "Continue Game" << Reset << endl;
        if (choice == 2)
            cout << "->" << Bold << Green;
        else
            cout << "  ";
        cout << "New Game" << Reset << endl;
        if (choice == 3)
            cout << "->" << Bold << Green;
        else
            cout << "  ";
            
        cout << "Game Settings" << Reset << endl;
        if (choice == 4)
            cout << "->" << Bold << Green;
        else
            cout << "  ";
        cout << "Quit Game" << Reset << endl;
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
                gameSetting(grand);
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
    try
    {
        remove("SaveFile.bin");
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    bool flag = false;
    grand.enemy.exist = false;
    system("cls");
    do
    {
        cout << BoldRed << "New Game" << Reset << endl;
        cout << "Please enter the map grand size you want: ";
        cin >> grand.size;
        cout << "Please enter the end point you want: ";
        cin >> grand.endPoint;
        if (grand.size < 15)
        {
            system("cls");
            cout << "Undefiend!!"<< endl << "map grand size cannot be less than 15" << endl <<"please try again" << endl;
            flag = false;
            Sleep(10);
        }
        else
            flag = true;
    } while (flag == false);
    if (grand.size%2 == 0)
    {
        cout << "The map size cannot be even play start in grand size " << grand.size - 1 << endl;
        grand.size--;
        Sleep(10);
    }
    grand.map = new condition*[grand.size];
    for (size_t i = 0; i < grand.size ; i++)
        grand.map[i] = new condition[grand.size];
    for (size_t i = 0; i < grand.size; i++)
        for (size_t j = 0; j < grand.size; j++)
            grand.map[i][j] = Null;
    grand.spaceShip.x = ((grand.size - 1)/2);
    grand.map[grand.size - 1][grand.spaceShip.x] = SpaceShip;
}

void gameSetting(grandStruct &grand)
{
    unsigned int marker = 1;
    bool menuSelected = false;

    do
    {
        system("cls");
        cout << Green << "========= Game Settings =========" << Reset << endl;

        if (marker == 1)
            cout<< "->" << Bold << Green;
        else
            cout << "  ";
        cout << "Change Spaceship Character" << Reset << endl;

        if (marker == 2)
            cout << "->" << Bold << Green;
        else
            cout << "  ";
        cout << "Change Enemy Character" << Reset << endl;

        if (marker == 3)
            cout << "->" << Bold << Green;
        else
            cout << "  ";
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
                system("cls");
                cout << "Enter new character for Spaceship: ";
                cin >> grand.spaceShip.c;
                system("cls");           
            }
            else if (marker == 2)
            {
                system("cls");
                cout << "Enter new character for Enemy: ";
                cin >> grand.enemy.c;
                system("cls");
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
        for (size_t j = 0; j < 4; j++)
            cout << "-";
    cout << '-';
    cout << endl;
}

void grandDraw(grandStruct &grand)
{
    system("cls");
    for (size_t i = 0; i < grand.size - 3; i++)
        cout << Blue << "/\\" << Reset;
    cout << "Final Fight";
    for (size_t i = 0; i < grand.size - 3; i++)
        cout << Blue << "/\\" << Reset;
    cout << endl;
    cout << "heal = " << Red << grand.spaceShip.heal << Reset << '\t' << "point = " << Red << grand.spaceShip.point << Reset << endl;
    for (size_t i = 0; i < grand.size; i++)
    {
        horizontalLineDraw(grand.size);
        for (size_t j = 0; j < grand.size; j++)
        {
            cout << '|';
            switch (grand.map[i][j])
            {
            case Enemy:
                cout << Red << ' ' << grand.enemy.c << ' ' << Reset;
                break;
            case SpaceShip:
                cout << Green << ' ' << grand.spaceShip.c << ' ' << Reset;
                break;
            case Bullet:
                cout << Blue << ' ' << grand.bullet[0].c << ' ' << Reset;
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
            flag = true;
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
    bullets newBullet;
    newBullet.x = grand.spaceShip.x;
    newBullet.y = grand.size - 2;
    grand.map[newBullet.y][newBullet.x] = Bullet;
    grand.bullet.push_back(newBullet);
}