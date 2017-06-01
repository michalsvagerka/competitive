#include "mod.h"
#include <vector>
namespace FFT {
	const unsigned int MAX_BITS = 25;
	const unsigned int PRIME = 4194304001u;
	const unsigned int OMEGA[] = {1u, 4194304000u, 809539273u, 2303415184u, 1800537630u, 1287904184u, 3915137183u,
								  341015394u, 418248771u, 2297133295u, 246248871u, 91156249u, 911964167u, 1905142968u,
								  888982599u, 3459657251u, 577736066u, 2694679249u, 779825358u, 2946902746u,
								  2007716871u, 4100601466u, 374757901u, 1568239201u, 39601u, 199u};
	const unsigned int OMEGA_INV[] = {1u, 4194304000u, 3384764728u, 3412379098u, 1559634102u, 2633613076u, 1804313316u,
									  3353703883u, 103452218u, 3326307677u, 1194130126u, 176344934u, 298085440u,
									  2167853111u, 2564851092u, 3922803478u, 941634782u, 1390530532u, 3386056271u,
									  2737677338u, 3042570214u, 2405831823u, 4070788264u, 3279912072u, 2785964305u,
									  758768563u};

	typedef Field<PRIME> F;

	void fft(std::vector<F> &V, bool inverse = false) {
		int P = 1;
		while ((1u << P) < V.size()) ++P;
		V.resize(1u << P);
		fft(V, P, inverse);
	}

	void fft(std::vector<F> &V, const int P, bool inverse = false) {
		if (P == 0) return;
		if (P > MAX_BITS) throw std::runtime_error("Number of bits in FFT too large");
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
}