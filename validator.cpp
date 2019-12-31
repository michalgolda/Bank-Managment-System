#include <string>
#include "validator.h"

bool Validator::validate_pin(int pin)
{
	std::string _pin = std::to_string(pin);

	if(_pin.length() < 4)
	{	
		return false;
	} else {
		return true;
	}
}

bool Validator::validate_phone_number(int phone_number)
{
	std::string _phone_number = std::to_string(phone_number);

	if(_phone_number.length() < 9)
	{
		return false;
	} else {
		return true;
	}
}