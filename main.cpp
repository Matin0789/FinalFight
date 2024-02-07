// Matin amirpanah ------->40212358003
// Nima makhmali  -------->40212358035

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

void GrandDraw()
{
    srand(time(NULL));

    cout << " --------------------" << endl;

    int count = 0; // تعداد "*" های تصادفی
    bool chosen[5] = { false }; // وضعیت انتخاب هر خانه

    while (count < 4) {
        int randomIndex = rand() % 5;
        if (!chosen[randomIndex]) {
            chosen[randomIndex] = true;
            count++;
        }
    }

    for (int i = 0; i < 4; i++)
    {
        cout << "|";

        for (int j = 0; j < 5; j++)
        {
            if (i == 0 && j < 4)
            {
                if (chosen[j]) {
                    cout << " * ";
                }
                else {
                    cout << "   ";
                }
            }
            else {
                cout << "   ";
            }

            cout << "|";
        }

        cout << endl;
        cout << " --------------------" << endl;
    }

    cout << "|";
    int position = rand() % 5;
    for (int j = 0; j < 5; j++)
    {
        if (j == position)
            cout << " # ";
        else
            cout << "   ";

        cout << "|";
    }

    cout << endl;
    cout << " --------------------" << endl;
}
//************************************************************************
//      move function 
//************************************************************************

void MoveHash()
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

int main()
{
    MoveHash();

    return 0;
}