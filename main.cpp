#include <iostream>

using namespace std;

void GrandDraw() 
{
    for (int i = 0; i < 5; i++) 
	{
       cout << " ---------------" << endl;
       cout << "|   |   |   |   |" << endl;
    }
       cout << " ---------------" << endl;
}

int main() 
{
    GrandDraw();
    return 0;
}