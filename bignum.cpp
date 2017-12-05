#include <algorithm>
#include <iomanip>
#include <iostream>
#include <cassert>
#include <cmath>
#include <sstream>
#include "bignum.h"

#define NODE_SIZE 2

using namespace std;

Bignum::Bignum() {
	this->prev = nullptr;
	this->next = nullptr;
	this->value = 0;
}

Bignum::Bignum(int n) {
	assert(n < pow(10, NODE_SIZE));

	this->prev = nullptr;
	this->next = nullptr;
	this->value = n;
}

// only copies to right
Bignum::Bignum(const Bignum *num) {
	this->prev = num->prev;
	this->next = num->next ? new Bignum(num->next) : nullptr;
	this->value = num->value;
}

Bignum::~Bignum() {
	delete this->next;
	this->next = nullptr;
}


Bignum *Bignum::prepend(Bignum *num) {
	num->prev = this->prev;
	this->prev = num;
	num->next = this;
	return num;
}

Bignum *Bignum::append(Bignum *num) {
	num->next = this->next;
	this->next = num;
	num->prev = this;
	return num;
}


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

const Bignum *Bignum::begin(void) const {
	const Bignum *current = this;
	while (current->prev) {
		current = current->prev;
	}
	return current;
}
const Bignum *Bignum::end(void) const {
	const Bignum *current = this;
	while (current->next) {
		current = current->next;
	}
	return current;
}


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

Bignum *Bignum::multiply(const Bignum *a, const Bignum *b) {
	// TODO
}

Bignum *Bignum::fibonacci(int n) {
	assert(n < 10000); // as stated in the exercice

	if (n == 0 || n == 1) {
		return new Bignum(n);
	}

	Bignum *result;
	Bignum *first = new Bignum(0);
	Bignum *second = new Bignum(1);

	for (int i = 0; i < n-1; i++) {
		result = Bignum::sum(first, second);

		delete first;
		first = second;

		second = result;
	}

	delete first;
	// don't delete second
	return result;
}

Bignum *Bignum::factorial(const Bignum *to) {
	Bignum one(1);

	Bignum *res = new Bignum(1);
	Bignum *i = new Bignum(2);

#define RUN() do { \
		Bignum *newres = Bignum::multiply(res, i); \
		delete res; \
		res = newres; \
		\
		Bignum *newI = Bignum::sum(i, &one); \
		delete i; \
		i = newI; \
	} while(0)

	while (i->stringify() != to->stringify()) {
		RUN();
	}
	RUN(); // one time more

	delete i;
	return res;

#undef RUN
}


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

Bignum *Bignum::makeZeroes(long long m) {
	return Bignum::fromString(string(m * NODE_SIZE, '0'));
}
