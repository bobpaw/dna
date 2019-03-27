#include <iostream>

#include "dna.h"
#include "strand.h"

int main (int argc, char *argv[]) {
	if (argc < 2)
		return 0;
	auto arg1 = std::string(argv[1]);
	if (arg1 == "size")
		std::cout << "Codon: " << sizeof(DNA::Codon) << "\nMet: " << sizeof(DNA::Met) << std::endl;
	else if (arg1 == "set") {
		auto a = DNA::Codon("acu");
		std::cout << a;
		a.set(2, 'g');
		std::cout << "\nSetting 2 to G: " <<  a << std::endl;
	} else if (arg1 == "decode") {
		if (argc < 3) return 0;
		auto arg2 = std::string(argv[2]);
		bool started = false;
		DNA::Strand str(arg2);
		for (int i = 0; i < str.size(); ++i) {
			if (str[i] == DNA::Met && !started)
				started = true;
			else if (!started) ++i;
			else if (str[i].letter() == 'O')
				break;
			else
				std::cout << str[i].letter();
		}
		std::cout << std::endl;
	} else if (arg1 == "help")
		std::cout << "DNA tester help\nUsage: " << argv[0] << " [command | codons...]\n"
		"Possible commands:\n"
		"size      Print the sizeof the class and predefined codon\n"
		"set       Print and change a single codon to test changing it\n"
		"---\n"
		"codons... Print the names of codons with string codes" << std::endl;
	else
		for (int i = 1; i < argc; ++i)
			std::cout << DNA::Codon(argv[i]).name() << std::endl;
	return 0;
}
