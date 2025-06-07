#include "tools.h"
#include "flight.h"
#include "admin.h"
#include "customer.h"
#include "agent.h"
#include"manager.h"
//ȫ��flight�����head
flight* headFlight = NULL;
//ȫ��ticket
ticket* headTicket = NULL;
//ȫ�ֹ���Ա
admin* onlyAdmin;
//ȫ�ֳ˿�
customer* headCustomer = nullptr;
//ȫ�ִ���
agent* onlyAgent = nullptr;
//ȫ�־���
manager* onlyManager = nullptr;


void adminMenu()
{
	while (true)
	{
		system("cls");
		headFlight = nullptr;
		readFlight(&headFlight);//��ȡ��ǰ���к���

		cout << "----------" << endl
			<< "|  Admin  |" << endl
			<< "-----------" << endl
			<< "1: View all Flight" << endl
			<< "2: Add Flight" << endl
			<< "3: Delete Flight" << endl
			<< "0: Back" << endl
			<< "choose: ";
		int choose = inputNumFun(0, 3);
		//����
		if (choose == 0)
		{
			backMenu();
			break;
		}
		//��ʾ����
		else if (choose == 1)
		{
			showFlight(headFlight);
			cout << "Enter for back...";
			while (getchar() != '\n');
		}
		//���Ӻ���
		else if (choose == 2)
		{
			flight* newFlight = onlyAdmin->newFlight();
			onlyAdmin->addFlight(&headFlight, newFlight);
			writeFlight(headFlight);
			cout << "Enter for back...";
			while (getchar() != '\n');
		}
		//ɾ������
		else if (choose == 3)
		{
			cout << "Please enter the flight id you want to delete: ";
			string flightId = inputStrFun();
			onlyAdmin->deleteFlight(headFlight, flightId);
			writeFlight(headFlight);
			cout << "Enter for back...";
			while (getchar() != '\n');
		}
	}
}


void agentSearch()
{
	cout << "Please enter the departure city (airport): ";
	string depart = inputStrFun();
	cout << "Please enter the arrival city (airport): ";
	string arrive = inputStrFun();
	flight* filterFlight = searchFlight(headFlight, depart, arrive);
	//�з��ϵĺ���
	if (filterFlight != nullptr)
	{
		showFlight(filterFlight);
		cout << "1. Reserve a ticket for customer" << endl
			<< "0. Back" << endl
			<< "Choose:";
		int choose = inputNumFun(0, 1);
		if (choose == 0)
		{
			backMenu();
		}
		else {
			cout << "please enter the Flight ID: ";
			string FlightID = inputStrFun();
			flight* SpecificFlight = searchFlightByID(filterFlight, FlightID);
			//������ȷ��չʾ����������λ
			if (SpecificFlight != nullptr)
			{
				system("cls");
				showSpecificFlightSeat(SpecificFlight);
				cout << "Enter the seat you want to reserve: ";
				string Seat = inputStrFun();

				cout << "Please enter the customer name: ";
				string name = inputStrFun();
				bool NameExist = headCustomer->ifNameExist(headCustomer, name);
				if (NameExist)
				{
					onlyAgent->reserveSeat(SpecificFlight, headTicket, Seat, name);//����λ
					synFlight(headFlight, SpecificFlight);//ͬ��������Ϣ
					writeTicketFile(headTicket);
					writeFlight(headFlight);
					while (getchar() != '\n');
				}
				else
				{
					cout << "customer name not exist!...";
					while (getchar() != '\n');
				}
			}
			else
			{
				cout << "Enter wrong Flight ID!...";
				while (getchar() != '\n');
			}
		}
	}
	//û�з��ϵĺ���
	else
	{
		cout << "There are no eligible flights!..." << endl;
		while (getchar() != '\n');
	}

}

//����˵�
void agentMenu()
{
	while (true)
	{
		system("cls");
		headFlight = nullptr;
		headCustomer = nullptr;
		headTicket = nullptr;
		readFlight(&headFlight);//��ȡ��ǰ���к���
		headCustomer->readCustomer(&headCustomer);//��ȡ��ǰ�����û�
		readTicket(headTicket);//��ȡ��ǰ���е�Ʊ

		cout << "----------" << endl
			<< "|  Agent  |" << endl
			<< "-----------" << endl
			<< "1: Reserve--Search for departure and arrival" << endl
			<< "2: Pay for specific customer" << endl
			<< "3: Cancel for specific customer" << endl
			<< "4: Check sold ticket number" << endl
			<< "0: Back" << endl
			<< "choose: ";
		int choose = inputNumFun(0, 4);
		//����
		if (choose == 0)
		{
			backMenu();
			break;
		}

		else if (choose == 1)
		{
			agentSearch();
		}
		else if (choose == 2 || choose == 3)
		{
			cout << "Please enter the customer name: ";
			string name = inputStrFun();
			bool NameExist = headCustomer->ifNameExist(headCustomer, name);
			if (NameExist == true)
			{
				customer thisCustomer(name);
				thisCustomer.readCustomerTicket(&thisCustomer, headTicket);
				thisCustomer.showCustomerTicket(thisCustomer);

				cout << "please input the ticket id (0 for back): ";
				int chosenTicket = inputNumFun(0,99999999);
				if (chosenTicket <= 10000000)
				{
					backMenu();
				}
				else
				{
					if (choose == 2)
					{
						onlyAgent->paySeat(headTicket, chosenTicket, headFlight);
						while (getchar() != '\n');
					}
					else if (choose == 3)
					{
						onlyAgent->cancelSeat(headTicket, chosenTicket, headFlight);
						while (getchar() != '\n');
					}
					writeFlight(headFlight);
					writeTicketFile(headTicket);
				}
			}
			else
			{
				cout << "Customer name not exist...";
				while (getchar() != '\n');
			}
		}
		else if (choose == 4)
		{
			int time1[2], time2[2];
			cout << "please input the time interval(2020-2900): ";
			time1[0] = inputNumFun(2020, 2900);
			cout << "please input the time interval(1-12): ";
			time1[1] = inputNumFun(1, 12);
			cout << "please input the time interval(2020-2900): ";
			time2[0] = inputNumFun(2020, 2900);
			cout << "please input the time interval(1-12): ";
			time2[1] = inputNumFun(1, 12);

			onlyAgent->checkIncome(time1, time2, headTicket);
			while (getchar() != '\n');
		}
	}
}

//�û��Ĳ˵�
void customerMenu(customer thisCustomer)
{
	customer* ThisCustomer = new customer;

	while (true)
	{
		cout << "--------------" << endl
			<< "|  Customer  |" << endl
			<< "--------------" << endl
			<< "1: View Tickets " << endl
			<< "0: Back" << endl
			<< "choose: ";
		int choose = inputNumFun(0, 2);
		if (choose == 0)
		{
			backMenu();
			break;
		}
		else if (choose == 1)
		{

			ThisCustomer->readCustomerTicket(&thisCustomer, headTicket);
			ThisCustomer->showCustomerTicket(thisCustomer);
			while (getchar() != '\n');
		}
	}

}

void managerMenu() {
	while (true)
	{
		system("cls");
		headFlight = nullptr;
		headTicket = nullptr;
		readFlight(&headFlight);//��ȡ��ǰ���к���
		readTicket(headTicket); 

		cout << "-------------" << endl
			<< "|  Manager  |" << endl
			<< "--------------" << endl
			<< "1: View Flight Information" << endl
			<< "2: View Plane Number for a specific Flight type" << endl
			<< "3: View Total Income" << endl
			<< "0: Back" << endl
			<< "choose: ";
		int choose = inputNumFun(0, 3);
		//����
		if (choose == 0)
		{
			backMenu();
			break;
		}
		//��ʾ����
		else if (choose == 1)
		{
			showFlight(headFlight);
			cout << "Enter for back...";
			while (getchar() != '\n');
		}
		//�鿴�ɻ�����
		else if (choose == 2)
		{
			int length, width;
			cout << "Enter the length of the plane:";
			length = inputNumFun(0, 100);
			cout << "Enter the width of the plane:";
			width = inputNumFun(0, 12);
			flight*thisTpye = onlyManager->findTypeNum(length, width, headFlight);
			showFlight(thisTpye);
			cout << "Enter for back...";
			while (getchar() != '\n');
		}
		//���������
		else if (choose == 3)
		{
			onlyManager->calculateIncome(headTicket);
			onlyManager->showIncome();
			cout << "Enter for back...";
			while (getchar() != '\n');
		}
	}
}



//���û���¼
void customerLogin()
{
	//����һ���û���Ҫ��¼�������ʺ�����
	headCustomer = nullptr;
	headTicket = nullptr;
	headCustomer->readCustomer(&headCustomer);
	readTicket(headTicket);
	cout << "Enter your ID: ";
	string name = inputStrFun();
	cout << "Enter your PASSWORD: ";
	string password = inputStrFun();
	//�ж��Ƿ���ȷ
	bool ifLogin = headCustomer->loginCustomer(name, password, headCustomer);
	if (ifLogin == true)
	{
		system("cls");
		customer thisCustomer(name, password);
		customerMenu(thisCustomer);
	}
	else
	{
		cout << "Enter wrong Id of Password..." << endl;
		while (getchar() != '\n');
		backMenu();
	}
}

//���û�ע��
void customerRegistration()
{
	headCustomer = nullptr;

	cout << "please set your NAME: ";
	string name = inputStrFun();
	cout << "please set your PASSWORD: ";
	string pass = inputStrFun();

	//�������û�
	customer ThisCustomer(name, pass);
	//��ȡ�����û�
	ThisCustomer.readCustomer(&headCustomer);
	//�ж��Ƿ��ظ�id
	if (ThisCustomer.ifSameCustomer(headCustomer, &ThisCustomer) == false)
	{
		//��ӽ�����
		ThisCustomer.addCustomer(&headCustomer, &ThisCustomer);
		//д���ļ�
		ThisCustomer.writeCustomer(headCustomer);

		cout << "Registration success!" << endl << "press enter for back...";
		while (getchar() != '\n');
	}
	else
	{
		cout << "Name exist!" << endl << "press enter for back...";
		while (getchar() != '\n');
	}
	backMenu();
}


//�û����
void customerIdentity()
{
	while (true)
	{
		cout << "--------------" << endl
			<< "|  Customer  |" << endl
			<< "--------------" << endl
			<< "1: Registration" << endl
			<< "2: Login" << endl
			<< "0: Back" << endl
			<< "choose: ";
		int choose = inputNumFun(0, 2);
		if (choose == 0)
		{
			backMenu();
			break;
		}
		else if (choose == 1)
		{
			system("cls");
			customerRegistration();
		}
		else if (choose == 2)
		{
			system("cls");
			customerLogin();
		}
	}
}

//�������
void agentIdentity()
{
	string id, password;
	onlyAgent = new agent;

	onlyAgent->readAgent();

	cout << "Enter Agent ID: ";
	id = inputStrFun();
	cout << "Enter Password: ";
	password = inputStrFun();
	bool ifLogin = onlyAgent->loginAgent(id, password);
	if (ifLogin == true)
	{
		system("cls");
		agentMenu();
	}
	else
	{
		cout << "Enter wrong Id of Password..." << endl;
		while (getchar() != '\n');
		backMenu();
	}

}

//����Ա���
void adminIdentity()
{
	string id, password;
	onlyAdmin = new admin;
	onlyAdmin->readAdmin();
	if (onlyAdmin->compareAdminId())
	{
		if (onlyAdmin->compareAdminPass())
		{
			adminMenu();
		}
	}
}

void managerIdentity() {
	string id, password;
	onlyManager = new manager;
	onlyManager->readManager();
	if (onlyManager->compareManagerID())
	{
		if (onlyManager->compareManagerPass())
		{
			managerMenu();
		}
	}
}

int main()
{
	//��ʼ���û��ļ�
	headCustomer->checkCustomerFile();
	//��ʼ������Ա�ļ�
	onlyAdmin->checkAdminFile();
	//��ʼ�������ļ�
	onlyManager->checkManagerFile();
	//��ʼ�������ļ�
	onlyAgent->checkAgentFile();
	//��ʼ����Ʊ�ļ�
	checkTicketFile();
	//��ʼ�������ļ�
	checkFlightFile();
	cout << "--------------------" << endl;

	//�˵�
	while (true)
	{
		cout << "please choose your identity" << endl;
		cout << "1. admin" << endl
			<< "2. manager" << endl
			<< "3. agent" << endl
			<< "4. customer" << endl
			<< "0. exit" << endl
			<< "enter: ";
		int choose = inputNumFun(0, 4);
		if (choose == 0) {//����
			break;
		}
		else if (choose == 1)//����Ա
		{
			adminIdentity();
		}
		else if (choose == 2)//����
		{
			system("cls");
			managerIdentity();
		}
		else if (choose == 3)//����
		{
			system("cls");
			agentIdentity();
		}
		else if (choose == 4)//�û�
		{
			system("cls");
			customerIdentity();
		}

	}
	return 0;

}
