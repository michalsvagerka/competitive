#include "../l/lib.h"
// #include "../l/mod.h"

class revsubst {
public:
	deque<vector<int>> Last;
	vector<vector<int>> First;
	vector<int> C;
	int Sols;

	void solve(int i, int N, vector<int> &Q) {
		if (i==N) {
			if (First.size() < 5) First.push_back(Q);
			else Last.push_back(Q);
			if (Last.size() == 6) Last.pop_front();
			++Sols;
			return;
		}

		if (Q[i] == 0 || C[Q[i]] > 0) {
			C[Q[i]]++;
			solve(i+1, N, Q);
			C[Q[i]]--;
		}

		if (Q[i] != 25 && C[Q[i]+1] == 0) {
			C[Q[i]+1] = 1;
			Q[i]++;
			solve(i+1, N, Q);
			Q[i]--;
			C[Q[i]+1] = 0;
		}
	}


    void solve(istream& cin, ostream& cout) {
		while (true) {
			string S; cin >> S;
			if (S == "#") return;

			Last.clear();
			First.clear();
			Sols = 0;
			C = vector<int>(26, 0);

			int N = S.size();
			vector<int> Q(N);
			for (int i = 0; i < N; ++i) {
				Q[i] = S[i] - 'a';
			}

			solve(0, N, Q);
			cout << Sols << '\n';
			for (auto&v:First) { for (int vv:v) cout << (char)(vv+'a'); cout << '\n';}
			for (auto&v:Last) { for (int vv:v) cout << (char)(vv+'a'); cout << '\n'; }
		}
    }
};
