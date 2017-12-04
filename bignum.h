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

	void multiply(const Bignum&, const Bignum&);

	const Bignum *begin(void) const;
	const Bignum *end(void) const;

	Bignum *prepend(Bignum*);
	Bignum *append(Bignum*);

	std::string stringify(void) const;

	static Bignum *sum(const Bignum*, const Bignum*);
	static Bignum *fibonacci(int);
	static Bignum *fromString(std::string&);
	static Bignum *fromString(const char*); // REVIEW
};
