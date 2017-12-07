#include "mod.h"
#include <vector>
#include <array>

template <ui P> struct Group {};
template <> struct Group<4194304001u> { constexpr static ui bits = 25, root = 199, rootInverse = 758768563u; };
template <> struct Group<998244353u> { constexpr static ui bits = 23, root = 31, rootInverse = 128805723; };
template <> struct Group<104857601u> { constexpr static ui bits = 22, root = 21, rootInverse = 49932191; };
template <> struct Group<924844033u> { constexpr static ui bits = 21, root = 3597, rootInverse = 508059997; };

template <ui Prime> class FFT {
public:
	typedef Field<Prime> F;

	FFT() {
		OMEGA[Group<Prime>::bits] = Group<Prime>::root;
		OMEGA_INV[Group<Prime>::bits] = Group<Prime>::rootInverse;
		for (size_t i = Group<Prime>::bits; i > 0; --i) {
			OMEGA[i-1] = ui((ull(OMEGA[i])*ull(OMEGA[i]))%Prime);
			OMEGA_INV[i-1] = ui((ull(OMEGA_INV[i])*ull(OMEGA_INV[i]))%Prime);
		}
	}

	void fft(std::vector<F> &V, bool inverse = false) {
		int P = 1;
		while ((1u << P) < V.size()) ++P;
		V.resize(1u << P);
		fft(V, P, inverse);
	}

	void fft(std::vector<F> &V, const int P, bool inverse = false) {
		if (P == 0) return;
		if (P > Group<Prime>::bits) throw std::runtime_error("Number of bits in FFT too large");
		if (V.size() != (1 << P)) throw std::runtime_error("Vector has wrong size");
		for (int i = 1, j = 0; i < (1 << P); ++i) {
			int bit = (1 << (P - 1));
			for (; j >= bit; bit >>= 1) j -= bit;
			j += bit;
			if (i < j) std::swap(V[i], V[j]);
		}

		for (int B = 1; B <= P; ++B) {
			F omega = inverse ? OMEGA_INV[B] : OMEGA[B];
			for (int i = 0; i < (1 << P); i += (1 << B)) {
				F x = 1;
				for (int j = 0; j < (1 << (B - 1)); j++) {
					F u = V[i + j], v = V[i + j + (1 << (B - 1))] * x;
					V[i + j] = u + v;
					V[i + j + (1 << (B - 1))] = u - v;
					x *= omega;
				}
			}
		}

		if (inverse) {
			F q = 1 / F(1 << P);
			for (F &v:V) v *= q;
		}
	}

private:
	std::array<ui, Group<Prime>::bits+1> OMEGA, OMEGA_INV;
};
