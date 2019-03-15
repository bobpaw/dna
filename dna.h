#include <string>

#ifndef DNA_DNA_H_
#define DNA_DNA_H_

namespace DNA {
	const unsigned char A = 0, T = 1, U = T, C = 2, G = 3, DNA = 0, RNA = 1;
	class Codon {
	private:
		unsigned char bm;
	public:
		Codon (unsigned char t, unsigned char b1, unsigned char b2, unsigned char b3) {
			setType(t);
			set(0, b1);
			set(1, b2);
			set(2, b3);
		}

		Codon (unsigned char b) : bm(b) {}

		unsigned char operator[] (int n) const {
			return (bm >> n * 2) & 0x3;
		}

		unsigned char operator() () const { return bm; }

		void set (int n, unsigned char val) {
			val &= 0x3;
			val <<= n * 2;
			bm &= ~(0x3 << n * 2);
			bm |= val;
		}

		void setType (unsigned char t) {
			bm &= ~(64);
			bm |= t & 1 == 1 ? 64 : 0;
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
	} Met(RNA, A, U, G); // class Codon
} // namespace DNA

#endif
