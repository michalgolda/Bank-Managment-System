#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <fmt/core.h>
#include <nlohmann/json.hpp>
#include <unistd.h>
#include <stdlib.h>
#include "bank.cpp"
#include "person.h"
#include "validator.cpp"

using json = nlohmann::json;
using namespace std;

int main()
{
	Bank bank;
	Validator validator;

	while(true){
		system("clear");

		int option;

		cout << "##### BANK SYSTEM #####" << endl;
		cout << endl;
		cout << endl;
		cout << "1. Create account." << endl;
		cout << "2. Account." << endl;
		cout << "3. Exit" << endl;
		cout << endl;
		cout << "Enter your option: ";
		cin >> option;

		if(option == 1)
		{
			int pin;
			int phoneNumber;
			Person person;

			bool valid_status;

			cout << "Phone number: ";
			cin >> phoneNumber;

			valid_status = validator.validate_phone_number(phoneNumber);
			if(valid_status == false)
			{
				cout << "Phone number length is short!" << endl;
				
				sleep(1);

				continue;
			}

			cout << "Pin code: ";
			cin >> pin;

			valid_status = validator.validate_pin(pin);
			if(valid_status == false)
			{
				cout << "Pin length is not valid." << endl;

				sleep(1);

				continue;
			}

			cout << "First name: ";
			cin >> person.firstName;

			cout << "Last name: ";
			cin >> person.lastName;

			person.phoneNumber = phoneNumber;

			bank.create_account(person, pin);

			cout << "Account success created." << endl;

			sleep(1);

			continue;
		} else if(option == 2)
		{
			int pin;
			int phoneNumber;
			bool valid_status;

			cout << "Pin: ";
			cin >> pin;
			valid_status = validator.validate_pin(pin);

			if(valid_status == false)
			{
				cout << "Pin is invalid." << endl;

				sleep(2);

				continue;
			}

			cout << "Phone number: ";
			cin >> phoneNumber;
			valid_status = validator.validate_phone_number(phoneNumber);

			if(valid_status == false)
			{
				cout << "Phone number is invalid." << endl;
				
				sleep(2);

				continue;
			}

			system("clear");

			bool account_exists = bank.check_account_exists(phoneNumber);
			bool check_pin = bank.check_account_pin(phoneNumber, pin);

			if(account_exists)
			{
				if(check_pin)
				{
							
					while(true)
					{
						json account_details = bank.get_account_details(phoneNumber);

						system("clear");

						cout << "Account details: " << endl;
						cout << endl;
						cout << "First name: " << account_details["firstName"] << endl;
						cout << "Last name: " << account_details["lastName"] << endl;
						cout << "Phone number: " << account_details["phoneNumber"] << endl;
						cout << "Balance: " << account_details["balance"] << endl;

						int option;
						cout << "1. Exit" << endl;
						cout << "2. Delete account" << endl;
						cout << "3. Transfer money" << endl;
						cout << "4. Deposit" << endl;
						cin >> option;

						if(option == 1)
						{
							break;
						} else if(option == 2)
						{
							bank.delete_account(account_details["phoneNumber"]);

							cout << "Account success deleted." << endl;

							sleep(1);

							break;
						} else if(option == 3) {
							int option;

							cout << "1. Exit" << endl;
							cout << "2. Continue" << endl;
							cin >> option;

							system("clear");

							if(option == 1)
							{
								break;
							} else {
								int to;
								float amount;

								cout << "To: ";
								cin >> to;

								bool valid_to = bank.check_account_exists(to);
								if(valid_to == false)
								{	
									cout << "Account is not exists!" << endl;
									sleep(1);

									continue;
								}

								cout << "Amount: ";
								cin >> amount;

								bank.transfer_money(account_details["phoneNumber"], to, amount);

								cout << "Success transfered money." << endl;

								sleep(1);

								continue;
							}
 						} else if(option == 4)
 						{
 							int amount;

 							cout << "Amount: ";
 							cin >> amount;

 							bank.deposit(account_details["phoneNumber"], amount);

 							cout << "Success." << endl;

 							sleep(1);

 							continue;
 						} else {
 							continue;
 						}
					}
				} else {
					cout << "Pin is not valid." << endl;

					sleep(1);

					continue;
				}
			} else {
				cout << "Account is not exists!" << endl;

				sleep(1);

				continue;
			}

		} else if(option == 3)
		{
			exit(3);
		}
	}
	

}