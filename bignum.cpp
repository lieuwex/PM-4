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

void Bignum::sum(const Bignum *a, const Bignum *b) {
#define APPLY(num, a, b) do {\
	num->value = a + b + carry; \
	carry = 0; \
	if (ndigits(num->value) > NODE_SIZE) { \
		carry = num->value / pow(10, NODE_SIZE); \
		num->value -= carry * pow(10, NODE_SIZE); \
	} \
} while(0);

	unsigned short carry = 0;
	APPLY(this, a->value, b->value);

	Bignum *curr = this->prepend(new Bignum());
	while (a->prev || b->prev || carry) {
		long aPrev = a->prev ? a->prev->value : 0;
		long bPrev = b->prev ? b->prev->value : 0;
		APPLY(curr, aPrev, bPrev);
	}

#undef APPLY
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

string Bignum::strinigfy(void) const {
	stringstream ss;

	const Bignum *current = this;
	do {
		ss << current->value;
		current = current->next;
	} while (current != nullptr);

	return ss.str();
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
			current->prepend(num);
		}
	}

	return current;
}
