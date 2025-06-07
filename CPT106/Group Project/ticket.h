#pragma once
#include "tools.h"

//机票信息，每张为单位
struct ticket
{
    //订单编号
    int ticket_id;
    //对应的用户
    string _customerName;
    //对应的航班id
    string flight_id;
    //对应的座位
    string seat_id;
    //对应的价格
    double price;
    //日期
    int departDate[5];
    int arriveDate[5];
    //支付状态
    bool ifpay;
    //是否已经取消
    bool ifcanceled;
    //链表
    ticket* next;
};

void checkTicketFile()
{
    ifstream file("ticket.txt");
    if (file.good()) {
        cout << "ticket file exists." << endl;
    }
    else {
        ofstream createFile("ticket.txt");
        createFile.close();
        cout << "initialized success!" << endl;
    }
}

void readTicket(ticket*& headTicket)
{
    ifstream file("ticket.txt");
    ticket* lastTicket = nullptr;

    while (!file.eof()) {
        ticket* newTicket = new ticket;
        file >> newTicket->ticket_id >> newTicket->_customerName >> newTicket->flight_id >> newTicket->seat_id
            >> newTicket->price; 
        for (int i = 0; i < 5; i++)
        {
            file >> newTicket->departDate[i];
        }
        for (int i = 0; i < 5; i++)
        {
            file >> newTicket->arriveDate[i];
        }
        file >> newTicket->ifpay >> newTicket->ifcanceled;
        newTicket->next = nullptr;

        if (file.fail()) {
            delete newTicket;
            break;
        }

        if (headTicket == nullptr) {
            headTicket = newTicket;
        }
        else {
            lastTicket->next = newTicket;
        }
        lastTicket = newTicket;
    }
    file.close();
}

void writeTicketFile(ticket* headTicket) {
    ofstream file("ticket.txt");
    ticket* currentTicket = headTicket;
    while (currentTicket != nullptr) {
        file << currentTicket->ticket_id << " "
            << currentTicket->_customerName << " "
            << currentTicket->flight_id << " "
            << currentTicket->seat_id << " "
            << currentTicket->price << " "
            << currentTicket->departDate[0]<<" "
            << currentTicket->departDate[1] << " "
            << currentTicket->departDate[2] << " "
            << currentTicket->departDate[3] << " "
            << currentTicket->departDate[4] << " "
            << currentTicket->arriveDate[0] << " "
            << currentTicket->arriveDate[1] << " "
            << currentTicket->arriveDate[2] << " "
            << currentTicket->arriveDate[3] << " "
            << currentTicket->arriveDate[4] << " "
            << currentTicket->ifpay << " "
            << currentTicket->ifcanceled << "\n";
        currentTicket = currentTicket->next;
    }
    file.close();
}


int generateUniqueTicketID(ticket* ticketHead)
{
    int newID = 10000001; // Start from 1xxxxxxx
    ticket* currentTicket = ticketHead;

    while (currentTicket != nullptr) {
        if (currentTicket->ticket_id >= newID) {
            newID = currentTicket->ticket_id + 1;
        }
        currentTicket = currentTicket->next;
    }

    return newID;
}

