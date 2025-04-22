#ifndef IP_H
#define IP_H

#include <stddef.h>
#include <iostream>
#include "generic-field.h"

class IP : public GenericField {

	String ip_law;  // required ip of the law, i.e. left to the '/'
	String law;
	String field; //src or dst

public:

	/**
	 * @brief get an extern packet from the user. Checks whether it obeys the law.
	 */
	bool match(String packet);

	/**
	 * @brief Get a single law -> Initiate/Parsing the ip_law.
	 * @returns TRUE if parsing process is done without errors
	 */
	bool set_value(String value);

	/**
	 * @brief Initiates a IP from a given packet and required-law
	 */
	IP(String law);

	/**
	 * @brief find the required field dst or src
	 */
	String find_field(String law);
	
	/**
	* @brief split the packet according to bytes and convert the packet to unsigned int
	*/
	unsigned int ip_to_int(String ext_ip);

	/**
	* @brief create a mask according to a given law
	*/
	unsigned int get_mask(String law);


	/**
	* @brief Get the IP from a single field by split this field in '='
	*/
	String equ_sep(String single_field);

};

















#endif
