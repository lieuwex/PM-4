#include <iostream>
#include <string>
#include "bignum.h"

using namespace std;

int main(void) {
	string sa = "50";
	string sb = "99";

	Bignum *a = Bignum::fromString(sa);
	Bignum *b = Bignum::fromString(sb);

	Bignum res;
	res.sum(a, b);
	cout << res.begin()->strinigfy() << endl;
}
