#include "Message.h"

void Message::broadcastMessage(User& user, std::vector<Message>& box)
{
	idSender = user.getID();
	idReceiver = 0;
	isRead = false;
	std::cout << "Please, type your BROADCAST MESSAGE: ";
	std::getline(std::cin, text);
	messageTime = time(0);
	box.push_back(*this);
	std::cout << "Your broadcast message was successfully transmitted.\n";
	return;
}

void Message::privateMessage(User& user, std::vector<Message>& box, int recID)
{
	idSender = user.getID();
	idReceiver = recID;
	isRead = false;
	std::cout << "Please, type your PRIVATE MESSAGE: ";
	std::getline(std::cin, text);
	messageTime = time(0);
	box.push_back(*this);
	std::cout << "Your private message was successfully transmitted.\n";
	return;
}