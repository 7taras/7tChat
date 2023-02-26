
#include <iostream>
#include <vector>
#include <string>
#include <conio.h> // for _getch()
#include "Message.h"
#include "User.h"

std::vector<User> usersBox;          // keeps all users
std::vector<Message> messagesBox;    // keeps all messages

int select012()
{
    char ch = 'X';
    std::cin.clear();
    std::cout << ' ';
    while ((ch != '0') && (ch != '1') && (ch != '2'))
    {
        std::cout << char(0x08);
        ch = _getch();
        std::cout << ch;
    }
    std::cout << '\n';
    if (ch == '0') return 0;
    if (ch == '1') return 1;
    if (ch == '2') return 2;
    return -1;
}

int select01234()
{
    char ch = 'X';
    std::cin.clear();
    std::cout << ' ';
    while ((ch != '0') && (ch != '1') && (ch != '2') && (ch != '3') && (ch != '4'))
    {
        std::cout << char(0x08);
        ch = _getch();
        std::cout << ch;
    }
    std::cout << '\n';
    if (ch == '0') return 0;
    if (ch == '1') return 1;
    if (ch == '2') return 2;
    if (ch == '3') return 3;
    if (ch == '4') return 4;
    return -1;
}

void login()
{
    User currentUser;
    while (!currentUser.inputUsernameForLogin(usersBox));
    while (!currentUser.inputPasswordForLogin(usersBox));

    std::cout << "LOGIN success\n";
    bool flag = true;
    while(flag)
    {
        std::cout << "Please, press 1 to BROADCAST MESSAGE, 2 to PRIVATE MESSAGE, " <<
            "3 to READ NEW MESSAGES, 4 to READ ALL MESSAGES, 0 to EXIT TO THE MENU\nYour choice : ";

        Message temp;
        int tempRecieverID{ 0 };
        switch (select01234())
        {
        case 1:
            temp.broadcastMessage(currentUser, messagesBox);
            break;
        case 2:
            
            while (!tempRecieverID)
            {
                tempRecieverID = currentUser.inputReceiversUsername(usersBox);
            }
            temp.privateMessage(currentUser, messagesBox, tempRecieverID);
            break;
        case 3:
            for (auto& it : messagesBox)
            {
                if ( ( (it.idReceiver == currentUser.getID()) || (it.idReceiver == 0) ) && !(it.isRead))
                {
                    char messageTime[26];
                    ctime_s(messageTime, sizeof(messageTime), &it.messageTime);
                    messageTime[24] = ' ';
                    std::string transmitterUsername = usersBox.at(it.idSender - 1).getName();
                    std::cout << messageTime << ":: " << transmitterUsername <<
                        " wrote you \"" << it.text << "\"\n";
                    if (it.idReceiver != 0)
                    {
                        it.isRead = true;
                    }
                }
            }
            break;
        case 4:
            for (auto& it : messagesBox)
            {
                if ((it.idReceiver == currentUser.getID()) || (it.idReceiver == 0))
                {
                    char messageTime[26];
                    ctime_s(messageTime, sizeof(messageTime), &it.messageTime);
                    messageTime[24] = ' ';
                    std::string transmitterUsername = usersBox.at(it.idSender - 1).getName();
                    std::cout << messageTime << ":: " << transmitterUsername <<
                        " wrote you \"" << it.text << "\"\n";
                    if (it.idReceiver != 0)
                    {
                        it.isRead = true;
                    }
                }
            }
            break;
        case 0:
            flag = false;
            break;
        default:
            return;
        }
    }
    return;
}

void createNewUser()
{
    User newUser;
    while (!newUser.inputNameForNewUser());
    while (!newUser.inputUsernameForNewUser(usersBox));
    while (!newUser.inputPasswordForNewUser());
    newUser.add(usersBox);
    return;
}

int main()
{
    std::string n{ "Taras K." };
    std::string u{ "taras" };
    std::string u1{ "rabbit" };
    std::string p{ "12345" };
    User first(n, u, p);
    first.add(usersBox);
    User second(n, u1, p); 
    second.add(usersBox);

    std::cout << "Welcome to the 7tChat!\n";

    bool menuFlag = true;
    while(menuFlag)
    {
        std::cout << "Please, press 1 to LOGIN, 2 to CREATE ACCOUNT, 0 to EXIT THE CHAT\nYour choice: ";
        switch (select012())
        {
        case 1:
            login();
            break;
        case 2:
            createNewUser();
            break;
        case 0:
            return 0;
        default:
            return -1;
        }
    }

    std::cout << "the End\n";
    return 0;
}