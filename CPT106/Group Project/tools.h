#pragma once
#include<iostream>
#include <string>
#include <fstream>
#include<iomanip>
#include <sstream>
using namespace std;

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"


//��������
double inputNumFun(int limSize, int maxSize)
{
	double num;
	string temp;
	cin >> num;
	getchar();
	while (num > maxSize || num < limSize)
	{
		cout << "input invalid, please enter again..." << endl;
		cin >> num;
		getchar();
	}
	return num;
}

//��������
string inputStrFun()
{
	string line;

	getline(cin, line);
	while (true) {
		//���費���ڿո�
		bool existSpace = false;
		//��������
		for (int i = 0; i < line.length(); i++) {
			//�ҵ��ո�������true,���˳�forѭ��
			if (line[i] == ' ') {
				existSpace = true;
				break;
			}
		}
		//���false��Ҳ����û�ո���while break
		if (!existSpace)
			break;
		//�пո񣬼�������
		else {
			cout << "Input contains space, please enter again..." << endl;
			getline(cin, line);
		}
	}
	return line;
}

//��������
void inputDate(int& year, int& month, int& day, int& hour, int& minute) {
	cout << "Please set the year: ";
	year = inputNumFun(2024, 2030);
	cout << "Please set the month: ";
	month = inputNumFun(1, 12);
	cout << "Please set the day: ";
	day = inputNumFun(1, 31);
	cout << "Please set the hour: ";
	hour = inputNumFun(0, 23);
	cout << "Please set the minute: ";
	minute = inputNumFun(0, 59);
}

//�������
string convertType(int num[2])
{
	ostringstream ss;
	ss << "P" << num[0] << num[1];
	string result = ss.str();
	return result;
}

//����������
string convertYear(int num[5])
{
	ostringstream ss;
	ss << num[0] << "-" << num[1] << "-" << num[2];
	string result = ss.str();
	return result;
}

//����ʱ��
string convertHour(int num[5])
{
	stringstream ss;
	string min;
	if (num[4] < 10)
	{
		stringstream aa;
		aa << "0" << num[4];
		min = aa.str();
	}
	else
	{
		stringstream aa;
		aa << num[4];
		min = aa.str();
	}
	ss << num[3] << ":" << min;
	string result = ss.str();
	return result;
}


//������һ������
void backMenu()
{
	system("cls");
	cout << "Back to previous menu..." << endl;
}


bool isWithinRange(int* ticketDate, int* startTime, int* endTime) {
	// Compare years first
	if (ticketDate[0] < startTime[0] || ticketDate[0] > endTime[0]) {
		return false;
	}
	// If year matches, compare months
	if (ticketDate[0] == startTime[0] && ticketDate[1] < startTime[1]) {
		return false;
	}
	if (ticketDate[0] == endTime[0] && ticketDate[1] > endTime[1]) {
		return false;
	}
	return true;
}