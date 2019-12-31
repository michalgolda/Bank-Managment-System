#pragma once
#include <string>
#include <nlohmann/json.hpp>
#include "person.h"

using json = nlohmann::json;

class Bank
{
public:
	void create_account(Person person, int pin);
	void delete_account(int phoneNumber);
	void transfer_money(int from, int to, float amount);
	void deposit(int phoneNumber, int amount);
	bool check_account_exists(int phoneNumber);
	bool check_account_pin(int phoneNumber, int pin);
	json get_account_details(int phoneNumber);
};