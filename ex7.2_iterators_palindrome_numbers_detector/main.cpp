// ex7.2.cpp : Defines the entry point for the application.
//
#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>

using namespace std;

template <typename TYPE>
bool palindrome(vector<TYPE> v) { //Create a template of a function that returns true or false if its or its not a palindrome
	bool palindrome = true;
	typename vector<TYPE>::iterator ibeg;
	ibeg = v.begin();
	typename vector<TYPE>::iterator iend;
	iend = v.end();
	--iend;
		
	while (ibeg != --v.end()) {
		if (*ibeg != *iend) {
			palindrome = false;
			cout << "This is not a palindrome" << endl;
			break;
		}
		ibeg++; --iend;
	}
	if (palindrome) { cout << "This is a palindrome" << endl;}
	return palindrome;
}

int main() {
	vector<double> v1 = { 1.5,2.2,3,2.2,1.5 };
	palindrome(v1);
	vector<int> v2 = { 1,1,3,2,1 };
	palindrome(v1);

	return 0;
}