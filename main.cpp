/*
 * Auteurs: Lieuwe Rooijakkers (s2012820) en Bart de Zoete (s2030098)
 * Compiler: clang++ 800.0.42.1
 * Last modified on: 2017-12-07
 *
 * PM opdracht 4: Grote getallen
 */

#define _GNU_SOURCE // asprintf

#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include "bignum.h"

using namespace std;

unique_ptr<Bignum> nums[5];

// Splits the given string `str` on the string delimiter `delim` into a
// vector<string>.
vector<string> split(const string &str, const string &delim) {
	vector<string> res;
	string::size_type start = 0U;
	string::size_type end = str.find(delim);

	while (end != string::npos) {
		res.push_back(str.substr(start, end - start));
		start = end + delim.length();
		end = str.find(delim, start);
	}

	res.push_back(str.substr(start, end)); // add rest
	return res;
}

// Trims the given string `s`, that means: remove leading and trailing spaces
// and tabs.
string trim(const string &s) {
	string::size_type begin = s.find_first_not_of(" \t");
	string::size_type end = s.find_last_not_of(" \t");

	if (begin == string::npos) {
		return "";
	} else {
		return s.substr(begin, end - begin + 1);
	}
}

struct Command {
	string name;
	vector<string> args;
};

// Parses the given `line` as a Command.
Command parseLine(const string &line) {
	vector<string> words = split(trim(line), " ");
	return {
		.name = words[0],
		.args = vector<string>(words.begin()+1, words.end()),
	};
}

// Returns the index of the bignum var represented by `c`.
int getNumber(char c) {
	switch (c) {
	case 'a': case 'A':
		return 0;
	case 'b': case 'B':
		return 1;
	case 'c': case 'C':
		return 2;
	case 'd': case 'D':
		return 3;
	case 'e': case 'E':
		return 4;

	default:
		return -1;
	}
}

// Runs the given `command`, fills the string at `error` with the error, if any.
// Returns true when the prompt should quit.
bool runCommand(Command &command, char **error) {
#define GETNUM(val, c, err) \
	int val = getNumber(c); \
	if (err && val == -1) { \
		asprintf(error, "unknown bignum var '%c'", (c)); \
		return false; \
	}

	if (command.name == "p" || command.name == "print") { // print <val>
		GETNUM(num, command.args[0][0], true);

		cout << nums[num]->begin()->stringify() << endl;
	} else if (command.name == "s" || command.name == "set") { // set <dest> <val>
		GETNUM(destNum, command.args[0][0], true);
		GETNUM(valNum, command.args[1][0], false);

		nums[destNum].reset(
			valNum >= 0 ?
				new Bignum(*nums[valNum]) :
				Bignum::fromString(command.args[1])
		);
	} else if (command.name == "+" || command.name == "add") { // add <dest> <a> <b>
		GETNUM(destNum, command.args[0][0], true);
		GETNUM(aNum, command.args[1][0], true);
		GETNUM(bNum, command.args[2][0], true);

		nums[destNum].reset(Bignum::sum(nums[aNum].get(), nums[bNum].get()));
	} else if (command.name == "*" || command.name == "multiply") { // multiply <dest> <a> <b>
		GETNUM(destNum, command.args[0][0], true);
		GETNUM(aNum, command.args[1][0], true);
		GETNUM(bNum, command.args[2][0], true);

		nums[destNum].reset(Bignum::multiply(nums[aNum].get(), nums[bNum].get()));
	} else if (command.name == "!" || command.name == "factorial") { // factorial <dest> <n>
		GETNUM(destNum, command.args[0][0], true);
		nums[destNum].reset(Bignum::factorial(stoi(command.args[1])));
	} else if (command.name == "fib" || command.name == "fibonacci") { // factorial <dest> <n>
		GETNUM(destNum, command.args[0][0], true);
		nums[destNum].reset(Bignum::fibonacci(stoi(command.args[1])));
	} else if (command.name == "h" || command.name == "help") { // help
		cout << "=== VARIABLES" << endl;
		cout << "a=" << nums[0]->stringify() << endl;
		cout << "b=" << nums[1]->stringify() << endl;
		cout << "c=" << nums[2]->stringify() << endl;
		cout << "d=" << nums[3]->stringify() << endl;
		cout << "e=" << nums[4]->stringify() << endl;
		cout << "=== COMMANDS" << endl;
		cout << "print <val>\t\t\tprints the given variable" << endl;
		cout << "set <dest> <val>\t\tsets dest to the given numeric value or bignum variable" << endl;
		cout << "add <dest> <a> <b>\t\tsets dest to the result of a+b" << endl;
		cout << "multiply <dest> <a> <b>\t\tsets dest to the result of a*b" << endl;
		cout << "fibonacci <dest> <n>\t\tsets dest to the value of F_n where n is an integer" << endl;
		cout << "factorial <dest> <n>\t\tsets dest to the value of n! where n is an integer" << endl;
		cout << "quit\t\t\t\tquits the program" << endl;
	} else if (command.name == "q" || command.name == "quit" || command.name == "exit") { // quit
		return true;
	} else {
		asprintf(error, "unknown command '%s'", command.name.c_str());
	}

	return false;

#undef GETNUM
}

void printInfoBlock(void) {
	cout << "--------------------------------------------------------------------------------" << endl;
	cout << "|                                Grote getallen                                |" << endl;
	cout << "|                                     PM4                                      |" << endl;
	cout << "|                                                                              |" << endl;
	cout << "|             Geschreven door Lieuwe Rooijakkers en Bart de Zoete              |" << endl;
	cout << "|                                  s2012820           s2030098                 |" << endl;
	cout << "|                                                                              |" << endl;
	cout << "|     Dit programma stelt de gebruiker in staat om te rekenen met arbitrair    |" << endl;
	cout << "|                     lange getallen groter dan INT_MAX                        |" << endl;
	cout << "|                                                                              |" << endl;
	cout << "|                         enter 'help' to print help                           |" << endl;
	cout << "--------------------------------------------------------------------------------" << endl;
	cout << endl;
}

int main(void) {
	printInfoBlock();

	nums[0] = unique_ptr<Bignum>(new Bignum(0));
	nums[1] = unique_ptr<Bignum>(new Bignum(1));
	nums[2] = unique_ptr<Bignum>(new Bignum(2));
	nums[3] = unique_ptr<Bignum>(new Bignum(3));
	nums[4] = unique_ptr<Bignum>(new Bignum(4));

	while (true) {
		cout << "> " << flush;

		string line;
		getline(cin, line);

		if (cin.eof()) {
			cout << endl;
			break;
		}

		Command command = parseLine(line);

		char *err = nullptr;
		bool exit = runCommand(command, &err);
		if (err != nullptr) {
			cerr << err << endl;
			free(err);
		}

		if (exit) {
			break;
		}
	}

	cout << "bye!" << endl;
	return 0;
}
