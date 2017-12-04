#include <iomanip>
#include <cassert>
#include <cmath>
#include <sstream>
#include "bignum.h"

#define NODE_SIZE 2

using namespace std;

template <class T>
int ndigits(T num)
{
	int len = 0;
	while (num) {
		num /= 10;
		len++;
	}
	return len;
}

Bignum::Bignum() {
	this->prev = nullptr;
	this->next = nullptr;
}
Bignum::Bignum(int n) {
	this->prev = nullptr;
	this->next = nullptr;
	this->value = n;
}
Bignum::~Bignum() {
	delete this->prev;
}

Bignum *Bignum::begin(void) {
	Bignum *current = this;
	while (current->prev) {
		current = current->prev;
	}
	return current;
}
Bignum *Bignum::end(void) {
	Bignum *current = this;
	while (current->next) {
		current = current->next;
	}
	return current;
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

Bignum *Bignum::sum(Bignum *a, Bignum *b) {
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
		carry = 0;
		// set possible carry
		if (ndigits(res->value) > NODE_SIZE) {
			carry = res->value / pow(10, NODE_SIZE);
			res->value -= carry * pow(10, NODE_SIZE);
		}

		if (a != nullptr) a = a->prev;
		if (b != nullptr) b = b->prev;
	}

	return res;
}

void Bignum::fibonacci(int n) {
	assert(n < 10000);
}

Bignum *Bignum::fromString(string &str) {
	Bignum *current = nullptr;
	reverse(str.begin(), str.end());

	for (size_t i = 0; i < str.size(); i += NODE_SIZE) {
		string slice = str.substr(i, NODE_SIZE);
		reverse(slice.begin(), slice.end());

		Bignum *num = new Bignum(stoi(slice));
		if (current == nullptr) {
			current = num;
		} else {
			current = current->prepend(num);
		}
	}

	return current;
}

Bignum *Bignum::fromString(const char *str) {
	string s = str;
	return Bignum::fromString(s);
}
