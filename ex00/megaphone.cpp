/* Any copyright is dedicated to the Public Domain.
 * https://creativecommons.org/publicdomain/zero/1.0/ */

#include <cctype>
#include <iostream>

#define MEGAPHONE_DEF_MSG "* LOUD AND UNBEARABLE FEEDBACK NOISE *"

int main(int argc, char* argv[])
{
	std::string str;
	if (argc > 1)
	{
		for (int i = 1; i < argc; i++)
		{
			const std::string arg(argv[i]);
			for (std::size_t j = 0; j < arg.length(); j++)
			{
				str += std::toupper(arg[j]);
			}
		}
	}
	else
	{
		str = MEGAPHONE_DEF_MSG;
	}
	std::cout << str << std::endl;
	return 0;
}
