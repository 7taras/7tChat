#pragma once

#include <string>
#include <iostream>
#include <ctime>
#include <vector>
#include "User.h"

class Message
{
public:
	void broadcastMessage(User& user, std::vector<Message>& box);
	void privateMessage(User& user, std::vector<Message>& box, int recID);

	time_t messageTime{ 0 };
	int idSender{ 0 };
	int idReceiver{ 0 };
	bool isRead{ false };
	std::string text;
};