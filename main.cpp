#include <iostream>
#include <stddef.h>
#include "generic-field.h"
#include "ip.h"
#include "port.h"
#include "string.h"
#include "input.h"
#define ERROR 1
#define CORRECT_SIZE 2
using namespace std;

int main(int argc, char** argv) {
	
	if (check_args(argc,argv)) {
		return ERROR;
	}
	GenericField *field;
	//GenericField *test;

	String law(argv[1]);
	String * splitted_law;
	size_t size;
	String law_tmp(law);
	law_tmp.split("=", &splitted_law, &size);
	if (size != CORRECT_SIZE) {
		return ERROR;
	}
	//checking if this is a port/ip law
	if (splitted_law[0].trim().equals("src-ip") || splitted_law[0].trim().equals("dst-ip")) {
		field = new IP(law);
	}
	else if (splitted_law[0].trim().equals("src-port") || splitted_law[0].trim().equals("dst-port")) {
		field = new Port(law);
		//initializing port field
		if (!(field->set_value(splitted_law[1].trim()))) {
			delete[] splitted_law;
			return ERROR;
		}

	}
	else {
		delete[] splitted_law;
		return ERROR;
	}


	parse_input(*field);
	delete[] splitted_law;
	delete field;
	return 0;

}
