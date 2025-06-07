#pragma once
#include"tools.h"
#include"flight.h" 

class admin
{
private:
	string _adminId;
	string _adminPass;
public:
	admin()
	{
		_adminId = "notGiven";
		_adminPass = "notGiven";
	}

	//�����ǵ�¼���麯��

	//ϵͳ��ʼ�����ã����ļ��Ͳ��ٵ��ã���
	void checkAdminFile();
	//�ļ���ȡ�˺�����
	void readAdmin();
	//�Ƚ�ID��
	bool compareAdminId();
	//�Ƚ������
	bool compareAdminPass();

	//�����ǹ���Ա�˵�����

	//��Ӻ��࣬���غ���ָ���
	flight* newFlight();
	//д����������ȫ��ָ��head���·ɻ�newFlight ��
	void addFlight(flight** head, flight* newFlight);
	//ɾ�������
	void deleteFlight(flight*& head, string flight_id);
};

//��
void admin::checkAdminFile()
{
	ifstream file("admin.txt");
	if (file) {
		cout << "Admin file exist..." << endl;
	}
	else {
		ofstream fout("admin.txt");
		if (!fout.is_open()) {
			cerr << "Unable to create Admin file";
		}
		else {
			string adminId, adminPass;
			cout << "please set the admin ID (no space) :";
			adminId = inputStrFun();
			cout << "please set the admin Password (no space) :";
			adminPass = inputStrFun();
			fout << adminId << " " << adminPass;
			cout << "Admin flie initialized success..." << endl;
		}
	}
}

void admin::readAdmin()
{
	std::ifstream file("admin.txt");
	if (file)
	{
		file >> _adminId >> _adminPass;
	}
	else {
		std::cerr << "Failed to open admin file." << std::endl;
	}
	file.close();
}

//��
bool admin::compareAdminId()
{
	string adminId;
	cout << "please input the admin ID :";
	adminId = inputStrFun();
	if (adminId == _adminId) {
		return true;
	}
	else {
		cout << "admin ID wrong, log out...";
		return false;
	}
}
//��
bool admin::compareAdminPass()
{
	string adminPass;
	cout << "please input the admin Password :";
	adminPass = inputStrFun();
	if (adminPass == _adminPass) {
		return true;
	}
	else {
		cout << "admin Password wrong, log out...";
		return false;
	}
}

//��
flight* admin::newFlight()
{
	flight* newFlight = new flight;
	//�����
	cout << "please set the flight number (no space allowed): ";
	newFlight->flight_id = inputStrFun();
	//��λ��x��
	cout << "please set the seat length (<=100): ";
	newFlight->type[0] = inputNumFun(0, 100);
	cout << "please set the seat width (<=12): ";
	newFlight->type[1] = inputNumFun(0, 12);
	//��λ��ʼ��
	newFlight->totalSeat = newFlight->type[0] * newFlight->type[1];
	newFlight->remainSeat = newFlight->totalSeat;
	//�����ﵽ����
	cout << "please set the departure city (airport)(no space allowed): ";
	newFlight->depart = inputStrFun();
	cout << "please set the arrival city (airport)(no space allowed): ";
	newFlight->arrive = inputStrFun();
	//��������ʱ��
	inputDate(newFlight->departDate[0], newFlight->departDate[1],
		newFlight->departDate[2], newFlight->departDate[3],
		newFlight->departDate[4]);
	inputDate(newFlight->arriveDate[0], newFlight->arriveDate[1],
		newFlight->arriveDate[2], newFlight->arriveDate[3],
		newFlight->arriveDate[4]);

	//�۸�
	cout << "please set the price (decimals allowed): ";
	newFlight->price = inputNumFun(0, 20000);

	//��ʼ����λ == ��
	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 12; j++) {
			if (i < newFlight->type[0] && j < newFlight->type[1])
				newFlight->seat[i][j] = 0;
			else
				newFlight->seat[i][j] = -1;
		}
	}
	//�Ƿ�ȡ��
	newFlight->ifCancel = false;
	//��ʼ��ָ��
	newFlight->next = NULL;
	return newFlight;
}

//��
void admin::addFlight(flight** head, flight* newFlight)
{
	//����Ƿ����ظ������
	flight* test = *head;
	while (test != NULL)
	{
		if (newFlight->flight_id == test->flight_id)
		{
			cout << "flight ID exist, adding fail...";
			return;
		}
		test = test->next;
	}
	//û���ظ�����ʼд��
	if (*head == nullptr)
		*head = newFlight;
	else
	{
		flight* current = *head;
		while (current->next != nullptr) 
		{
			current = current->next;
		}
		current->next = newFlight;

	}
}

//ɾ��head������ض�����
void admin::deleteFlight(flight*& head, string flight_id)
{
	flight* current = head;
	while (current != nullptr)
	{
		if (current->flight_id == flight_id)
		{
			current->ifCancel = true;
			cout << "flight delete success...";
			break;
		}
		current = current->next;
	}
	if (current == nullptr)
	{
		cout << "flight no found...";
	}
}





