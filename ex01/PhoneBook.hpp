/* Any copyright is dedicated to the Public Domain.
 * https://creativecommons.org/publicdomain/zero/1.0/ */

#pragma once

#include "Contact.hpp"

#define CONTACT_ROW_MAX 8
#define CONTACT_SEARCH_WIDTH 10

class PhoneBook
{
private:
    Contact contacts[CONTACT_ROW_MAX];
    std::size_t count;

public:
    PhoneBook();
    void Add();
    void Search();
};
