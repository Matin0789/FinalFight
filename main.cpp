/* 
****** This project creat for FOP finall project winter1402 ******

authors:
    Matin amirpanah, Student No:40212358003
    Nima makhmali, Student No:40212358035
The relevant teacher :
    Dr. Bashiri
     
*/

/// libraries
#include <iostream>    // Interaction with terminal 
#include <stdlib.h>    // Interaction with the operating system
#include <ctime>       // Get system clock for Primary seed of rand
#include <fstream>     // Interaction with file
#include <conio.h>
#include <vector>      // for a vector and all its functions
#include<windows.h>    // for windows
//#include<unistd.h>   // for linux  <if you start this game in linux>


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

/// enums       <This is an enumeration structure>
enum condition
{
    Null,          //  <empty blocks>
    Enemy,          
    SpaceShip,
    Bullet          // <shoot>
};

/// structs    <This is the structure for the enemies, which includes variables for their shape name and position>
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

struct spaceShipStruct  // <This is the structure for the my ship, which represents the shape of its features and position>
{
    char c = '#';// space ship default charater
    size_t heal = 3;// space ship's health
    unsigned int x;// condition of the spaceship
    unsigned int point = 0;//  spaceShip points
};

struct bullets   // <This is the structure for the ship's beams, which includes the position and shape of the beam>
{
    int x;// column of the bollets
    int y;// row of the bollets
    char c = '^';// shot default character
};
 
struct grandStruct   // <This is the structure for our playground, on which all the characters of our game ride>
{
    unsigned int size;// size of grand
    unsigned int endPoint = 0; // spaceShip points
    enemyStruct enemy; // calling
    spaceShipStruct spaceShip;
    condition **map;
    vector<bullets> bullet;   // for shooting 
};


/// function declaration
// Preliminary function
bool save(grandStruct &grand);     //  <this function for saving game>
bool load(grandStruct &grand);
void newGame(grandStruct &grand);  //  <this function for starting new game with menu>
// drawing grand functions
void horizontalLineDraw(size_t);   //  <This function is for the horizontal lines of the game board>
void grandDraw(grandStruct &grand);// <This function is for the game board>
// move and shoot functions
void move(grandStruct &grand);     // <This function is to move the ship sideways>
void shoot(grandStruct &grand);    // <This function is for the ship to attack enemies using its arrows>
//menu functions
void menu(grandStruct &grand);     //  <This function makes a menu appear at the beginning of the game>
void gameSetting(grandStruct &grand);  

/// main function
int main()
{
    srand(time(NULL));    // This function is to use the rand function
    grandStruct grand;
    grand.enemy.exist = false;
    enemyStruct typesOfEnemys[4] =       // <This structure is for all kinds of our enemies>
    {
        {"Dart", '*', 1, 1, false , 0, 0},   
        {"Striker", '*', 2, 2, false, 0, 0},            // <<<<<<< typeofenemys >>>>>>>
        {"Wraith", '*', 3, 4, false, 0, 0},
        {"Banshee", '*', 4, 6, false, 0, 0},
    };
    
    menu(grand);    //   Call the menu function
    while (grand.spaceShip.heal > 0 && grand.spaceShip.point < grand.endPoint)
    {
        if(grand.enemy.heal == 0)        // A condition for checking the condition of the ship
        {
            grand.enemy.exist = false;    // If the heal is equal to zero, it will be out of the game
        }
        if (grand.enemy.exist == false)
        {
            grand.enemy = typesOfEnemys[rand()%4];      //  Random enemy selection by the system to enter the game screen
            grand.enemy.y = 0;
            grand.enemy.x = rand() % (grand.size - (grand.enemy.size - 1));
            grand.enemy.exist = true;
            for (size_t i = grand.enemy.x; i < grand.enemy.size + grand.enemy.x; i++)
                for (size_t j = grand.enemy.y; j < grand.enemy.y + grand.enemy.size; j++)   //   Lines 153 and 154 print the enemy using two circles
                    if (j >= 0)         // This condition is for the ship to be printed completely on the page and not to be removed from the page
                        grand.map[j][i] = Enemy;         ////  print enemys
        }
        grandDraw(grand);  
        //   In this section, we want to write about shooting the ship
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
                grand.enemy.heal--;                 // If the arrow hits the ship, reduce one of the enemy's lives
            }
            grand.map[grand.bullet[i].y][grand.bullet[i].x] = Null;
            grand.bullet[i].y--;
            grand.map[grand.bullet[i].y][grand.bullet[i].x] = Bullet;
        }
        move(grand);   //   Call the move function
        for (size_t i = grand.enemy.x; i < grand.enemy.x + grand.enemy.size; i++)
        {
            for (size_t j = grand.enemy.y; j < grand.enemy.y + grand.enemy.size; j++)
            {
                grand.map[j][i] = Null;
            }
        }
        if (grand.enemy.heal == 0)    // Checking the condition of continuing the game   <heal>
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
    for (size_t i = 0; i < grand.size - 3; i++)    // Print the symbol /\\ in the number of three less than the last line of the game screen entered by the user
        cout << Magenta << "/\\" << Reset;
    if (grand.spaceShip.heal == 0)
        cout << BoldRed << "Game Over";  // If the ship's heal becomes zero, print Game Over at the top of the screen.
    else
        cout << BoldGreen << "You Win";  //  If the heal of the ship is not equal to zero, print on the top of the screen you win
    for (size_t i = 0; i < grand.size - 3; i++)
        cout << Magenta << "/\\" << Reset;      // Print the symbol /\\ in the number of three less than the last line of the game screen entered by the user
    cout << endl;
 	system("pause");   // clear page
    return 0;
}

/// function definition
bool save(grandStruct &grand)
{
    fstream saveFile("SaveFile.bin", ios::binary | ios::trunc | ios::out);  // Save game information in a binary file
    if(saveFile.write((char *) &grand , sizeof(grand)))
    {
    	saveFile << flush;    // Use the flush command to continuously store changes in the file
    	return true;          // return true for bool function 
	}
    else
        return false;         // return false for bool function 
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
	unsigned int marker;        // Taking three commands by the system from the user to move in the menu
    unsigned int choice = 1;
    do                //do while loop to display the statements before checking the condition once
    {
        system("cls");
        cout << Green << "========= Menu =========" << Reset << endl;   // Titr
        if (choice == 1)                   // case down or up 
            cout << "->" << Bold << Green;  //If the user clicks on this part, the line will be displayed in green
        else
            cout << "  ";
        cout << "Continue Game" << Reset << endl; 
        if (choice == 2)                    // case down or up
            cout << "->" << Bold << Green;   //If the user clicks on this part, the line will be displayed in green
        else
            cout << "  ";
        cout << "New Game" << Reset << endl;
        if (choice == 3)                   // case down or up
            cout << "->" << Bold << Green;  // If the user clicks on this part, the line will be displayed in green
        else
            cout << "  ";
            
        cout << "Game Settings" << Reset << endl;
        if (choice == 4)                    // case up
            cout << "->" << Bold << Green;   // If the user clicks on this part, the line will be displayed in green
        else
            cout << "  ";
        cout << "Quit Game" << Reset << endl;
        cout << Green << "========================" << Reset << endl;

        marker = getch();   

        switch (marker) 
        {
        case UP:               // up key  <define>
            if (choice <= 1)  // If the user clicks the top key, the program will exit the game as stated in the fourth condition
                choice = 4;   
            else
                choice--;
            break;
        case DOWN:            //  Toggle options
            if (choice >= 4)
                choice = 1;
            else
                choice++;    // next choice
            break;
        case 13:    // Enter key 
            bool flag = true;
            switch (choice)
            {
            case 1:
                system("cls");
                load(grand);    
                return ;
                break;
            case 2:
                newGame(grand);   // call the newGame function       // Choose the second option     // Enter the game  
                return ;
                break;
            case 3:
                system("cls");
                gameSetting(grand);  // call the GameSetting function   // Choose the Third option
                break;
            case 4:
                system("cls");     
                exit(0);        // call the exit(return 0)  function   // Choose the fourth option
                break;
            }
            break;
        }
        
    } while (true);
}

void newGame(grandStruct &grand)
{
    try                      // debuging 
    {
        remove("SaveFile.bin");     // remove Information 
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    bool flag = false;
    grand.enemy.exist = false;
    system("cls");
    do               //do while loop to display the statements before checking the condition once
    { 
        cout << BoldRed << "New Game" << Reset << endl;    // Write newGame
        cout << "Please enter the map grand size you want: ";   // size of grand
        cin >> grand.size;
        cout << "Please enter the end point you want: ";       // Goal score
        cin >> grand.endPoint;              // call the struct 
        if (grand.size < 15)     // If the user enters a number less than 15 for the number of rows and columns of the page, it will get an error
        {
            system("cls");
            cout << "Undefiend!!"<< endl << "map grand size cannot be less than 15" << endl <<"please try again" << endl;  // write error
            flag = false;
            Sleep(10);     // break
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

void gameSetting(grandStruct &grand)    // second part of menu
{
    unsigned int marker = 1;    //  Select keys
    bool menuSelected = false;     // loop

    do                 //do while loop to display the statements before checking the condition once
    {
        system("cls");
        cout << Green << "========= Game Settings =========" << Reset << endl;   // print Titr

        if (marker == 1)
            cout<< "->" << Bold << Green;   //Changing Position //first option
        else
            cout << "  ";
        cout << "Change Spaceship Character" << Reset << endl;

        if (marker == 2)
            cout << "->" << Bold << Green;  //Changing Position // second option
        else
            cout << "  ";
        cout << "Change Enemy Character" << Reset << endl;

        if (marker == 3)
            cout << "->" << Bold << Green;  //Changing Position // third option
        else
            cout << "  ";
        cout << "Return to Main Menu" << Reset << endl;  

        int key = getch();  // input 

         switch (key)
        {
        case UP:    // If up is selected
            if (marker > 1)
                marker--;  
            break;

        case DOWN:   // If down is selected
            if (marker < 3)
                marker++;  // next option 
            break;

        case 13:   // If Enter is selected
            if (marker == 1)
            {
                system("cls");
                cout << "Enter new character for Spaceship: "; 
                cin >> grand.spaceShip.c;      // Change character of SpaceShip
                system("cls");           
            }
            else if (marker == 2)
            {
                system("cls");
                cout << "Enter new character for Enemy: ";
                cin >> grand.enemy.c; // Change character of enemys
                system("cls");
            }
            else if (marker == 3)
            {
                menuSelected = true; //loop  // goto menu
            }
            break;
        }
    } while (!menuSelected);  // If we have not gone to the main menu, it will continue working
}

void horizontalLineDraw(size_t size)
{
    for (size_t i = 0; i < size; i++)  // Print rows to the number of input cells
        for (size_t j = 0; j < 4; j++)    
            cout << "-";                  // -------
    cout << '-';
    cout << endl;
}

void grandDraw(grandStruct &grand)   // Game map
{
    system("cls");        // clear page 
    for (size_t i = 0; i < grand.size - 3; i++)
        cout << Blue << "/\\" << Reset;   // this line for print Titr
    cout << "Final Fight";
    for (size_t i = 0; i < grand.size - 3; i++)
        cout << Blue << "/\\" << Reset;    // this line for print Titr
    cout << endl;
    cout << "heal = " << Red << grand.spaceShip.heal << Reset << '\t' << "point = " << Red << grand.spaceShip.point << Reset << endl;  // Write heal and point
    for (size_t i = 0; i < grand.size; i++)
    {
        horizontalLineDraw(grand.size);  // call the horizontalLineDraw function 
        for (size_t j = 0; j < grand.size; j++)
        {
            cout << '|';
            switch (grand.map[i][j])
            {
            case Enemy:
                cout << Red << ' ' << grand.enemy.c << ' ' << Reset;  //Writing the character of the enemys
                break;
            case SpaceShip:
                cout << Green << ' ' << grand.spaceShip.c << ' ' << Reset;  //Writing the character of the ship
                break;
            case Bullet:
                cout << Blue << ' ' << grand.bullet[0].c << ' ' << Reset;  //Writing the character of the bullets
                break;
            default:
                cout << "   ";
                break;
            }
        }
        cout << '|';
        cout << endl;
    }
    horizontalLineDraw(grand.size);     // call the horizontalLineDraw function 
}

void move(grandStruct &grand)      // this function It is for the movement of the ship
{
    bool flag = true;    // loop 
    do          //do while loop to display the statements before checking the condition once
    {  
        switch (getch())
        {
        case RIGHT:      // if user select Right key.....
            if (grand.spaceShip.x < grand.size - 1)
            {
                grand.map[grand.size - 1][grand.spaceShip.x] = Null; //Clear the current position of the ship
                grand.spaceShip.x += 1; // plus plus 
                grand.map[grand.size - 1][grand.spaceShip.x] = SpaceShip;  // new position for ship
            }
            else           //  Select irrelevant button
            {
                grand.map[grand.size - 1][grand.spaceShip.x] = Null;    //Clear the current position of the ship
                grand.spaceShip.x = 0;                                 //Do not change the position
                grand.map[grand.size - 1][grand.spaceShip.x] = SpaceShip;   //The same position as before
            } 
            flag = true; // loop
            shoot(grand);  // call the shoot function 
            break;
        case LEFT:         // if user select Right key.....
            if (grand.spaceShip.x > 0)
            {
                grand.map[grand.size - 1][grand.spaceShip.x] = Null;   //Clear the current position of the ship
                grand.spaceShip.x -= 1;                                     //Low-off
                grand.map[grand.size - 1][grand.spaceShip.x] = SpaceShip;    // new position for ship
            }
            else              //  Select irrelevant button
            {
                grand.map[grand.size - 1][grand.spaceShip.x] = Null;         //Clear the current position of the ship
                grand.spaceShip.x = (grand.size - 1);                       //Do not change the position
                grand.map[grand.size - 1][grand.spaceShip.x] = SpaceShip;   //The same position as before
            }
            shoot(grand);    // call the shoot function 
            flag = true;   // loop 
            break;
        case DOWN:        // if user select Down key.....
            shoot(grand);    // call the shoot function 
            flag = true;
            break;
        case UP:     // if user select Up key.....
            menu(grand);      // call the menu function 
            break;
        default:          //  Select irrelevant button
            flag = false;    // loop
            break;         
        }
    }while (flag == false);   // if flag is false ......

}

void shoot(grandStruct &grand)     /// shooting function 
{
    bullets newBullet;    // call the bullet struct 
    newBullet.x = grand.spaceShip.x;  // Condition 
    newBullet.y = grand.size - 2;     // Condition 
    grand.map[newBullet.y][newBullet.x] = Bullet;
    grand.bullet.push_back(newBullet);    // increase
}