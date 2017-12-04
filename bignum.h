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

	Bignum *begin(void);
	Bignum *end(void);

	Bignum *prepend(Bignum*);
	Bignum *append(Bignum*);

	std::string stringify(void) const;

	static Bignum *sum(Bignum*, Bignum*);
	static Bignum *fibonacci(int);
	static Bignum *fromString(std::string&);
	static Bignum *fromString(const char*); // REVIEW
};
