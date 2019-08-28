#include <iostream>
#include <string>
using namespace std;

int main() {

	int initialReading;                       //this code block and ones below ask user for infromation and stores given info in variables
	cout << "Initial meter reading: ";
	cin >> initialReading;

	int finalReading;
	cout << "Final meter reading: ";
	cin >> finalReading;
	cin.ignore(10000, '\n');

	cout << "Customer name: ";
	string name;
	getline(cin, name);

	int month;
	cout << "Month number (1=Jan, 2=Feb, etc.): ";
	cin >> month;

	cout << "---" << endl;

	double cost = -1;                                  // initializes cost and hcfUsed(hundred cubic feet used) variables
	int hcfUsed = finalReading - initialReading;

	if (finalReading >= initialReading && initialReading >= 0 && name != "" && month <= 12 && month >= 1) {  // makes sure that info provided is valid
		if (month >= 11 || month <= 3) {     // determines if it's a high or low month and does calculations based on this info
			if (hcfUsed > 29) {
				cost = (29 * 2.71) + (((double)hcfUsed - 29) * 2.87);
			} else {
				cost = hcfUsed * 2.71;
			}
		} else {
			if (hcfUsed > 43) {
				cost = (43 * 2.71) + (((double)hcfUsed - 43) * 3.39);
			} else {
				cost = hcfUsed * 2.71;
			}
		}
	} else if (initialReading < 0) {                                      // this statement and below are error codes
		cout << "The initial meter reading must be nonnegative." << endl;
		return 1;
	} else if (finalReading < initialReading) {                         // exits the program after giving the error code
		cout << "The final meter reading must be at least as large as the initial reading." << endl;
		return 1;
	} else if (name == "") {
		cout << "You must enter a customer name." << endl;
		return 1;
	} else if (month > 12) {
		cout << "The month number must be in the range 1 through 12." << endl;
		return 1;
	} else if (month < 1) {
		cout << "The month number must be in the range 1 through 12." << endl;
		return 1;
	}

	cout.setf(ios::fixed);                  // formats the cost with two digits following the period
	cout.precision(2);

	cout << "The bill for " << name << " is " << "$" << cost << endl;
}