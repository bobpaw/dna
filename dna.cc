#include <iostream>

#include "dna.h"

int main () {
	std::cout << (std::string) DNA::Met << std::endl;
	std::cout << (std::string) DNA::Codon(DNA::RNA, DNA::C, DNA::G, DNA::A) << std::endl;
	std::cout << DNA::Met() << std::endl;
	return 0;
}
