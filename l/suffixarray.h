#include "lib.h"
#include <type_traits>

// ordinary suffix array with optional LCP and LCP RMQ. look elsewhere
template<typename Index, bool PrecomputeLCP = false, bool PrecomputeRMQ = false>
class SuffixArray {
public:
	static_assert(PrecomputeLCP || !PrecomputeRMQ, "Must have RMQ for LCP");

	template<typename T>
	explicit SuffixArray(T t):N(t.size()), S(N), I(N), LCP(PrecomputeLCP ? N : 0) {
		typedef typename std::remove_reference<decltype(t[0])>::type Item;
		vector<pair<Item, Index>> TR(N);
		for (Index i = 0; i < N; ++i) { TR[i] = {t[i], i}; }
		sort(TR.begin(), TR.end());
		vector<Index> R(N);
		Index r = R[TR[0].y] = S[TR[0].y] = 0;
		for (Index i = 1; i < N; ++i) {
			R[TR[i].y] = r += (TR[i - 1].x != TR[i].x);
			S[TR[i].y] = i;
		}
		vector<Index> RA(N), SA(N), C(N);
		for (Index k = 1; k < N; k <<= 1) {
			counting_sort(R, C, SA, k, r+1);
			counting_sort(R, C, SA, 0, r+1);
			RA[S[0]] = r = 0;
			for (Index i = 1; i < N; ++i) {
				RA[S[i]] = r += (R[S[i]] != R[S[i-1]] || S[i]+k >= N || S[i-1]+k >= N ||
								R[S[i]+k] != R[S[i-1]+k]);
			}
			swap(RA, R);
			if (R[S[N-1]] == N-1) break;
		}
		for (Index i = 0; i < N; ++i) { I[S[i]] = i; }
		if (PrecomputeLCP) {
			Index k = 0;
			for (Index i = 0; i < N; ++i) {
				if (I[i] == N - 1) {
					LCP[I[i]] = k = 0;
					continue;
				}
				while (i + k < N && S[I[i] + 1] + k < N && t[i + k] == t[S[I[i] + 1] + k]) { ++k; }
				LCP[I[i]] = k;
				if (k > 0) { --k; }
			}
		}
		if (PrecomputeRMQ) {
			RMQ.push_back(LCP);
			for (int p = 0; (1 << p) < N; ++p) {
				RMQ.push_back(RMQ[p]);
				for (int i = 0; i < N - (1 << p); ++i) { RMQ[p + 1][i] = min(RMQ[p + 1][i], RMQ[p][i + (1 << p)]); }
			}
		}
	}

	Index next(Index i) { return (I[i] == N - 1) ? -1 : S[I[i] + 1]; }

	template<typename=std::enable_if<PrecomputeLCP>>
	Index lcp(Index i) const { return LCP[I[i]]; }

	template<typename=std::enable_if<PrecomputeRMQ>>
	Index lcp(Index i, Index j) const {
		i = I[i];
		j = I[j];
		if (i > j) { swap(i, j); }
		if (i == j - 1)return LCP[i];
		Index p = 0;
		while ((1 << p) < j - i) { ++p; }
		--p;
		return min(RMQ[p][i], RMQ[p][j - (1 << p)]);
	}

	inline void counting_sort(const vector<int> &R, vector<int> &C, vector<int> &SA, int k, int r) {
		Index i;
		fill(C.begin(), C.begin()+r, 0);
		for (i = k; i < N; i++) C[R[i]]++;
		C[0] += k;
		for (Index sum = i = 0; i < r; i++) { C[i] = (sum += C[i], sum - C[i]); }
		if (k) for (i = 0; i < N; i++) { SA[C[S[i]+k<N ? R[S[i]+k] : 0]++] = S[i]; }
		else for (i = 0; i < N; i++) { SA[C[R[S[i]]]++] = S[i]; }
		swap(SA, S);
	}

	Index N;
	vector<Index> S, I, LCP;
	vector<vector<Index>> RMQ;
};