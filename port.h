#ifndef PORT_H
#define PORT_H

#include <stddef.h>
#include <iostream>
#include "generic-field.h"

class Port : public GenericField {

	String field; //src or dest
	int port;
	int upper_bound;
	int lower_bound;


public:

	Port(String law); //construct a Port object with default values
	~Port(); // destructor
	String find_field(String law); //find the required field dst or src
	bool set_value(String range); // set the legal values of the range
	bool match(String packet); // checks if the correct field matches the given law
	/**
	* @brief Get the port from a single field by split this field in '='
	*/
	int equ_sep(String single_field);
};
#endif
