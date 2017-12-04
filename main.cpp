#include <iostream>
#include <string>
#include "bignum.h"

using namespace std;

int main(void) {
	for (int i = 0; i < 50; i++) {
		Bignum *fib = Bignum::fibonacci(i);
		cout << "\t" << i << ": " << fib->stringify() << endl;
		delete fib;
	}
}
