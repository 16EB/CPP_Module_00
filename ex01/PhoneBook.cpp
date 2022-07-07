/* Any copyright is dedicated to the Public Domain.
 * https://creativecommons.org/publicdomain/zero/1.0/ */

#include "PhoneBook.hpp"

#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

static void string_upcase(std::string& str)
{
    for (std::string::iterator it = str.begin(); it != str.end(); it++)
    {
        *it = std::toupper(*it);
    }
}

int main(void)
{
    PhoneBook instance;
    bool run = true;
    while (run)
    {
        std::cout << "> ";
        std::string cmd;
        if (std::getline(std::cin, cmd))
        {
            string_upcase(cmd);
            if (cmd == "ADD")
            {
                instance.Add();
            }
            else if (cmd == "SEARCH")
            {
                instance.Search();
            }
            else if (cmd == "EXIT")
            {
                std::cout << "Sure want to exit? (y or n)";
                std::string prompt;
                std::getline(std::cin, prompt);
                string_upcase(prompt);
                if (prompt == "Y")
                {
                    std::cout << "__EXIT__" << std::endl;
                    run = false;
                }
            }
            else
            {
                // Discard
            }
        }
        else
        {
            std::cout << "__EOF__" << std::endl;
            run = false;
        }
    }
    return 0;
}

PhoneBook::PhoneBook()
{
    this->count = 0;
}

static std::string name_of(ContactField x)
{
    switch (static_cast<int>(x))
    {
    case CF_FIRST_NAME:
        return "First Name";

    case CF_LAST_NAME:
        return "Last Name";

    case CF_NICKNAME:
        return "Nickname";

    case CF_PHONE_NUMBER:
        return "Phone Number";

    case CF_DARKEST_SECRET:
        return "Darkest Secret";
    }
    return "(null)";
}

static bool assert_field(ContactField key, std::string& value, std::string& err)
{
    if (key == CF_PHONE_NUMBER)
    {
        std::string new_value;
        for (std::size_t i = 0; i < value.length(); i++)
        {
            if (std::isdigit(value[i]))
            {
                new_value += std::toupper(value[i]);
            }
            else if (value[i] != '-')
            {
                err = "must be phone number format.";
                return false;
            }
        }
        if (new_value.empty())
        {
            err = "empty phone number.";
            return false;
        }
        value = new_value;
    }
    return true;
}

void PhoneBook::Add()
{
    Contact c;
    for (int i = 0; i < NO_CONTACT_FIELD; i++)
    {
        ContactField k = static_cast<ContactField>(i);
        do
        {
            std::cout << name_of(k) << ": ";
            std::string v;
            if (!std::getline(std::cin, v))
            {
                std::cout << std::endl;
                return;
            }
            if (v.empty())
            {
                std::cout << "A saved contact CAN NOT have empty fields. ADD has been canceled." << std::endl;
                return;
            }
            std::string err;
            if (!assert_field(k, v, err))
            {
                std::cout << "Invalid input: " << err << std::endl;
                continue;
            }
            c.Set(k, v);
            break;
        } while (true);
    }
    this->contacts[this->count++ % CONTACT_ROW_MAX] = c;
}

static std::string string_truncate(const std::string& s, std::size_t w)
{
    std::string r = s;
    if (r.length() > w)
    {
        r.erase(w - 1);
        r.insert(w - 1, ".");
    }
    return r;
}

void PhoneBook::Search()
{
    std::string err = "";
    do
    {
        std::cout << std::setw(CONTACT_SEARCH_WIDTH) << "index" << '|'
                  << std::setw(CONTACT_SEARCH_WIDTH) << "first name" << '|'
                  << std::setw(CONTACT_SEARCH_WIDTH) << "last name" << '|'
                  << std::setw(CONTACT_SEARCH_WIDTH) << "nickname" << std::endl;
        for (int i = 0; i < CONTACT_ROW_MAX; i++)
        {
            std::cout << std::setw(CONTACT_SEARCH_WIDTH) << i << '|'
                      << std::setw(CONTACT_SEARCH_WIDTH) << string_truncate(this->contacts[i].Get(CF_FIRST_NAME), CONTACT_SEARCH_WIDTH) << '|'
                      << std::setw(CONTACT_SEARCH_WIDTH) << string_truncate(this->contacts[i].Get(CF_LAST_NAME), CONTACT_SEARCH_WIDTH) << '|'
                      << std::setw(CONTACT_SEARCH_WIDTH) << string_truncate(this->contacts[i].Get(CF_NICKNAME), CONTACT_SEARCH_WIDTH) << std::endl;
        }
        std::cout << err << std::endl;
        std::cout << "Enter index or empty to exit." << std::endl;
        std::cout << ">> ";
        std::string prompt;
        std::size_t index;
        if (!std::getline(std::cin, prompt))
        {
            std::cout << std::endl;
            return;
        }
        if (prompt.empty())
        {
            break;
        }
        if (!(std::istringstream(prompt) >> index))
        {
            err = "Invalid input.";
            continue;
        }
        if (index >= CONTACT_ROW_MAX)
        {
            err = "Out of index.";
            continue;
        }
        err = "";
        Contact& c = this->contacts[index];
        for (int i = 0; i < NO_CONTACT_FIELD; i++)
        {
            ContactField k = static_cast<ContactField>(i);
            std::cout << name_of(k) << ": " << c.Get(k) << std::endl;
        }
        std::cout << std::endl;
        break;
    } while (true);
    std::cout << "Quit SEARCH gracefully." << std::endl;
}
