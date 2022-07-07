/* Any copyright is dedicated to the Public Domain.
 * https://creativecommons.org/publicdomain/zero/1.0/ */

#pragma once

#include <string>

enum ContactField
{
    CF_FIRST_NAME,
    CF_LAST_NAME,
    CF_NICKNAME,
    CF_PHONE_NUMBER,
    CF_DARKEST_SECRET,
    NO_CONTACT_FIELD
};

class Contact
{
private:
    std::string table[NO_CONTACT_FIELD];

public:
    const std::string& Get(ContactField key) const;
    void Set(ContactField key, const std::string& value);
};
