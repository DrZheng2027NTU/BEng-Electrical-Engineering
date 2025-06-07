#pragma once
#include "tools.h"
#include"flight.h"
//manager ptrMan;//因为不需要对航班信息做出修改和调整，因此不需要定义这个对象
class manager
{
private:
    string _managerID;
    string _managerPass;

    int planeNum[100];
    string planeType[100];
    int customerNum[100];
    string flightId[100];
    double totalIncome;
public:
    manager();
    //查询每种航班数量
    void showPlaneNum(flight* head);
    //一个航班里的乘客数量
    void showCustomerNum(flight* head, string FlightId);
    flight* findTypeNum(int L, int W, flight* head); 
    void setPlane(string type, int PlaneNum);
    double getIncome();
    void setFlight(string FlightId, int CustomerNum);
    void setIncome(int Income);
    void checkManagerFile();
    void readManager();
    bool compareManagerID();
    bool compareManagerPass();
    void calculateIncome(ticket* head);
    void showIncome();

};
manager::manager()
{
    for (int i = 0; i < 100; i++)
    {
        planeNum[i] = 0;
        customerNum[i] = 0;
        flightId[i] = "Not exist";
        planeType[i] = "Not exist";
    }
    totalIncome = 0.0;
}
void manager::showPlaneNum(flight* head)
{
    int count = 0;
    flight* current = head;
    while (current != nullptr)
    {
        count++;
        current = current->next;
    }
    cout << "Total flights: " << count << endl;
}
void manager::showCustomerNum(flight* head, string FlightId)
{
    flight* current = head;
    while (current != nullptr)
    {
        if (current->flight_id == FlightId)
        {
            int count = 0;
            for (int i = 0; i < 100; i++)
            {
                for (int j = 0; j < 12; j++)
                {
                    if (current->seat[i][j] > 0)
                        count++;
                }
            }
            cout << "Number of passengers in flight " << FlightId << ": " << count << endl;
            return;
        }
        current = current->next;
    }
    cout << "Flight " << FlightId << " not found." << endl;
}
void manager::setPlane(string type, int PlaneNum)
{
    bool updated = false; // 用于标记是否更新了数据
    for (int i = 0; i < 100; i++)
    {
        if (planeType[i] == "Not exist" || planeType[i] == type)
        {
            planeType[i] = type;
            planeNum[i] = PlaneNum;
            updated = true; // 标记已经更新
            break; // 退出循环
        }
    }
    if (!updated)
    {
        cout << "No more space to add new plane types." << endl;
    }
}

void manager::setFlight(string FlightId, int CustomerNum)
{
    for (int j = 0; j < 100; j++)
    {
        if (flightId[j] == "Not exist")
        {
            flightId[j] = FlightId;
            customerNum[j] = CustomerNum;
            return;
        }
        else if (flightId[j] == FlightId)
        {
            customerNum[j] = CustomerNum;
            return;
        }
    }
    cout << "No more space to add new flights." << endl;
}


void manager::checkManagerFile() 
{
    ifstream file("manager.txt");
    if (file) {
        cout << "Manager file exist..." << endl;
    }
    else {
        ofstream fout("manager.txt");
        if (!fout.is_open()) {
            cerr << "Unable to create Manager file";
        }
        else {
            string managerId, managerPass;
            cout << "please set the manager ID (no space) :";
            managerId = inputStrFun();
            cout << "please set the manager Password (no space) :";
            managerPass = inputStrFun();
            fout << managerId << " " << managerPass;
            cout << "Manager flie initialized success..." << endl;
        }
    }
}

void manager::readManager() {
    std::ifstream file("manager.txt");
    if (file)
    {
        file >> _managerID >> _managerPass;
    }
    else {
        cerr << "Failed to open manager file." << std::endl;
    }
    file.close();
}

bool manager::compareManagerID() {
    string managerId;
    cout << "please input the manager ID :";
    managerId = inputStrFun();
    if (managerId == _managerID) 
    {
        return true;
    }
    else {
        cout << "manager ID wrong, log out...";
        return false;
    }
}

bool manager::compareManagerPass() {
    string managerPass;
    cout << "please input the manager Password :";
    managerPass = inputStrFun();
    if (managerPass == _managerPass) {
        return true;
    }
    else {
        cout << "manager Password wrong, log out...";
        return false;
    }
}

void manager::calculateIncome(ticket* head) 
{
    totalIncome = 0.0;
    ticket* currentTicket = head;

    while (currentTicket != nullptr) {
        if (!currentTicket->ifcanceled && currentTicket->ifpay) {
            totalIncome += currentTicket->price;
        }
        currentTicket = currentTicket->next;
    }


}
void manager::showIncome()
{
    cout << "Total income is :" << totalIncome << endl;
}

flight* manager::findTypeNum(int L, int W,flight*head) 
{
    flight* newHead = nullptr; // New list head
    flight* lastAdded = nullptr; // Last added node in the new list

    flight* currentFlight = head;

    while (currentFlight != nullptr) {
        if (currentFlight->type[0] == L && currentFlight->type[1] == W) {
            // Create a new flight node and copy the current flight's data
            flight* newFlight = new flight(*currentFlight);
            newFlight->next = nullptr;

            // Add to the new list
            if (newHead == nullptr) {
                newHead = newFlight;
            }
            else {
                lastAdded->next = newFlight;
            }
            lastAdded = newFlight;
        }
        currentFlight = currentFlight->next;
    }

    return newHead;
}