#include <vector>

#include "dna.h"

#ifndef DNA_STRAND_H_
#define DNA_STRAND_H_

namespace DNA {
	class Strand {
		std::vector<Codon> code;
	public:
		Strand () {}

		Strand (std::string str) {
			code.reserve(str.size() / 3);
			for (int i = 0; i < str.size(); i += 3) {
				code.emplace_back(DNA::Codon(str.substr(i, 3)));
			}
		}

		Codon operator[] (int n) const { return code[n]; }

		auto size () const { return code.size(); }

		operator std::string () const {
			std::string ret;
			for (auto i : code) ret += (std::string) i;
			return ret;
		}
	}; // class Strand
} // namespace DNA

#endif // DNA_STRAND_H_
