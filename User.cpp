#include "User.h"

int User::getID()
{
    return id;
}

std::string User::getName()
{
    return name;
}

bool User::inputNameForNewUser()
{
    std::cout << "Please, type your REAL NAME (it may consist only latin letters, dots and spaces, min 3 max 40 symbols): ";
    std::getline(std::cin, name);
    for (auto& it : name)
    {
        if (!(it == ' ' || it == '.' || (it >= 'A' && it <= 'Z') || (it >= 'a' && it <= 'z')))
        {
            std::cout << "Sorry, you input some incorrect symbol. Try again.\n";
            return false;
        }
    }
    if (name.size() < 3)
    {
        std::cout << "Sorry, you input less than 3 symbols. Try again.\n";
        return false;
    }
    if (name.size() > 40)
    {
        std::cout << "Sorry, you input more than 40 symbols. Try again.\n";
        return false;
    }
    return true;
}

bool User::inputUsernameForNewUser()
{
    std::cout << "Please, type your USERNAME (it may consist only latin letters and digits, min 3 max 20 symbols): ";
    std::getline(std::cin, username);
    for (auto& it : username)
    {
        if (!((it >= '0' && it <= '9') || (it >= 'A' && it <= 'Z') || (it >= 'a' && it <= 'z')))
        {
            std::cout << "Sorry, you input some incorrect symbol. Try again.\n";
            return false;
        }
    }
    if (username.size() < 3)
    {
        std::cout << "Sorry, you input less than 3 symbols. Try again.\n";
        return false;
    }
    if (username.size() > 20)
    {
        std::cout << "Sorry, you input more than 20 symbols. Try again.\n";
        return false;
    }
    return true;
}

bool User::inputUsernameForLogin(const std::vector<User>& box)
{
    std::cout << "Please, type your USERNAME (it may consist only latin letters and digits, min 3 max 20 symbols): ";
    std::getline(std::cin, username);
    for (auto& it : username)
    {
        if (!((it >= '0' && it <= '9') || (it >= 'A' && it <= 'Z') || (it >= 'a' && it <= 'z')))
        {
            std::cout << "Sorry, you input some incorrect symbol. Try again.\n";
            return false;
        }
    }
    if (username.size() < 3)
    {
        std::cout << "Sorry, you input less than 3 symbols. Try again.\n";
        return false;
    }
    if (username.size() > 20)
    {
        std::cout << "Sorry, you input more than 20 symbols. Try again.\n";
        return false;
    }

    for (auto& it : box)
    {
        if (it.username == username)
        {
            return true;
        }
    }
    std::cout << "Sorry, you typed nonexistent USERNAME. Try again.\n";
    return false;    
}

bool User::inputPasswordForNewUser()
{
    std::cout << "Please, type your PASSWORD (it may consist any chacacters, min 4 max 20 symbols): ";
    std::getline(std::cin, password);
    for (auto& it : password)
    {
        if (!(it >= '!' && it <= '~'))
        {
            std::cout << "Sorry, you input some incorrect symbol. Try again.\n";
            return false;
        }
    }
    if (password.size() < 4)
    {
        std::cout << "Sorry, you input less than 4 symbols. Try again.\n";
        return false;
    }
    if (password.size() > 20)
    {
        std::cout << "Sorry, you input more than 20 symbols. Try again.\n";
        return false;
    }
    return true;
}

bool User::inputPasswordForLogin(const std::vector<User>& box)
{
    std::cout << "Please, type your PASSWORD (it may consist any chacacters, min 4 max 20 symbols): ";
    std::getline(std::cin, password);
    for (auto& it : password)
    {
        if (!(it >= '!' && it <= '~'))
        {
            std::cout << "Sorry, you input some incorrect symbol. Try again.\n";
            return false;
        }
    }
    if (password.size() < 4)
    {
        std::cout << "Sorry, you input less than 4 symbols. Try again.\n";
        return false;
    }
    if (password.size() > 20)
    {
        std::cout << "Sorry, you input more than 20 symbols. Try again.\n";
        return false;
    }
    
    for (auto& it : box)
    {
        if (it.username == username)
        {
            if (it.password == password)
            {
                id = it.id;
                name = it.name;
                return true;
            }
            else
            {
                std::cout << "Sorry, you typed wrong PASSWORD. Try again.\n";
                return false;
            }            
        }
    }
    return false;
}

bool User::inputUsernameForNewUser(const std::vector<User>& box)
{
    std::cout << "Please, type your USERNAME (it may consist only latin letters and digits, min 3 max 19 symbols): ";
    std::getline(std::cin, username);
    for (auto& it : username)
    {
        if (!((it >= '0' && it <= '9') || (it >= 'A' && it <= 'Z') || (it >= 'a' && it <= 'z')))
        {
            std::cout << "Sorry, you input some incorrect symbol. Try again.\n";
            return false;
        }
    }
    if (username.size() < 3)
    {
        std::cout << "Sorry, you input less than 3 symbols. Try again.\n";
        return false;
    }
    if (username.size() > 20)
    {
        std::cout << "Sorry, you input more than 20 symbols. Try again.\n";
        return false;
    }
    for (auto& it : box)
    {
        if (it.username == username)
        {
            std::cout << "Sorry, this USERNAME is used yet by another user. Try again.\n";
            return false;
        }
    }    
    return true;
}

bool User::add(std::vector<User>& box)
{
    for (auto& it : box)
    {
        if (it.username == username)
        {
            return false;
        }
    }
    id = (box.size() + 1);
    box.push_back(*this);
    return true;
}

int User::inputReceiversUsername(const std::vector<User>& box)
{
    std::string receiverUsername;
    std::cout << "Please, type RECEIVER'S USERNAME (it may consist only latin letters and digits, min 3 max 19 symbols): ";
    std::getline(std::cin, receiverUsername);
    for (auto& it : receiverUsername)
    {
        if (!((it >= '0' && it <= '9') || (it >= 'A' && it <= 'Z') || (it >= 'a' && it <= 'z')))
        {
            std::cout << "Sorry, you input some incorrect symbol. Try again.\n";
            return 0;
        }
    }
    if (receiverUsername.size() < 3)
    {
        std::cout << "Sorry, you input less than 3 symbols. Try again.\n";
        return 0;
    }
    if (receiverUsername.size() > 20)
    {
        std::cout << "Sorry, you input more than 20 symbols. Try again.\n";
        return 0;
    }

    for (auto& it : box)
    {
        if (it.username == receiverUsername)
        {
             return it.id;
        }        
    }
    std::cout << "Sorry, typed USERNAME is unknown. Try again.\n";
    return 0;
}