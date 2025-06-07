#pragma once
#include<iostream>
#include<string>
#include"Vehicle.h"//call all the head files 
#include"Car.h"//call all the head files 
using namespace std;
class Truck : public Car 
{
protected:
	string brandName;
	string colour;
	int power;
	double weight;
    int seats;
private:
    int load;  
public:
    Truck(string& brand, string& col, int pwr, double wt, int st, int ld)
        : Car(brand, col, pwr, wt, st), load(ld) { }//the same as brand=brandName¡­¡­, but more simple
    void input() 
    {
        Car::input(); // we do not need to cout every term because we have defined them in the car, we can now just call them
        cout << "Enter load capacity: ";
        cin >> load;
    }
    void display() 
    {
        Car::display(); // we do not need to cout every term because we have defined them in the car, we can now just call them
        cout << "show load:" << load << endl;
    }
};