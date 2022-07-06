/* Any copyright is dedicated to the Public Domain.
 * https://creativecommons.org/publicdomain/zero/1.0/ */

#include "Contact.hpp"

const std::string& Contact::Get(ContactField key) const
{
	return this->table[key];
}

void Contact::Set(ContactField key, const std::string& value)
{
	this->table[key] = value;
}
