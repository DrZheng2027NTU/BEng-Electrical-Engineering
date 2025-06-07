#pragma once
#include<iostream>
#include<string>
using namespace std;
class Vehicle
{
private:
	string brandName;
	string colour;
	int power;
	double weight;
public:
    Vehicle( string& brand, string& col, int pwr, double wt)
        : brandName(brand), colour(col), power(pwr), weight(wt) { }//the same as brand=brandName¡­¡­, but more simple

    virtual void input() 
    {
        cout << "Enter brand name";
        cin >> brandName;
        cout << "Enter colour";
        cin >> colour;
        cout << "Enter power";
        cin >> power; 
        cout << "Enter weight";
        cin >> weight;
    }
    virtual void display()
    {
        cout << "show brandName:"<<endl<<brandName<<endl;
        cout << "show colour:" <<endl<<colour <<endl;;
        cout << "show power:"<<endl<<power<<endl;
        cout << "show weight:"<<endl<<weight<<endl;
    }
};