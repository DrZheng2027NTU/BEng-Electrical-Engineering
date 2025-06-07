#pragma once
#include"tools.h"


struct flight
{
	//航班号
	string flight_id = "";
	//出发 到达 地名
	string depart = "";
	string arrive = "";
	//年-月-日 //时:分
	int departDate[5] = { {0} };
	int arriveDate[5] = { {0} };
	//票价
	double price = 0;
	//机型
	int type[2] = { 0 };
	int totalSeat = 0;
	int remainSeat = 0;
	//座位及占有情况（-1表示这个座位不存在，0表示这个座位是空的，有用户购买则输入其id号）
	int seat[100][12] = { {-1} };
	//是否取消
	bool ifCancel = false;
	//链表
	flight* next = nullptr;
};


//创建flight文件，没有则自动创建，有则显示存在√
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

//从文件里读flight√
void readFlight(flight** head)
{
	ifstream fin("flight.txt"); // 打开文件以读取
	if (!fin.is_open()) {
		cerr << "Error: Could not open the file 'flight.txt'." << endl;
		return;
	}

	flight* last = nullptr;
	flight* newFlight;


	while (!fin.eof())
	{
		newFlight = new flight; // 创建一个新的航班结构体实例

		// 航班号
		if (!(fin >> newFlight->flight_id))
			break;
		//出发到达名字
		fin >> newFlight->depart;
		fin >> newFlight->arrive;
		//出发到达时间
		for (int i = 0; i < 5; i++)
		{
			fin >> newFlight->departDate[i];
		}
		for (int i = 0; i < 5; i++)
		{
			fin >> newFlight->arriveDate[i];
		}
		//价格
		fin >> newFlight->price;
		//座位类型
		fin >> newFlight->type[0];
		fin >> newFlight->type[1];
		//座位数量
		fin >> newFlight->totalSeat;
		fin >> newFlight->remainSeat;
		//座位状态初始化
		for (int i = 0; i < 100; ++i) {
			for (int j = 0; j < 12; ++j) {
				fin >> newFlight->seat[i][j];
			}
		}
		//是否取消
		fin >> newFlight->ifCancel;

		newFlight->next = nullptr;

		// 将新结点链接到链表中
		if (*head == nullptr) {
			*head = newFlight; // 如果链表为空，新结点是头结点
		}
		else {
			last->next = newFlight; // 否则，链接到上一个结点的 next
		}
		last = newFlight; // 更新 last 为当前的新结点
	}

	fin.close(); // 关闭文件
}

//航班写入文件√
void writeFlight(flight* head)
{
	ofstream fout("flight.txt");
	flight* current = head;
	while (current != nullptr)
	{
		// 航班号
		fout << current->flight_id << " ";
		//出发到达名字
		fout << current->depart << " ";
		fout << current->arrive << " ";
		//出发到达时间
		for (int i = 0; i < 5; i++)
		{
			fout << current->departDate[i] << " ";
		}
		for (int i = 0; i < 5; i++)
		{
			fout << current->arriveDate[i] << " ";
		}
		//价格
		fout << current->price << " ";
		//座位类型
		fout << current->type[0] << " ";;
		fout << current->type[1] << " ";;
		//座位数量
		fout << current->totalSeat << " ";
		fout << current->remainSeat << " ";
		//座位状态初始化
		for (int i = 0; i < 100; ++i) {
			for (int j = 0; j < 12; ++j) {
				fout << current->seat[i][j] << " ";
			}
		}
		//是否取消
		fout << current->ifCancel;
		// 换行以写入下一个航班信息
		fout << endl;
		// 移动到下一个节点
		current = current->next;
	}
	fout.close(); // 关闭文件
}

//打印所有航班 √
void showFlight(flight* head)
{
	// 设置每列的宽度
	int flightIdWidth = 12, departWidth = 12, arriveWidth = 12;
	int departTimeWidth = 15, arriveTimeWidth = 15, priceWidth = 12;
	int planeTypeWidth = 12, totalSeatWidth = 15, remainSeatWidth = 15;
	int ifCancelWidth = 12;
	//总长度
	int sum = 6 * 12 + 6 * 15;

	//格式化输出标题
	cout << endl << endl
		<< right << setw(flightIdWidth) << "flightId" << right << setw(departWidth) << "depart"
		<< right << setw(arriveWidth) << "arrive" << right << setw(departTimeWidth) << "departDate"
		<< right << setw(departTimeWidth) << "departHour" << right << setw(arriveTimeWidth) << "arriveDate"
		<< right << setw(arriveTimeWidth) << "arriveHour" << right << setw(priceWidth) << "price"
		<< right << setw(planeTypeWidth) << "type" << right << setw(totalSeatWidth) << "totalSeat"
		<< right << setw(remainSeatWidth) << "remainSeat" << right << setw(ifCancelWidth) << "condition"
		<< endl;

	// 打印分隔线
	cout << setfill('-') << setw(sum) << "" << endl;
	// 重置填充字符为默认的空格
	cout << setfill(' ');

	// 打印每行数据
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

//返回搜索结果
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