#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <cstdio>
#include <fmt/core.h>
#include "bank.h"
#include "person.h"
#include <string>


using json = nlohmann::json;


void Bank::create_account(Person person, int pin)
{

	std::ofstream f(fmt::format("{}.json", person.phoneNumber));

	json j = {
		{"firstName", person.firstName},
		{"lastName", person.lastName},
		{"phoneNumber", person.phoneNumber},
		{"pin", pin},
		{"balance", 0.0}
	};

	f << j << std::endl;

	f.close();
}


json Bank::get_account_details(int phoneNumber)
{
	std::ifstream f(fmt::format("{}.json", phoneNumber));

	json j;

	f >> j;

	return j;
}


bool Bank::check_account_exists(int phoneNumber)
{
	std::ifstream f(fmt::format("{}.json", phoneNumber));

	if(f)
	{
		return true;
	} else{
		return  false;
	}
}

bool Bank::check_account_pin(int phoneNumber, int pin)
{
	std::ifstream f(fmt::format("{}.json", phoneNumber));

	json j;

	f >> j;

	if(j["pin"] == pin)
	{
		return true;
	} else {
		return false;
	}
}

void Bank::delete_account(int phoneNumber)
{
	std::remove(fmt::format("{}.json", phoneNumber).c_str());
}


void Bank::transfer_money(int from, int to, float amount)
{
	std::ifstream from_f(fmt::format("{}.json", from));
	std::ifstream to_f(fmt::format("{}.json", to));

	json f;
	from_f >> f;

	json t;
	to_f >> t;

	float f_balance = f["balance"];
	float t_balance = t["balance"];

	f["balance"] = f_balance - amount;
	t["balance"] = t_balance + amount;

	std::ofstream f_from(fmt::format("{}.json", from));
	std::ofstream f_to(fmt::format("{}.json", to));

	f_from << f;
	f_to << t;

	f_from.close();
	f_to.close();
}


void Bank::deposit(int phoneNumber, int amount)
{
	std::ifstream f(fmt::format("{}.json", phoneNumber));

	json j;	

	f >> j;

	float balance = j["balance"];
	j["balance"] = balance + amount;	

	std::ofstream f_w(fmt::format("{}.json", phoneNumber));

	f_w << j;

	f_w.close();
}