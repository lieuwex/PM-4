#pragma once

class Bignum {
private:

public:
	Bignum();
	~Bignum();

	void add(const Bignum&, const Bignum&);
	void multiply(const Bignum&, const Bignum&);
	void fibonacci(int);

	void strinigfy(void) const;
};
