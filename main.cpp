#include <iostream>
#include <string>
#include "bignum.h"

using namespace std;

int main(void) {
	for (int i = 0; i <= 2000; i++) {
		Bignum *fib = Bignum::fibonacci(i);
		cout << i << ": " << fib->stringify() << endl;
		delete fib;
	}
}
