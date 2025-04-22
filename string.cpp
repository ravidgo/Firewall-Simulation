#include "string.h"
#include <iostream>
using namespace std;
#include <string.h>

String::String() {
	data = new char[1];
	data[0] = '\0';
	length = 0;
}


String::String(const String& str) {
	length = str.length;
	data = strcpy(new char[length + 1], str.data);
}


String::String(const char* str) {
	length = strlen(str);
	data = strcpy(new char[length + 1], str);
}

String::~String() {

	delete[] data;
}

String& String::operator=(const String& rhs) {
	if (this == &rhs) {
		return *this;
	}
	delete[] data;

	data = strcpy(new char[rhs.length + 1], rhs.data);
	length = rhs.length;
	return *this;
}

String& String::operator=(const char* str) {
	if (this->data == str) {
		return *this;
	}
	delete[] data;

	length = strlen(str);
	data = strcpy(new char[length + 1], str);
	return *this;
}

bool String::equals(const String& rhs) const {
	int cond1=0;
	int cond2=0;
	if (!strcmp(this->data, rhs.data)) {
		cond1 = 1;
	}
	if (this->length == rhs.length) {
		cond2 = 1;
	}

	return cond1 && cond2;
}

bool String::equals(const char *rhs) const {
	int cond1 = 0;
	int cond2 = 0;
	if (!strcmp(this->data, rhs)) {
		cond1 = 1;
	}
	if (this->length == strlen(rhs)) {
		cond2 = 1;
	}
	return cond1 && cond2;

}


void String::split(const char* delimiters, String** output, size_t* size) const {
  // Make a copy of the string and a copy of the delimiters
  char *str = new char[length + 1];
  strcpy(str,data);
  char *delims = new char[strlen(delimiters) + 1];
  strcpy(delims,delimiters);
 

  // Initialize the output array and the size
  *size = 0;
  //*output = NULL;

  // Tokenize the string
  char *token = strtok(str, delims);
  while (token != NULL) {


   	if(this->equals(token)){
		*output = NULL;
		break;
    	}

    // Allocate memory for the new token
   	if (*size == 0 && output != NULL) {
     		*output = new String[1];
    	}
	else if(output != NULL) {
		String* new_output = new String[*size + 1];

		// reallocating:
		for (size_t i = 0; i < *size; i++) {
			new_output[i] = (*output)[i];
		}

		// delete the old array and update new
		delete[] * output;
		*output = new String[*size + 1];
		//*output = new_output;
		for (size_t i = 0; i < *size; i++){
			(*output)[i] = new_output[i];
		}
		delete[] new_output;

	}

	if(output != NULL){
		// Initialize the new token
    		(*output)[*size] = token;
	}
    (*size)++;

    // Get the next token
    token = strtok(NULL, delims);
  }

  // Free the copies of the string and delimiters
  delete[] str;
  delete[] delims;
}


int String::to_integer() const {

	return atoi(this->data);
}



String String::trim() const {
  // Find the first non-whitespace character
  size_t start = 0;
  //String cpy_str;
  //strcpy(cpy_str.data,this->data);
  //char *copy_str = cpy_str.data;
	 
  while (start < length && data[start] == ' ') {
    start++;
  }

  // Find the last non-whitespace character
  size_t end = length - 1;
  while (end > start && data[end] == ' ') {
    end--;
  }

  //delete[] cpy_str;

  // Create a new string and copy the relevant part of the original string to it
  char *cpy_str = new char[end - start + 2];
  memcpy(cpy_str, data + start, end - start + 1);
  cpy_str[end - start + 1] = '\0';
  String result(cpy_str);
  delete[] cpy_str;
  return result;
}

