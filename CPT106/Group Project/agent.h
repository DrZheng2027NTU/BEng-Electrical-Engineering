#pragma once
#include "tools.h"
#include "flight.h"
#include "ticket.h"


class agent
{
private:
	string agentId;
	string agentPassword;
	ticket* agentTicket;
	int ticketamount;
public:
	//construction of agent（注意！永远只在初始化时才调用它！）
	agent()
	{
		ticketamount = 0;
	}
	void checkAgentFile();
	void readAgent();
	bool loginAgent(string, string);
	void reserveSeat(flight*&, ticket*&, string, string);
	void cancelSeat(ticket*&, int, flight*&); 
	bool isTimeOverlap(int* start1, int* end1, int* start2, int* end2);
	void paySeat(ticket*&, int, flight*&);
	void checkIncome(int time1[2], int time2[2], ticket* headTicket);
};


void agent::checkAgentFile()
{
	ifstream file("agent.txt");
	if (file.good()) {
		std::cout << "agent file exists." << endl;
	}
	else {
		file.close();
		cout << "No agent file found. Please enter agent ID and password to initialize." << endl;
		string id, password;
		cout << "Enter Agent ID: ";
		id = inputStrFun();
		cout << "Enter Password: ";
		password = inputStrFun();

		ofstream outFile("agent.txt");
		outFile << id << " " << password;
		outFile.close();
		cout << "Agent file initialized successfully!" << endl;
	}
}

void agent::readAgent() {
	std::ifstream file("agent.txt");
	if (file) {
		file >> agentId >> agentPassword;
	}
	else {
		std::cerr << "Failed to open agent file." << std::endl;
	}
	file.close();
}

bool agent::loginAgent(string id, string password)
{
	if (id == agentId && password == agentPassword)
	{
		return true;
	}
	return false;
}

void agent::reserveSeat(flight*& specificFlight, ticket*& ticketHead, string seat, string name) {
	int col = seat[0] - 'A';
	int row = std::stoi(seat.substr(1)) - 1;

	if (row >= specificFlight->type[0] || col >= specificFlight->type[1] || specificFlight->seat[row][col] != 0) {
		std::cout << RED << "Seat " << seat << " is not available." << RESET << std::endl;
		return;
	}

	specificFlight->seat[row][col] = 1; // Mark the seat as occupied
	specificFlight->remainSeat = specificFlight->remainSeat - 1;

	// Create and initialize the new ticket
	ticket* newTicket = new ticket;
	newTicket->ticket_id = generateUniqueTicketID(ticketHead);
	newTicket->_customerName = name;
	newTicket->flight_id = specificFlight->flight_id;
	newTicket->seat_id = seat;
	newTicket->price = specificFlight->price;
	for (int i = 0; i < 5; i++)
	{
		newTicket->departDate[i] = specificFlight->departDate[i];
		newTicket->arriveDate[i] = specificFlight->arriveDate[i];
	}
	newTicket->ifpay = false;
	newTicket->ifcanceled = false;
	newTicket->next = nullptr;

	// Add the new ticket to the ticket list
	if (ticketHead == nullptr) {
		ticketHead = newTicket;
	}
	else {
		ticket* currentTicket = ticketHead;
		while (currentTicket->next != nullptr) {
			currentTicket = currentTicket->next;
		}
		currentTicket->next = newTicket;
	}

	std::cout << GREEN << "Seat " << seat << " reserved successfully for " << name << "." << RESET << std::endl;
	std::cout << "Ticket ID: " << newTicket->ticket_id << std::endl;
}

void agent::cancelSeat(ticket*& ticketHead, int ticketID, flight*& flightHead) 
{// Find the ticket and mark it as canceled
	ticket* currentTicket = ticketHead;
	while (currentTicket != nullptr) {
		if (currentTicket->ticket_id == ticketID) 
		{
			if (currentTicket->ifcanceled) {
				std::cout << "Ticket ID " << ticketID << " has been canceled and cannot be re-cancel." << std::endl;
				return;
			}
			else
			{
				currentTicket->ifcanceled = true;
				std::cout << "Ticket ID " << ticketID << " has been canceled." << std::endl;
			}
			
			// Check if the ticket has been paid
			if (currentTicket->ifpay) {
				std::cout << "Refund amount: $" << currentTicket->price << std::endl;
			}

			// Find the corresponding flight
			flight* currentFlight = flightHead;
			while (currentFlight != nullptr) {
				if (currentFlight->flight_id == currentTicket->flight_id) {
					// Parse the seat_id to get row and column
					int col = currentTicket->seat_id[0] - 'A';
					int row = std::stoi(currentTicket->seat_id.substr(1)) - 1;

					// Update the seat status to empty
					if (row < currentFlight->type[0] && col < currentFlight->type[1]) {
						currentFlight->seat[row][col] = 0; // Mark the seat as empty
						currentFlight->remainSeat += 1; // Increment remaining seats count
					}
					break;
				}
				currentFlight = currentFlight->next;
			}
			return;
		}
		currentTicket = currentTicket->next;
	}

	std::cout << "Ticket ID " << ticketID << " not found." << std::endl;
}

//新
bool agent::isTimeOverlap(int* start1, int* end1, int* start2, int* end2) {
	for (int i = 0; i < 5; ++i) {
		if (start1[i] < end2[i] && end1[i] > start2[i]) {
			return true;
		}
		if (start1[i] != start2[i]) {
			return start1[i] < start2[i];
		}
	}
	return false;
}


void agent::paySeat(ticket*& ticketHead, int ticketID, flight*& flightHead) 
{ // Find the ticket and mark it as paid
	ticket* currentTicket = ticketHead;
	ticket* targetTicket = nullptr;

	while (currentTicket != nullptr) {
		if (currentTicket->ticket_id == ticketID) {
			targetTicket = currentTicket;
			break;
		}
		currentTicket = currentTicket->next;
	}

	if (targetTicket == nullptr) {
		std::cout << "Ticket ID " << ticketID << " not found." << std::endl;
		return;
	}

	if (targetTicket->ifpay) {
		std::cout << "Ticket ID " << ticketID << " has been paid already." << std::endl;
		return;
	}
	if (targetTicket->ifcanceled) {
		std::cout << "Ticket ID " << ticketID << " has been canceled and cannot be paid." << std::endl;
		return;
	}

	// Find the corresponding flight for the target ticket
	flight* targetFlight = nullptr;
	flight* currentFlight = flightHead;
	while (currentFlight != nullptr) {
		if (currentFlight->flight_id == targetTicket->flight_id) {
			targetFlight = currentFlight;
			break;
		}
		currentFlight = currentFlight->next;
	}

	if (targetFlight == nullptr) {
		std::cout << "Corresponding flight for ticket ID " << ticketID << " not found." << std::endl;
		return;
	}

	// Check for overlapping flights for the same customer
	currentTicket = ticketHead;
	while (currentTicket != nullptr) {
		if (currentTicket->_customerName == targetTicket->_customerName && currentTicket->ifpay && !currentTicket->ifcanceled && currentTicket != targetTicket) {
			// Find the corresponding flight for this ticket
			currentFlight = flightHead;
			while (currentFlight != nullptr) {
				if (currentFlight->flight_id == currentTicket->flight_id) {
					break;
				}
				currentFlight = currentFlight->next;
			}

			if (currentFlight != nullptr) {
				if (isTimeOverlap(targetFlight->departDate, targetFlight->arriveDate, currentFlight->departDate, currentFlight->arriveDate)) {
					std::cout << "Customer " << targetTicket->_customerName << " already has a ticket for an overlapping flight." << std::endl;
					return;
				}
			}
		}
		currentTicket = currentTicket->next;
	}

	targetTicket->ifpay = true;
	std::cout << "Ticket ID " << ticketID << " has been paid successfully." << std::endl;
}


void agent::checkIncome(int time1[2], int time2[2], ticket* headTicket)
{
	int soldTicketsCount = 0;
	double totalIncome = 0.0;

	ticket* currentTicket = headTicket;

	while (currentTicket != nullptr) {
		if (currentTicket->ifpay && !currentTicket->ifcanceled) {
			if (isWithinRange(currentTicket->departDate, time1, time2)) {
				soldTicketsCount++;
				totalIncome += currentTicket->price;
			}
		}
		currentTicket = currentTicket->next;
	}

	std::cout << "Total tickets sold: " << soldTicketsCount << std::endl;
	std::cout << "Total income: $" << totalIncome << std::endl;

}
