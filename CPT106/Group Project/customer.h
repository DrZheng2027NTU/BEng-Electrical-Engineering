#pragma once
#include"tools.h"
#include"ticket.h"


class customer
{
private:
	//����
	string _customerName;
	//����
	string _customerPassword;
	//���û��Ļ�Ʊ����
	ticket* _customerTicketHead;
	//�û�����
	customer* _next;

public:
	//�������û���ʱ�����û������Լ������ֺ����룬�����ݵ��������
	customer(string customer_name = "", string customer_password = "")
	{
		_customerName = customer_name;
		_customerPassword = customer_password;
		_customerTicketHead = nullptr;
		_next = nullptr;
	}

	//��ʼ���ļ�
	void checkCustomerFile();

	//���û�,�û�����+�յ����û�ָ��
	bool ifSameCustomer(customer* head, customer* newCustomer);

	bool ifNameExist(customer* head, string name);

	//���û���¼
	bool loginCustomer(string Name, string Password, customer* head);

	//��ӽ�����
	void addCustomer(customer** head, customer* newCustomer);

	//�û�����д���ļ�
	void writeCustomer(customer* head);

	//��ȡ�û����˻�����
	void readCustomer(customer** head);


	//����������ڲ���ȡ���ļ����ݺ󣬽������ݸ�˽�б����е�headָ�룬
	//�����Ǵ��û�������Ʊ
	void readCustomerTicket(customer* thisCustomer, ticket* headTicket);

	//�鿴�������е�Ʊ
	//����headָ�룬�������û���Ʊ
	void showCustomerTicket(customer thisCustomer);


};


//��ʼ���ļ�
void customer::checkCustomerFile()
{
	//customer.txt
	//����Ƿ��Ѿ�������ļ�
	//���û�У�����һ�����ļ���Ȼ��ر�
	//����У�ֱ���˳���
	ifstream file("customer.txt");
	if (file)
	{
		cout << "customer file exist..." << endl;

	}

	else
	{
		ofstream fout("customer.txt");
		if (!fout.is_open())
		{
			cerr << "Unable to create Customer file";
		}
		else
		{
			cout << "Customer flie initialized success..." << endl;
		}
	}
}

//�û���¼
bool customer::loginCustomer(string Name, string Password, customer* head)
{
	while (head != nullptr)
	{
		if (head->_customerName == Name && head->_customerPassword == Password)
		{
			return true;
		}
		head = head->_next;
	}
	return false;
}

//�ж��Ƿ�id�ظ�
bool customer::ifSameCustomer(customer* head, customer* newCustomer)
{
	bool noSameName = false;
	while (head != nullptr)
	{
		if (head->_customerName == newCustomer->_customerName)
		{
			noSameName = true;
			break;
		}
		head = head->_next;
	}
	return noSameName;
}


bool customer::ifNameExist(customer* head, string name)
{
	bool NameExist = false;
	while (head != nullptr)
	{
		if (head->_customerName == name)
		{
			NameExist = true;
			break;
		}
		head = head->_next;
	}
	return NameExist;
}

//���û���ӽ�����
void customer::addCustomer(customer** head, customer* newCustomer)
{
	if (*head == nullptr)
		*head = newCustomer;
	else
	{
		customer* current = *head;
		while (current->_next != nullptr) {
			current = current->_next;
		}
		current->_next = newCustomer;
	}
}

//д���û�����
void customer::writeCustomer(customer* head)
{
	ofstream fout("customer.txt");
	while (head != nullptr)
	{
		fout << head->_customerName << " ";
		fout << head->_customerPassword << " ";
		fout << endl;
		head = head->_next;
	}
	fout.close();
}


//��ȡ�û�����
void customer::readCustomer(customer** head)
{
	ifstream fin("customer.txt"); // ���ļ��Զ�ȡ
	if (!fin.is_open()) {
		cerr << "Error: Could not open the file 'customer.txt'." << endl;
		return;
	}

	customer* last = nullptr;

	while (true) {
		customer* newCustomer = new customer;
		if (!(fin >> newCustomer->_customerName)) {
			delete newCustomer; // �ͷ�δʹ�õ��ڴ�
			break;
		}
		fin >> newCustomer->_customerPassword;
		newCustomer->_next = nullptr;
		newCustomer->_customerTicketHead = nullptr;

		// ���½�����ӵ�������
		if (*head == nullptr) {
			*head = newCustomer; // �������Ϊ�գ��½����ͷ���
		}
		else {
			last->_next = newCustomer; // �������ӵ���һ������ next
		}
		last = newCustomer; // ���� last Ϊ��ǰ���½��
	}
	fin.close();
}

//��ȡ�û��Լ���Ʊ
void customer::readCustomerTicket(customer* thisCustomer, ticket* headTicket)
{
	ticket* currentTicket = headTicket;  // Start at the head of the ticket list
	ticket* lastAddedTicket = nullptr;  // Track the last ticket added to the new list

	while (currentTicket != nullptr) {  // Traverse the ticket linked list
		// Check if the ticket belongs to the customer based on the name
		if (currentTicket->_customerName == thisCustomer->_customerName) {
			// Create a new ticket node for customer's list
			ticket* newTicket = new ticket(*currentTicket);  // Copy constructor assumed

			if (thisCustomer->_customerTicketHead == nullptr) {
				// If this is the first ticket found, initialize the head
				thisCustomer->_customerTicketHead = newTicket;
			}
			else {
				// Otherwise, add to the end of the new list
				lastAddedTicket->next = newTicket;
			}

			lastAddedTicket = newTicket;  // Update the last added ticket
		}
		currentTicket = currentTicket->next;  // Move to the next ticket
	}

	// Ensure the last ticket's next is nullptr to terminate the new list
	if (lastAddedTicket != nullptr) {
		lastAddedTicket->next = nullptr;
	}
}


void customer::showCustomerTicket(customer thisCustomer)
{
	ticket* currentTicket = thisCustomer._customerTicketHead; // Start at the head of the customer's ticket list

	// Header
	cout << right << setw(15) << "Ticket ID" << setw(20) << "Customer Name" << setw(15) << "Flight ID"
		<< setw(10) << "Seat ID" << setw(10) << "Price" << setw(10) << "Paid" << setw(10) << "Status" << endl; 

	// Traverse the linked list of customer tickets
	while (currentTicket != nullptr) {
		// Print each ticket's details
		cout << right
			<< setw(15) << currentTicket->ticket_id
			<< setw(20) << currentTicket->_customerName
			<< setw(15) << currentTicket->flight_id
			<< setw(10) << currentTicket->seat_id
			<< setw(10) << currentTicket->price;
		if (currentTicket->ifpay == true) cout << GREEN << setw(10) << "Pay" << RESET;
		else cout << RED << setw(10) << "Not Pay" << RESET;

		if (currentTicket->ifcanceled == false) cout << GREEN << setw(10)  << "Active" << RESET<<endl;
		else cout << RED << setw(10)  << "Cancel" << RESET << endl;
		currentTicket = currentTicket->next; // Move to the next ticket
	}
}

