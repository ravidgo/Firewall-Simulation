
#include <iostream>
using namespace std;
#include <string.h>
#include "ip.h"


IP::IP(String law) {
	
	this->law = law.trim();
	//find type of field from the law
	this->field = find_field(law);
	//zero initiating. we'll find the accurate ip in set_value
	this->ip_law = "0.0.0.0";

}

String IP::find_field(String law) {

	String* src_out;
	size_t src_size;
	law.split("=", &src_out, &src_size);
	if (src_out[0].trim().equals("src-ip")) {
		delete[] src_out;
		return String("src-ip");
	}
	else
	{	
		delete[] src_out;
		return String("dst-ip");
	}
}



bool IP::set_value(String value) {

	
	/*now, we'll get the IP of the law (left to "/")*/
	String cpy_value = value;
	String* equ_out;
	size_t equ_size;

	cpy_value.split("=", &equ_out, &equ_size);
	if (equ_out == NULL) {
		return false;
	}
	String ip_and_range = equ_out[1].trim(); // our law is right to '='
	delete[] equ_out;
	
	size_t slash_size;
	String* slash_out;
	ip_and_range.split("/", &slash_out, &slash_size);
	if (slash_out == NULL) {
		return false;
	}
	ip_law = slash_out[0]; //	IP is left to the '/'
	delete[] slash_out;


	return true;
}


bool IP::match(String packet) {

	//check if packet isn't empty
	if (packet.equals("")) {
		return false;
	}

	/*extract the IP from the packet according to field:*/
	String ip_extern;

	if (set_value(law)) {
		//1. divide to fields
		String* out_fields;
		size_t size_fields;
		packet.split(",", &out_fields, &size_fields);

		if (size_fields != 0) { //i.e. we have more than one field
			//2. divide each field according to '='
			for (size_t i = 0; i < size_fields; i++) {

				out_fields[i] = out_fields[i].trim();

				//3.extract ip from the field
				ip_extern = equ_sep(out_fields[i]);
				//4. find if this part is compatible to desired field 
				if (!ip_extern.equals(" ")) {
					break;
				}
			}
		}
		else {  // The case we get only single field in the packet(like in gdb-test)

			ip_extern = equ_sep(packet.trim());
			if (ip_extern.equals(" ")) {
				return false; //miss-match between ip and law
			}
		}

		delete[] out_fields;
	}

	/*now, we'll check matching between IP of law and IP of the outer packet*/
	unsigned int mask = get_mask(law);
	unsigned int ip_ext_int = ip_to_int(ip_extern);
	unsigned int ip_law_int = ip_to_int(ip_law);

	return (ip_ext_int & mask) == (ip_law_int & mask);
}



unsigned int IP::ip_to_int(String ext_ip) {

	String* out;
	size_t size;
	ext_ip.split(".", &out, &size);
	unsigned int arr[size];
	for (size_t i = 0; i < size; i++) {
		arr[i] = out[i].to_integer();
	}

	unsigned int ip_int;
	ip_int = arr[0] << 24 | arr[1] << 16 | arr[2] << 8 | arr[3];
	delete[] out;

	return ip_int;
}


unsigned int IP::get_mask(String law) {

	//extarct the length of mask
	String cpy_law = law;
	size_t size;
	String* out_str;
	cpy_law.split("/", &out_str, &size);
	int m = out_str[1].to_integer();
	delete[] out_str;

	// create the mask
	unsigned int mask = 0;
	mask = -1;
	mask = mask << (32 - m);

	return mask;
}

String IP::equ_sep(String single_field) {
	String* single_out;
	size_t single_size;
	String ip_extern;
	single_field.split("=", &single_out, &single_size);
	//field is left to "="
	if (single_out[0].trim().equals(field)) {
		//then the second sub-field is the ip!
		single_out[1] = single_out[1].trim();
		ip_extern = single_out[1];
		delete[] single_out;
	}
	else
	{
		ip_extern = " ";
	}

	return ip_extern;
}
