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
	~Bignum();

	void multiply(const Bignum&, const Bignum&);
	void fibonacci(int);

	Bignum *begin(void);
	Bignum *end(void);

	Bignum *prepend(Bignum*);
	Bignum *append(Bignum*);

	std::string strinigfy(void) const;

	static Bignum *sum(Bignum*, Bignum*);
	static Bignum *fromString(std::string&);
	static Bignum *fromString(const char*); // REVIEW
};
