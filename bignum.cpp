#include <algorithm>
#include <iomanip>
#include <iostream>
#include <cassert>
#include <cmath>
#include <sstream>
#include "bignum.h"

#define NODE_SIZE 2

using namespace std;

// Create a single empty Bignum cell.
Bignum::Bignum() {
	this->prev = nullptr;
	this->next = nullptr;
	this->value = 0;
}

// Create a single Bignum cell with value n.
Bignum::Bignum(int n) {
	assert(n < pow(10, NODE_SIZE));

	this->prev = nullptr;
	this->next = nullptr;
	this->value = n;
}

// Create a new Bignum that is a copy of the given `num`.
// Only copies to right
Bignum::Bignum(const Bignum *num) {
	this->prev = num->prev;
	this->next = num->next ? new Bignum(num->next) : nullptr;
	this->value = num->value;
}

// Deletes the current Bignum
Bignum::~Bignum() {
	delete this->next;
	this->next = nullptr;
}


// Prepends the given `num` to the current Bignum instance.
// Manipulates `num`.
Bignum *Bignum::prepend(Bignum *num) {
	num->prev = this->prev;
	this->prev = num;
	num->next = this;
	return num;
}

// Appends the given `num` to the current Bignum instance.
// Manipulates `num`.
Bignum *Bignum::append(Bignum *num) {
	num->next = this->next;
	this->next = num;
	num->prev = this;
	return num;
}


// Return a string representing the current Bignum instance.
string Bignum::stringify(void) const {
	stringstream ss;

	const Bignum *current = this;
	ss << current->value;
	while (current->next != nullptr) {
		current = current->next;
		ss << setfill('0') << setw(NODE_SIZE) << current->value;
	}

	return ss.str();
}

// Return a pointer to the first cell of the list of the current Bignum.
const Bignum *Bignum::begin(void) const {
	const Bignum *current = this;
	while (current->prev) {
		current = current->prev;
	}
	return current;
}
// Return a pointer to the last cell of the list of the current Bignum.
const Bignum *Bignum::end(void) const {
	const Bignum *current = this;
	while (current->next) {
		current = current->next;
	}
	return current;
}


// Returns a new Bignum containing the sum of `a` and `b`.
Bignum *Bignum::sum(const Bignum *a, const Bignum *b) {
	unsigned short carry = 0;

	Bignum *res = nullptr;
	a = a->end();
	b = b->end();

	while (a != nullptr || b != nullptr || carry != 0) {
		int aVal = a ? a->value : 0;
		int bVal = b ? b->value : 0;

		res = res == nullptr ?
			new Bignum() :
			res->prepend(new Bignum());

		res->value = aVal + bVal + carry;
		// set possible carry
		carry = res->value / pow(10, NODE_SIZE);
		res->value %= (int)pow(10, NODE_SIZE);

		if (a != nullptr) a = a->prev;
		if (b != nullptr) b = b->prev;
	}

	return res;
}

// Returns a new Bignum containing the product of `a` and `b`.
Bignum *Bignum::multiply(const Bignum *a, const Bignum *b) {
	// do some little tricks for *0 and *1
	{
		a = a->begin();
		b = b->begin();

		string aStr = a->stringify();
		string bStr = b->stringify();

		if (aStr == "0" || bStr == "0") {
			return new Bignum(0);
		} else if (aStr == "1") {
			return new Bignum(b);
		} else if (bStr == "1") {
			return new Bignum(a);
		}
	}

	Bignum *res = new Bignum(0);

	const Bignum *currA = a->end(); // don't free
	long long baseShift = 0;
	while (currA != nullptr) {
		long long shift = baseShift;

		const Bignum *currB = b->end(); // don't free
		while (currB != nullptr) {
			long long val = currA->value * currB->value;
			long long carry = val / pow(10, NODE_SIZE);
			val %= (int)pow(10, NODE_SIZE);

			Bignum *num = new Bignum(0);
			for (long long i = 1; i <= shift; i++) {
				num = num->prepend(new Bignum(0));
			}
			num->value = val;
			while (carry > 0) {
				long long val = carry % (int)pow(10, NODE_SIZE);
				carry /= pow(10, NODE_SIZE);
				num = num->prepend(new Bignum(val));
			}

			Bignum *newRes = Bignum::sum(res, num);
			delete res;
			delete num;
			res = newRes;

			currB = currB->prev;
			shift++;
		}

		currA = currA->prev;

		baseShift++;
	}

	return res;
}

// Returns a new Bignum containing the `n`th Fibonacci number.
Bignum *Bignum::fibonacci(unsigned int n) {
	if (n == 0 || n == 1) {
		return new Bignum(n);
	}

	Bignum *result;
	Bignum *first = new Bignum(0);
	Bignum *second = new Bignum(1);

	for (unsigned int i = 0; i < n-1; i++) {
		result = Bignum::sum(first, second);

		delete first;
		first = second;

		second = result;
	}

	delete first;
	// don't delete second
	return result;
}

// Returns a new Bignum containing `n`!.
Bignum *Bignum::factorial(int n) {
	assert(n < pow(10, NODE_SIZE));

	Bignum *res = new Bignum(1);

	for (int i = 1; i <= n; i++) {
		Bignum tmp(i);
		Bignum *newres = Bignum::multiply(res, &tmp);
		delete res;
		res = newres;
	}

	return res;
}


// Returns a new Bignum representing the value of the given base10 string.
Bignum *Bignum::fromString(string str) {
	Bignum *current = nullptr;
	reverse(str.begin(), str.end());

	for (size_t i = 0; i < str.size(); i += NODE_SIZE) {
		string slice = str.substr(i, NODE_SIZE);
		reverse(slice.begin(), slice.end());

		Bignum *num = new Bignum(stoi(slice));
		current = current == nullptr ?
			num :
			current->prepend(num);
	}

	return current;
}

// Returns a new Bignum that exists of `m` cells, filled with zeroes.
Bignum *Bignum::makeZeroes(long long m) {
	return Bignum::fromString(string(m * NODE_SIZE, '0'));
}
