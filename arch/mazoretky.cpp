#include "../l/lib.h"
// #include "../l/mod.h"

int MAX = 1000000000;

class mazoretky {
public:

	vector<int> A, U1, D2, D1, U2, O;
	int N;
	vector<int> SOL;

	vector<int> flatten(vector<vector<int>> V) {
		vector<int> W;
		for (auto &v: V) for (auto &vv:v) W.push_back(vv);
		sort(W.begin(), W.end());
		return W;
	}

	bool isasc(vector<int> V) {
		int l = 0;
		for (int v: V) {
			if (A[v] <= l) return false;
			l = A[v];
		}
		return true;
	}

	bool isdesc(vector<int> V) {
		int l = MAX+1;
		for (int v: V) {
			if (A[v] >= l) return false;
			l = A[v];
		}
		return true;
	}

	bool gen(vector<int> & U, vector<int> & D, int i) {
		if (i == O.size()) {
			if (isasc(flatten({U1, U, U2})) && isdesc(flatten({D1, D, D2}))) {
				SOL = flatten({U1, U, U2});
				return true;
			} return false;
		}

		U.push_back(O[i]);
		if (gen(U,D,i+1)) return true;
		U.pop_back();
		D.push_back(O[i]);
		if (gen(U,D,i+1)) return true;
		D.pop_back();
		return false;
	}

	void solve(istream& cin, ostream& cout) {
		cin >> N;
		A.resize(N); cin >> A;

		int T = bsh(0, MAX, [&](int T) {
			int l = 0; bool d = false;
			for (int i = 0; i < N; ++i) {
				if (A[i] > T) continue;
				if (d && A[i] >= l) return false;
				if (!d && A[i] <= l) { d = true; }
				l = A[i];
			}
			return true;
		});

		int l = MAX + 1;
		bool d = false;
		for (int i = 0; i < N; ++i) {
			if (A[i] <= T) continue;
			if (d && A[i] <= l) { cout << "Impossible\n"; return; }
			if (!d && A[i] >= l) { d = true; }
			if (d) U2.push_back(i); else D1.push_back(i);
			l = A[i];
		}

		l = 0; d = false;
		for (int i = 0; i < N; ++i) {
			if (A[i] > T) continue;
			if (!d && A[i] <= l) { d = true; }
			if (d) D2.push_back(i); else U1.push_back(i);
			l = A[i];
		}

		if (!U1.empty()) { O.push_back(U1.back()); U1.pop_back(); }
		if (!D1.empty()) { O.push_back(D1.back()); D1.pop_back(); }
		sort(O.begin(), O.end());
		vector<int> U, D;

		if (gen(U, D, 0)) {
			if (SOL.size() == 0) SOL.push_back(0);
			if (SOL.size() == N) SOL.pop_back();
			for(int&s:SOL) ++s;
			cout << SOL.size() << endl << SOL;
		} else {
			cout << "Impossible\n"; return;
		}
	}
};


