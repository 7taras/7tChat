#pragma once

#include <iostream>
#include <string>
#include <vector>

class User
{
public:
	User() = default;

	int getID();
	std::string& getName();
	std::string& getUserame();
	std::string& getPassword();

	void setID(int i);
	void setName(std::string& n);
	void setUsername(std::string& u);
	void setPassword(std::string& p);

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