#include <string>
#include <iostream>
#include <cstdint>

#ifndef DNA_DNA_H_
#define DNA_DNA_H_

namespace DNA {
	const char letters[65] = "KOQEILLVTSPARORGNYHDIFLVTSPASCRGNYHDIFLVTSPASCRGKOQEMLLVTSPARWRG";

	const char names[64][4] = {"Lys", "Stp", "Gln", "Glu", "Ile", "Leu", "Leu",
	"Val", "Thr", "Ser", "Pro", "Ala", "Arg", "Stp", "Arg", "Gly", "Asn", "Tyr",
	"His", "Asp", "Ile", "Phe", "Leu", "Val", "Thr", "Ser", "Pro", "Ala", "Ser",
	"Cys", "Arg", "Gly", "Asn", "Tyr", "His", "Asp", "Ile", "Phe", "Leu", "Val",
	"Thr", "Ser", "Pro", "Ala", "Ser", "Cys", "Arg", "Gly", "Lys", "Stp", "Gln",
	"Glu", "Met", "Leu", "Leu", "Val", "Thr", "Ser", "Pro", "Ala", "Arg", "Trp",
	"Arg", "Gly"};

	const uint_least8_t A = 0, T = 1, U = T, C = 2, G = 3, DNA = 0, RNA = 1;
	class Codon {
	private:
		uint_least8_t bm;
	public:
		Codon () : bm(0) {}
		Codon (decltype(bm) t, decltype(bm) b1, decltype(bm) b2, decltype(bm) b3) {
			setType(t);
			set(0, b1);
			set(1, b2);
			set(2, b3);
		}

		Codon (decltype(bm) b) : bm(b) {}

		Codon (std::string str) : bm(0) {
			setType(RNA);
			if (str.size() >= 3)
				for (int i = 0; i < 3; ++i)
					switch ((char) str[i]) {
						case 'A': case 'a':
						set(i, A); break;
						case 'T': case 't':
						case 'U': case 'u':
						set(i, U); break;
						case 'C': case 'c':
						set(i, C); break;
						case 'G': case 'g':
						set(i, G); break;
					}
		}

		decltype(bm) operator[] (int n) const noexcept {
			return (bm >> n * 2) & 0x3;
		}

		decltype(bm) operator() () const noexcept { return bm; }
		decltype(bm) & operator() () noexcept { return bm; }

		decltype(letters[0]) letter (void) const { return letters[(int) (bm & 63)]; }
		decltype(names[0]) name (void) const { return names[(int) (bm & 63)]; }

		void set (int n, decltype(bm) val) noexcept {
			switch (val) {
			case 'A':
			case 'a':
				val = A; break;
			case 'T':
			case 't':
			case 'U':
			case 'u':
				val = U; break;
			case 'C':
			case 'c':
				val = C; break;
			case 'G':
			case 'g':
				val = G; break;
			default:
				val &= 0x3;
			}
			val <<= n * 2;
			bm &= ~(0x3 << n * 2);
			bm |= val;
		}

		void setType (decltype(DNA) t) noexcept {
			if (t & 1 == 0) {
				bm &= ~(64);
			} else {
				bm |= 64;
			}
		}

		operator std::string () const {
			std::string ret(3, 0);
			for (int i = 0; i < 3; ++i) {
				switch (operator[] (i)) {
				case A:
					ret[i] = 'A';
					break;
				case T:
					ret[i] = (bm & 64 == DNA ? 'T' : 'U');
					break;
				case C:
					ret[i] = 'C';
					break;
				case G:
					ret[i] = 'G';
					break;
				default:
					ret[i] = '?';
				}
			}
			return ret;
		}

		bool operator== (const Codon &other) const noexcept {
			return bm == other.bm;
		}

		bool operator!= (const Codon &other) const noexcept {
			return !operator==(other);
		}

		friend std::ostream& operator<< (std::ostream& stream, const Codon& codon) {
			for (int i = 0; i < 3; ++i)
				switch (codon[i]) {
				case A:
					stream << 'A'; break;
				case T:
					stream << (codon.bm & 64 == DNA ? 'T' : 'U'); break;
				case C:
					stream << 'C'; break;
				case G:
					stream << 'G'; break;
				default:
					stream << '?';
				}
			return stream;
		}
	} Met(RNA, A, U, G); // class Codon
} // namespace DNA

#endif // DNA_DNA_H_
