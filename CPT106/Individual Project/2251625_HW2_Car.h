#pragma once
#include<iostream>
#include<string>
#include"Vehicle.h"//call all the head files 
using namespace std;
class Car:public Vehicle
{
protected:
	string brandName;
	string colour;
	int power;
	double weight;
private:
	int seats;
public:
	Car(string& brand, string& col, int pwr, double wt,int st)//do not forget to call by reference for strings
		: Vehicle(brand,col, pwr, wt),seats(st)
	{	}//the same as brand=brandName¡­¡­, but more simple
	void input()
	{
		Vehicle::input(); // we do not need to cout every term because we have defined them in the vehicle, we can now just call them
		cout << "Enter number of seats: ";
		cin >> seats;
	}
	void display()
	{
		Vehicle::display(); // // we do not need to cout every term because we have defined them in the vehicle, we can now just call them
		cout << "show seats:" << seats << endl;
	}
};