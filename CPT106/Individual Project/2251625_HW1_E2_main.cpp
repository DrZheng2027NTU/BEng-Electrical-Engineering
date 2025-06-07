#include<iostream>
#include<string>
#include"Vehicle.h"//call all the head files 
#include"Car.h"//call all the head files
#include"Trcuk.h"//call all the head files
using namespace std;
int main() 
{
    string brandA = "Bayerische Motoren Werke";//the abbreviation of which is BMW
    string colourA = "Blue";
    string brandB = "Alfa Romeo";
    string colourB = "Red";
    string brandC = "Maserati";
    string colourC = "Black";
    Vehicle* p[3];
    p[0] = new Vehicle(brandA, colourA, 120, 1000);//dynamic memory allocation
    p[1] = new Car(brandB, colourB, 150, 1200, 4);
    p[2] = new Truck(brandC, colourC, 200, 2500, 2, 5000);
    for (int i = 0; i < 3; i++) 
    {
        if (i == 0)
        {
            cout << "Vehicle parameter setting" << endl;
            p[i]->input();
            p[i]->display();
            delete p[i];//remember the release the memory after creating.
        }
        if (i == 1)
        {
            cout << "Car parameter setting" << endl;
            p[i]->input();
            p[i]->display();
            delete p[i];//remember the release the memory after creating.
        }
        if (i == 2)
        {
            cout << "Truck parameter setting" << endl;
            p[i]->input();
            p[i]->display();
            delete p[i];//remember the release the memory after creating.
        }
        
    }
    return 0;
}