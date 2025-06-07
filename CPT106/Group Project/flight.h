#pragma once
#include"tools.h"


struct flight
{
	//�����
	string flight_id = "";
	//���� ���� ����
	string depart = "";
	string arrive = "";
	//��-��-�� //ʱ:��
	int departDate[5] = { {0} };
	int arriveDate[5] = { {0} };
	//Ʊ��
	double price = 0;
	//����
	int type[2] = { 0 };
	int totalSeat = 0;
	int remainSeat = 0;
	//��λ��ռ�������-1��ʾ�����λ�����ڣ�0��ʾ�����λ�ǿյģ����û�������������id�ţ�
	int seat[100][12] = { {-1} };
	//�Ƿ�ȡ��
	bool ifCancel = false;
	//����
	flight* next = nullptr;
};


//����flight�ļ���û�����Զ�������������ʾ���ڡ�
void checkFlightFile()
{
	ifstream file("flight.txt");
	if (file) {
		cout << "Flight file exist..." << endl;
	}
	else {
		ofstream outfile("flight.txt");
		if (!outfile.is_open()) {
			cerr << "Unable to create file";
		}
		else {
			cout << "Flight flie initialized success..." << endl;
		}
	}
}

//���ļ����flight��
void readFlight(flight** head)
{
	ifstream fin("flight.txt"); // ���ļ��Զ�ȡ
	if (!fin.is_open()) {
		cerr << "Error: Could not open the file 'flight.txt'." << endl;
		return;
	}

	flight* last = nullptr;
	flight* newFlight;


	while (!fin.eof())
	{
		newFlight = new flight; // ����һ���µĺ���ṹ��ʵ��

		// �����
		if (!(fin >> newFlight->flight_id))
			break;
		//������������
		fin >> newFlight->depart;
		fin >> newFlight->arrive;
		//��������ʱ��
		for (int i = 0; i < 5; i++)
		{
			fin >> newFlight->departDate[i];
		}
		for (int i = 0; i < 5; i++)
		{
			fin >> newFlight->arriveDate[i];
		}
		//�۸�
		fin >> newFlight->price;
		//��λ����
		fin >> newFlight->type[0];
		fin >> newFlight->type[1];
		//��λ����
		fin >> newFlight->totalSeat;
		fin >> newFlight->remainSeat;
		//��λ״̬��ʼ��
		for (int i = 0; i < 100; ++i) {
			for (int j = 0; j < 12; ++j) {
				fin >> newFlight->seat[i][j];
			}
		}
		//�Ƿ�ȡ��
		fin >> newFlight->ifCancel;

		newFlight->next = nullptr;

		// ���½�����ӵ�������
		if (*head == nullptr) {
			*head = newFlight; // �������Ϊ�գ��½����ͷ���
		}
		else {
			last->next = newFlight; // �������ӵ���һ������ next
		}
		last = newFlight; // ���� last Ϊ��ǰ���½��
	}

	fin.close(); // �ر��ļ�
}

//����д���ļ���
void writeFlight(flight* head)
{
	ofstream fout("flight.txt");
	flight* current = head;
	while (current != nullptr)
	{
		// �����
		fout << current->flight_id << " ";
		//������������
		fout << current->depart << " ";
		fout << current->arrive << " ";
		//��������ʱ��
		for (int i = 0; i < 5; i++)
		{
			fout << current->departDate[i] << " ";
		}
		for (int i = 0; i < 5; i++)
		{
			fout << current->arriveDate[i] << " ";
		}
		//�۸�
		fout << current->price << " ";
		//��λ����
		fout << current->type[0] << " ";;
		fout << current->type[1] << " ";;
		//��λ����
		fout << current->totalSeat << " ";
		fout << current->remainSeat << " ";
		//��λ״̬��ʼ��
		for (int i = 0; i < 100; ++i) {
			for (int j = 0; j < 12; ++j) {
				fout << current->seat[i][j] << " ";
			}
		}
		//�Ƿ�ȡ��
		fout << current->ifCancel;
		// ������д����һ��������Ϣ
		fout << endl;
		// �ƶ�����һ���ڵ�
		current = current->next;
	}
	fout.close(); // �ر��ļ�
}

//��ӡ���к��� ��
void showFlight(flight* head)
{
	// ����ÿ�еĿ��
	int flightIdWidth = 12, departWidth = 12, arriveWidth = 12;
	int departTimeWidth = 15, arriveTimeWidth = 15, priceWidth = 12;
	int planeTypeWidth = 12, totalSeatWidth = 15, remainSeatWidth = 15;
	int ifCancelWidth = 12;
	//�ܳ���
	int sum = 6 * 12 + 6 * 15;

	//��ʽ���������
	cout << endl << endl
		<< right << setw(flightIdWidth) << "flightId" << right << setw(departWidth) << "depart"
		<< right << setw(arriveWidth) << "arrive" << right << setw(departTimeWidth) << "departDate"
		<< right << setw(departTimeWidth) << "departHour" << right << setw(arriveTimeWidth) << "arriveDate"
		<< right << setw(arriveTimeWidth) << "arriveHour" << right << setw(priceWidth) << "price"
		<< right << setw(planeTypeWidth) << "type" << right << setw(totalSeatWidth) << "totalSeat"
		<< right << setw(remainSeatWidth) << "remainSeat" << right << setw(ifCancelWidth) << "condition"
		<< endl;

	// ��ӡ�ָ���
	cout << setfill('-') << setw(sum) << "" << endl;
	// ��������ַ�ΪĬ�ϵĿո�
	cout << setfill(' ');

	// ��ӡÿ������
	while (head != nullptr)
	{
		cout << right << setw(flightIdWidth) << head->flight_id
			<< right << setw(departWidth) << head->depart << right << setw(arriveWidth) << head->arrive
			<< right << setw(departTimeWidth) << convertYear(head->departDate) << right << setw(departTimeWidth) << convertHour(head->departDate)
			<< right << setw(arriveTimeWidth) << convertYear(head->arriveDate) << right << setw(arriveTimeWidth) << convertHour(head->arriveDate)
			<< right << setw(priceWidth) << head->price
			<< right << setw(planeTypeWidth) << convertType(head->type)
			<< right << setw(totalSeatWidth) << head->totalSeat
			<< right << setw(remainSeatWidth) << head->remainSeat;

		if (head->ifCancel == false)
		{
			cout << right << setw(ifCancelWidth) << GREEN << "Active" << RESET << endl;
		}
		else
		{
			cout << right << setw(ifCancelWidth) << RED << "Canceled" << RESET << endl;
		}

		head = head->next;
	}
	cout << endl << endl;
}

//�����������
flight* searchFlight(flight* headFlight, string depart, string arrive)
{
	flight* filterFlight = nullptr;
	flight* currentFlight = headFlight;
	flight* lastAddedFlight = nullptr;

	while (currentFlight != nullptr) {
		if (currentFlight->depart == depart && currentFlight->arrive == arrive && !currentFlight->ifCancel)
		{
			// Create a new flight node to add to the filtered list
			flight* newFlight = new flight(*currentFlight);
			newFlight->next = nullptr;

			if (filterFlight == nullptr) {
				// Initialize the filtered list with the first matching flight
				filterFlight = newFlight;
				lastAddedFlight = newFlight;
			}
			else {
				// Add to the end of the filtered list
				lastAddedFlight->next = newFlight;
				lastAddedFlight = newFlight;
			}
		}
		currentFlight = currentFlight->next;
	}

	return filterFlight;
}

flight* searchFlightByID(flight* filterFlight, string flightID)
{
	flight* currentFlight = filterFlight;

	while (currentFlight != nullptr) {
		if (currentFlight->flight_id == flightID) {
			return currentFlight;
		}
		currentFlight = currentFlight->next;
	}

	return nullptr; // Return nullptr if the flight ID is not found
}

void showSpecificFlightSeat(flight* SpecificFlight) {
	int length = SpecificFlight->type[0];
	int width = SpecificFlight->type[1];

	for (int i = 0; i < length; ++i) {
		for (int j = 0; j < width; ++j) {
			char colChar = 'A' + j;
			std::ostringstream seatNumberStream;
			seatNumberStream << colChar << std::setw(3) << std::setfill('0') << (i + 1);
			std::string seatNumber = seatNumberStream.str();

			if (SpecificFlight->seat[i][j] == -1) {
				std::cout << std::setw(7) << " ";
			}
			else if (SpecificFlight->seat[i][j] == 0) {
				std::cout << GREEN << std::setw(7) << seatNumber << RESET;
			}
			else {
				std::cout << RED << std::setw(7) << seatNumber << RESET;
			}
		}
		std::cout << std::endl;
	}
	std::cout << std::endl << GREEN << "Green" << RESET << ": Available to choose" << std::endl;
	std::cout << RED << "Red" << RESET << ": Not available to choose" << std::endl;
}

void synFlight(flight*& headFlight, flight* specificFlight) {
	flight* currentFlight = headFlight;

	while (currentFlight != nullptr) {
		if (currentFlight->flight_id == specificFlight->flight_id) {
			// Synchronize seat states
			for (int i = 0; i < specificFlight->type[0]; ++i) {
				for (int j = 0; j < specificFlight->type[1]; ++j) {
					currentFlight->seat[i][j] = specificFlight->seat[i][j];
				}
			}
			// Synchronize other fields if needed
			currentFlight->totalSeat = specificFlight->totalSeat;
			currentFlight->remainSeat = specificFlight->remainSeat;

			return; // Synchronization complete
		}
		currentFlight = currentFlight->next;
	}

	std::cout << "Flight with ID " << specificFlight->flight_id << " not found in the headFlight list." << std::endl;
}