#pragma once

#include <iostream>
#include <string>
#include <vector>

class User
{
public:
	User() = default;
	User(std::string& n, std::string& u, std::string& p) : name(n), username(u), password(p)
	{
	}

	int getID();
	std::string getName();

	bool inputNameForNewUser();
	bool inputUsernameForNewUser();
	bool inputUsernameForLogin(const std::vector<User>& box);
	bool inputPasswordForNewUser();
	bool inputPasswordForLogin(const std::vector<User>& box);
	bool inputUsernameForNewUser(const std::vector<User>&);
	bool add(std::vector<User>& box);
	int inputReceiversUsername(const std::vector<User>& box);
	
private:
	int id{ 0 };
	std::string name;
	std::string username;
	std::string password;
};