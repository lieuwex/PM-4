#include <string>

#pragma once

class Bignum {
private:
	Bignum *prev;
	Bignum *next;
	int value;

public:
	Bignum();
	Bignum(int);
	Bignum(const Bignum*);
	~Bignum();

	Bignum *prepend(Bignum*);
	Bignum *append(Bignum*);

	std::string stringify(void) const;
	const Bignum *begin(void) const;
	const Bignum *end(void) const;

	static Bignum *sum(const Bignum*, const Bignum*);
	static Bignum *multiply(const Bignum*, const Bignum*);
	static Bignum *fibonacci(int);

	static Bignum *fromString(std::string&);
	static Bignum *fromString(const char*); // REVIEW
};
