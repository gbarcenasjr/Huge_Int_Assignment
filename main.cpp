#include <iostream>
#include <stdio.h>
#include <time.h>

#include "HugeInt.h"

using namespace std;

int main() {
	HugeInt hi1;
	HugeInt hi2;
	HugeInt hi3;
	HugeInt hi4;

	HugeInt hi5;
	HugeInt hi6;

	HugeInt hi7;


	srand(time(NULL)); //To make rand() less predictably random.


	for (int i = 0; i < 5; i++) {
		int randInt = rand() % 10;
		hi1.insertDigit(randInt);
	}

	for (int i = 0; i < 5; i++) {
		int randInt = rand() % 10;
		hi2.insertDigit(randInt);
	}


	cout << "Welcome to the Huge Int Program\n" <<
			"=====================================================\n" <<
			"We'll start off with our first two random Huge Ints:\n" <<
			"HugeInt 1: ";
			hi1.printDigits();
	cout << "\n" <<
			"HugeInt 2: ";
			hi2.printDigits();
	cout << "\n\n\n" <<
			"Let's compare the two!\n" <<
			"------------------------------------------\n" <<
			"Is Huge Int 1 less than Huge Int 2: " << boolalpha << (hi1 < hi2) << "\n" <<
			"Is Huge Int 2 less than Huge Int 1: " << boolalpha << (hi2 < hi1) << "\n\n" <<
			"Do Huge Int 1 equal to Huge Int 2: " << boolalpha << (hi1 == hi2) << "\n\n";
	hi3.insertDigit(1);
	hi3.insertDigit(2);
	hi3.insertDigit(3);
	hi3.insertDigit(4);
	hi3.insertDigit(5);

	hi4 = hi3; //This makes a deep copy of hi3. Hi4 does not points at hi3, instead has it's own copy of hi3's Nodes.

	cout << "(Let's make Huge Int 3 and Huge Int 4's Values and make them both contain \'12345\')\n" <<
			"Do Huge Int Value  equal to Huge Int 2: " << boolalpha << (hi3 == hi4);
	cout << "\n\n\n" <<
			"Let's do math with the two Huge Ints!\n" <<
			"------------------------------------------\n";
			hi3 = hi1 + hi2;
			hi1.printDigits();
	cout << " + ";
			hi2.printDigits();
	cout << " = ";
			hi3.printDigits();
	cout << "\n";


			hi5 = hi1 - hi2;
			hi1.printDigits();
	cout << " - ";
			hi2.printDigits();
	cout << " = ";
			hi5.printDigits();
	cout << "\n";



			hi6 = hi2 - hi1;
			hi2.printDigits();
	cout << " - ";
			hi1.printDigits();
	cout << " = ";
			hi6.printDigits();



	cout << "\n\n\n" <<
			"Let's do math with negative Huge Ints!\n" <<
			"------------------------------------------\n";
	if (hi5 < hi6) {
			hi7 = hi5 - hi1;
			hi5.printDigits();
		} else {
			hi7 = hi6 - hi1;
			hi6.printDigits();
		}
	cout << " - ";
	hi1.printDigits();
	cout << " = ";
	hi7.printDigits();
	cout << "\n";


	hi2.printDigits();
	cout << " - ";
	if (hi5 < hi6) {
			hi7 = hi2 - hi5;
			hi5.printDigits();
		} else {
			hi7 = hi2 - hi6;
			hi6.printDigits();
		}
	cout << " = ";
	hi7.printDigits();
	cout << "\n";

	if (hi5 < hi6) {
			hi7 = hi5 + hi1;
			hi5.printDigits();
		} else {
			hi7 = hi6 + hi1;
			hi6.printDigits();
		}
	cout << " + ";
	hi1.printDigits();
	cout << " = ";
	hi7.printDigits();
	cout << "\n";

	hi2.printDigits();
	cout << " + ";
	if (hi5 < hi6) {
		hi7 = hi2 + hi5;
		hi5.printDigits();
	} else {
		hi7 = hi2 + hi6;
		hi6.printDigits();
	}
	cout << " = ";
	hi7.printDigits();
	cout << "\n";

	if (hi5 < hi6) {
		hi7 = hi5 - hi5;
		hi5.printDigits();
		cout << " - ";
		hi5.printDigits();
	} else {
		hi7 = hi6 - hi6;
		hi6.printDigits();
		cout << " - ";
		hi6.printDigits();
	}

	cout << " = ";
	hi7.printDigits();
	cout << "\n";

	if (hi5 < hi6) {
		hi7 = hi5 + hi5;
		hi5.printDigits();
		cout << " + ";
		hi5.printDigits();
	} else {
		hi7 = hi6 + hi6;
		hi6.printDigits();
		cout << " + ";
		hi6.printDigits();
	}

	cout << " = ";
	hi7.printDigits();
	cout << "\n";



	return 0;
}
