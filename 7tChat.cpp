
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <conio.h> // for _getch()
#include "Message.h"
#include "User.h"

std::vector<User> usersBox;          // keeps all users
std::vector<Message> messagesBox;    // keeps all messages

// функция для ввода только 1 либо 2 либо 0
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

// функция для ввода только 1, 2, 3, 4 или 0, остальной ввод игнорируется
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

// функция введения логина/пароля
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

// создаем нового пользвателя
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
    std::cout << "Welcome to the 7tChat!\n";

    // читаем содержимое контейнера с данными пользователей
    std::ifstream readUsers("users.dat", std::ios::in);
    if (!readUsers)
    {
        std::cout << "File \"user.dat\" couldn\'t be read.\n";
    }
    else
    {
        std::string header;
        readUsers >> header;
        if (header == "users.dat")
        {
            int usersLinesSize{ 0 };
            readUsers >> usersLinesSize;

            int tempID{ 0 };
            std::string tempName;
            std::string tempUsername;
            std::string tempPassword;
            User tempUser;
            for (int i = 0; i < usersLinesSize; ++i)
            {
                readUsers >> tempID;
                std::getline(readUsers, tempName);
                std::getline(readUsers, tempName);
                readUsers >> tempUsername >> tempPassword;
                tempUser.setID(tempID);
                tempUser.setName(tempName);
                tempUser.setUsername(tempUsername);
                tempUser.setPassword(tempPassword);
                usersBox.push_back(tempUser);
            }
        }
        readUsers.close();
    }

    // читаем содержимое контейнера с сообщениями
    std::ifstream readMessages("messages.dat", std::ios::in);
    if (!readMessages)
    {
        std::cout << "File \"messages.dat\" couldn\'t be read.\n";
    }
    else
    {
        std::string header;
        readMessages >> header;
        if (header == "messages.dat")
        {
            int messagesLinesSize{ 0 };
            readMessages >> messagesLinesSize;
                        
            time_t tempMessageTime{ 0 };
            int tempIDSender{ 0 };
            int tempIDReceiver{ 0 };
            bool tempIsRead{ false };
            std::string tempText;
            Message tempMessage;
            for (int i = 0; i < messagesLinesSize; ++i)
            {
                readMessages >> tempMessageTime >> tempIDSender >> tempIDReceiver >> tempIsRead;
                std::getline(readMessages, tempText);
                std::getline(readMessages, tempText);
                tempMessage.messageTime = tempMessageTime;
                tempMessage.idSender = tempIDSender;
                tempMessage.idReceiver = tempIDReceiver;
                tempMessage.isRead = tempIsRead;
                tempMessage.text = tempText;
                messagesBox.push_back(tempMessage);
            }
        }
        readMessages.close();
    }
    
    // основное меню
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
            menuFlag = false;
            break;
            //return 0;
        default:
            return -1;
        }
    }
    
    // сохраняем содержимое контейнера с данными пользователей
    std::ofstream saveUsers("users.dat", std::ios::out);
    if (!saveUsers) std::cout << "File \"user.dat\" couldn\'t be opened\n";
    saveUsers << "users.dat" << std::endl << usersBox.size() << std::endl;
    for (auto& it : usersBox)
    {
        saveUsers << it.getID() << std::endl << it.getName() << std::endl << it.getUserame() << std::endl << it.getPassword() << std::endl;
    }

    // сохраняем содержимое контейнера с сообщениями
    std::ofstream saveMessages("messages.dat", std::ios::out);
    if (!saveMessages) std::cout << "File \"messages.dat\" couldn\'t be opened\n";
    saveMessages << "messages.dat" << std::endl << messagesBox.size() << std::endl;
    for (auto& it : messagesBox)
    {
        saveMessages << it.messageTime << std::endl << it.idSender << std::endl << it.idReceiver << std::endl << it.isRead << std::endl << it.text << std::endl;
    }

    std::cout << "You left the 7tChat, ciao!\n";
    return 0;
}