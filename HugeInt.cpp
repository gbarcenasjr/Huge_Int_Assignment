#include "HugeInt.h"
#include <iostream>
#include <string>

HugeInt::HugeInt() {
	lsd = nullptr;
	msd = nullptr;

	sign = PLUS;
	numDigits = 0;
}


HugeInt::~HugeInt() {
	HugeInt::makeEmpty();// To Remove Data from the Linked List
}


void HugeInt::makeEmpty() {
	//This function will remove digits from the left of the Huge Int
	sign = PLUS;
	Node *curr = msd;
	Node *lesser;

	while (curr != nullptr) {// Will execute until outside the LinkedList (Will NOT execute if LinkedList is already empty)
		lesser = curr->next_lesser;
		delete curr;
		curr = lesser;
	}

	lsd = nullptr;
	msd = nullptr;
	numDigits = 0;
}


void HugeInt::insertDigit(int newDigit) {
	//insert new integer digit to the left. Insert each digit separately!!!!!!!
	//(EX: HUGEINT = 1; user inputs '3'; HUGEINT = 31; user inputs '5'; HUGEINT = 531; etc.)

	Node *insert = new Node;

	insert->digit = newDigit;
	insert->next_greater = nullptr;

	if (msd == nullptr) {// Will execute if Linked List is empty. (Makes the first Node)
		insert->next_lesser = nullptr;
		msd = insert;
		lsd = insert;

	} else {// Will execute if Linked List is NOT empty.
		Node *temp = msd;

		insert->next_lesser = temp;
		temp->next_greater = insert;

		msd = insert;
	}
	numDigits += 1;
}

void HugeInt::printDigits() const{
	if (msd != nullptr){// Will execute if LinkedList is NOT empty.
		if (sign == MINUS) {
			std::cout << "-";
		}

		Node *temp = msd;
		while (temp != nullptr) {// Will execute until outside the LinkedList
			std::cout << temp->digit;
			temp = temp->next_lesser;
		}
	} else {// Will execute if LinkedList is empty
		std::cout << "Error: Unable to print empty Linked List.";
	}
}


bool HugeInt::operator<(const HugeInt &second) const {
	//compare for less than. return true/false
	if (sign == PLUS && second.sign == MINUS){
		return false;
	} else if (sign == MINUS && second.sign == PLUS){
		return true;
	} else if (sign == PLUS && second.sign == PLUS){
		if (numDigits < second.numDigits){// EX:  30 (2 Digits) is less than 3000 (4 Digits)
			return true;
		} else if (numDigits > second.numDigits){// EX:  5000 (4 Digits) is NOT less than 2 (1 Digit)
			return false;
		} else {//will execute if both have the same amount of digits
			Node *callingNode = msd;
			Node *comparingNode = second.msd;

			while (callingNode != nullptr){
				if (callingNode->digit < comparingNode->digit) {
					return true;
				} else if (callingNode->digit > comparingNode->digit) {
					return false;
				}
				callingNode = callingNode->next_lesser;
				comparingNode = comparingNode->next_lesser;
			}
			//if both HugeInts are the same
			return false;
		}
	} else {//if (sign == MINUS && second.sign == MINUS)
		if (numDigits > second.numDigits){
			return true;
		} else if (numDigits < second.numDigits){
			return false;
		} else { //will execute if both have the same amount of digits
			Node *callingNode = msd;
			Node *comparingNode = second.msd;

			while (callingNode->next_lesser != nullptr){
				if (callingNode->digit * -1 < comparingNode->digit * -1) {
					return true;
				} else if (callingNode->digit * -1 > comparingNode->digit * -1) {
					return false;
				}
				callingNode = callingNode->next_lesser;
				comparingNode = comparingNode->next_lesser;
			}
			//if both HugeInts are the same
			return false;
		}
	}
}


bool HugeInt::operator==(const HugeInt &second) const {
	//compare for equal. return true/false
	if (sign != second.sign){
		return false;
	} else if(numDigits != second.numDigits) {
		return false;
	} else {// will execute if both have the same amount of digits
		Node *callingNode = msd;
		Node *comparingNode = second.msd;

		while (callingNode != nullptr){
			if (callingNode->digit != comparingNode->digit) {
				return false;
			}
			callingNode = callingNode->next_lesser;
			comparingNode = comparingNode->next_lesser;
		}
		//If both HugeInts are the same
		return true;
	}
}


HugeInt HugeInt::operator+(const HugeInt &second) const{
	//add
	HugeInt callingHugeInt;
	callingHugeInt = *this;
	HugeInt copyOfSecond;
	copyOfSecond = second;
	HugeInt copy;

	if (callingHugeInt.sign == PLUS && copyOfSecond.sign == MINUS){
		// EX: 5 + (-3) is the same as  5 - 3 = 2
		copyOfSecond.sign = PLUS;
		copy = callingHugeInt - copyOfSecond;

		if (second < callingHugeInt){
			copy.sign = PLUS;
		} else {
			copy.sign = MINUS;
		}

		return copy;

	} else if (callingHugeInt.sign == MINUS && second.sign == PLUS) {
		// EX: -5 + 3 is the same as  3 - 5 = -2
		callingHugeInt.sign = PLUS;
		copy = callingHugeInt - copyOfSecond;

		if (second < callingHugeInt){
					copy.sign = MINUS;
				} else {
					copy.sign = PLUS;
				}

		return copy;

	} else { // if both HugeInts are Positives or Negatives
		Node *callingNode = callingHugeInt.lsd;
		Node *secondNode = second.lsd;
		int callingDigit, secondDigit, replacementDigit;
		int carryOver = 0;

		//THIS FUNCTION DEALS IN ABSOLUTE HUGE INT VALUE (The negative is added later)
		while (callingNode != nullptr || secondNode != nullptr || carryOver != 0) {// Will execute until outside of both LinkedList and there is no carryOver value
			if (callingNode == nullptr){// will execute if adding a non-existing digit from calling LinkedList
				callingDigit = 0;
			} else {// will execute if adding an existing digit from calling LinkedList
				callingDigit = callingNode->digit;
			}
			if (secondNode == nullptr){// will execute if adding a non-existing digit from second LinkedList
				secondDigit = 0;
			} else {// will execute if adding an existing digit from second LinkedList
				secondDigit = secondNode->digit;
			}

			//THE ADDITION PROCEDURE
			replacementDigit = callingDigit + secondDigit + carryOver; //adds both numbers from each list and any value carried over from the last addition
			carryOver = replacementDigit / 10;// will retrieve the number carried over to the next addition
			replacementDigit = replacementDigit % 10;// will replace the number to it's least significant digit
			copy.insertDigit(replacementDigit);

			if (callingNode != nullptr) {// will move the calling node to it's next greater unless it's already nullptr
				callingNode = callingNode->next_greater;
			}
			if (secondNode != nullptr) {// will move the second node to it's next greater unless it's already nullptr
				secondNode = secondNode->next_greater;
			}
		}

		if (callingHugeInt.sign == PLUS && second.sign ==  PLUS){
			copy.sign = PLUS;
		} else {// if (callingHugeInt.sign == MINUS && second.sign ==  MINUS)]
			copy.sign = MINUS;
		}
		return copy;
	}
}


HugeInt HugeInt::operator-(const HugeInt &second) const{
	//subtract
	HugeInt callingHugeInt;
	callingHugeInt = *this;
	HugeInt copyOfSecond;
	copyOfSecond = second;
	HugeInt copy;

	if (callingHugeInt.sign == PLUS && copyOfSecond.sign == MINUS){
		// EX: 5 - (-3) is the same as 5 + 3 = 8
		copyOfSecond.sign = PLUS;	//Makes the negative HugeInt positive
		copy = callingHugeInt + copyOfSecond;
		copy.sign = PLUS;
		return copy;
	} else if (callingHugeInt.sign == MINUS && second.sign == PLUS) {
		// EX: -5 - 3 is the same as  -(5 + 3) = -8
		callingHugeInt.sign = PLUS;   //Makes the negative HugeInt positive
		copy = callingHugeInt + copyOfSecond;
		copy.sign = MINUS;
		return copy;
	}else if (callingHugeInt.sign == MINUS && second.sign == MINUS) {
		// EX: -3 - (-5) is the same as  3 - 5 = -2
				callingHugeInt.sign = PLUS;
				copyOfSecond.sign = PLUS;
				copy = callingHugeInt - copyOfSecond;
				copy.sign = PLUS;
				return copy;
	} else {// if (callingHugeInt.sign == PLUS && second.sign == PLUS)
		// EX: 5 - 3 = 2

		Node *callingNode = callingHugeInt.lsd;
		Node *secondNode = second.lsd;
		int callingDigit, secondDigit, replacementDigit, top, bottom;
		int borrowOver = 0;

		//THIS FUNCTION DEALS IN ABSOLUTE HUGE INT VALUE
		while (callingNode != nullptr || secondNode != nullptr) {// Will execute until outside of both LinkedList and there is no carryOver value
			if (callingNode == nullptr){// will execute if adding a non-existing digit from calling LinkedList
				callingDigit = 0;
			} else {// will execute if adding an existing digit from calling LinkedList
				callingDigit = callingNode->digit;
			}
			if (secondNode == nullptr){// will execute if adding a non-existing digit from second LinkedList
				secondDigit = 0;
			} else {// will execute if adding an existing digit from second LinkedList
				secondDigit = secondNode->digit;
			}

			//THE SUBTRACTION PROCEDURE
			if (second < callingHugeInt) {
				top = callingDigit - borrowOver;
				bottom = secondDigit;
			} else {
				top = secondDigit - borrowOver;
				bottom = callingDigit;
			}

			if (top < bottom){
				borrowOver = 1;
				top = top + 10;
			}
			replacementDigit = top - bottom;
			copy.insertDigit(replacementDigit);


			//ICRIMENTINT PROCEDURE
			if (callingNode != nullptr) {// will move the calling node to it's next greater unless it's already nullptr
				callingNode = callingNode->next_greater;
			}
			if (secondNode != nullptr) {// will move the second node to it's next greater unless it's already nullptr
				secondNode = secondNode->next_greater;
			}
		}

		if (callingHugeInt.sign == PLUS && second.sign ==  PLUS){
			if (second < callingHugeInt){
				copy.sign = PLUS;
			} else {
				copy.sign = MINUS;
			}
		} else {// if (callingHugeInt.sign == MINUS && second.sign ==  MINUS)
			if (second < callingHugeInt){
				copy.sign = PLUS;
			} else {
				copy.sign = MINUS;
			}
		}
		return copy;
	}
}


void HugeInt::operator=(const HugeInt &second){
	//copy

	//MAKE CURRENT HUGEINT EMPTY
	makeEmpty();

	//DEEP COPY PROCEDURE
	if (second.sign == PLUS) {
		sign = PLUS;
	} else {
		sign = MINUS;
	}

	Node *temp = second.lsd;

	while (temp != nullptr) {
		insertDigit(temp->digit);
		temp = temp->next_greater;
	}
}
