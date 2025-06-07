#pragma once
#include"tools.h"
#include"ticket.h"


class customer
{
private:
	//名字
	string _customerName;
	//密码
	string _customerPassword;
	//此用户的机票链表
	ticket* _customerTicketHead;
	//用户链表
	customer* _next;

public:
	//创建新用户的时候，让用户输入自己的名字和密码，并传递到这个函数
	customer(string customer_name = "", string customer_password = "")
	{
		_customerName = customer_name;
		_customerPassword = customer_password;
		_customerTicketHead = nullptr;
		_next = nullptr;
	}

	//初始化文件
	void checkCustomerFile();

	//新用户,用户链表+空的新用户指针
	bool ifSameCustomer(customer* head, customer* newCustomer);

	bool ifNameExist(customer* head, string name);

	//老用户登录
	bool loginCustomer(string Name, string Password, customer* head);

	//添加进链表
	void addCustomer(customer** head, customer* newCustomer);

	//用户链表写入文件
	void writeCustomer(customer* head);

	//读取用户的账户密码
	void readCustomer(customer** head);


	//在这个函数内部读取到文件内容后，将链表传递给私有变量中的head指针，
	//读的是此用户的所有票
	void readCustomerTicket(customer* thisCustomer, ticket* headTicket);

	//查看此人所有的票
	//访问head指针，读出此用户的票
	void showCustomerTicket(customer thisCustomer);


};


//初始化文件
void customer::checkCustomerFile()
{
	//customer.txt
	//检查是否已经有这个文件
	//如果没有，创建一个空文件，然后关闭
	//如果有，直接退出，
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

//用户登录
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

//判断是否id重复
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

//新用户添加进链表
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

//写入用户链表
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


//读取用户链表
void customer::readCustomer(customer** head)
{
	ifstream fin("customer.txt"); // 打开文件以读取
	if (!fin.is_open()) {
		cerr << "Error: Could not open the file 'customer.txt'." << endl;
		return;
	}

	customer* last = nullptr;

	while (true) {
		customer* newCustomer = new customer;
		if (!(fin >> newCustomer->_customerName)) {
			delete newCustomer; // 释放未使用的内存
			break;
		}
		fin >> newCustomer->_customerPassword;
		newCustomer->_next = nullptr;
		newCustomer->_customerTicketHead = nullptr;

		// 将新结点链接到链表中
		if (*head == nullptr) {
			*head = newCustomer; // 如果链表为空，新结点是头结点
		}
		else {
			last->_next = newCustomer; // 否则，链接到上一个结点的 next
		}
		last = newCustomer; // 更新 last 为当前的新结点
	}
	fin.close();
}

//读取用户自己的票
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

