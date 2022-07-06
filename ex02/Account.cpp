/* Any copyright is dedicated to the Public Domain.
 * https://creativecommons.org/publicdomain/zero/1.0/ */

#include "Account.hpp"
#include <iostream>
#include <string>

void Account::_displayTimestamp(void)
{
	// std::cout << "[19920104_091532] ";
	std::time_t t;
	std::time(&t);
	char buf[1024];
	std::strftime(buf, sizeof(buf), "[%Y%m%d_%H%M%S] ", std::localtime(&t));
	std::cout << buf;
}

int Account::_nbAccounts;

int Account::getNbAccounts(void)
{
	return _nbAccounts;
}

int Account::_totalAmount;

int Account::getTotalAmount(void)
{
	return _totalAmount;
}

int Account::_totalNbDeposits;

int Account::getNbDeposits(void)
{
	return _totalNbDeposits;
}

int Account::_totalNbWithdrawals;

int Account::getNbWithdrawals(void)
{
	return _totalNbWithdrawals;
}

void Account::displayAccountsInfos(void)
{
	_displayTimestamp();
	std::cout << "accounts:" << getNbAccounts() << ';';
	std::cout << "total:" << getTotalAmount() << ';';
	std::cout << "deposits:" << getNbDeposits() << ';';
	std::cout << "withdrawals:" << getNbWithdrawals() << std::endl;
}

Account::Account()
{
	//No-OP
}

Account::Account(int initial_deposit)
{
	_accountIndex = _nbAccounts++;
	_amount = initial_deposit;
	_nbDeposits = _nbWithdrawals = 0;
	_totalAmount += initial_deposit;
	{
		_displayTimestamp();
		std::cout << "index:" << _accountIndex << ';';
		std::cout << "amount:" << _amount << ';';
		std::cout << "created" << std::endl;
	}
}

Account::~Account(void)
{
	{
		_displayTimestamp();
		std::cout << "index:" << _accountIndex << ';';
		std::cout << "amount:" << _amount << ';';
		std::cout << "closed" << std::endl;
	}
}

void Account::makeDeposit(int deposit)
{
	int new_amount = _amount + deposit;
	_nbDeposits++;
	_totalNbDeposits++;
	_totalAmount += deposit;
	{
		_displayTimestamp();
		std::cout << "index:" << _accountIndex << ';';
		std::cout << "p_amount:" << _amount << ';';
		std::cout << "deposit:" << deposit << ';';
		std::cout << "amount:" << new_amount << ';';
		std::cout << "nb_deposits:" << _nbDeposits << std::endl;
	}
	_amount = new_amount;
}

bool Account::makeWithdrawal(int withdrawal)
{
	int new_amount = _amount - withdrawal;
	if (new_amount < 0)
	{
		{
			_displayTimestamp();
			std::cout << "index:" << _accountIndex << ';';
			std::cout << "p_amount:" << _amount << ';';
			std::cout << "withdrawal:" << "refused" << std::endl;
		}
		return false;
	}
	_nbWithdrawals++;
	_totalNbWithdrawals++;
	_totalAmount -= withdrawal;
	{
		_displayTimestamp();
		std::cout << "index:" << _accountIndex << ';';
		std::cout << "p_amount:" << _amount << ';';
		std::cout << "withdrawal:" << withdrawal << ';';
		std::cout << "amount:" << new_amount << ';';
		std::cout << "nb_withdrawals:" << _nbWithdrawals << std::endl;
	}
	_amount = new_amount;
	return true;
}

int Account::checkAmount(void) const
{
	return _amount;
}

void Account::displayStatus(void) const
{
	_displayTimestamp();
	std::cout << "index:" << _accountIndex << ';';
	std::cout << "amount:" << _amount << ';';
	std::cout << "deposits:" << _nbDeposits << ';';
	std::cout << "withdrawals:" << _nbWithdrawals << std::endl;
}
