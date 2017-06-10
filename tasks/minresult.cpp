#include "../l/lib.h"
// #include "../l/mod.h"

class minresult {
public:
	ll solve(vector<ll> &V, vector<char> &W, int I) {
		if (I == 3) { return V[0]; }
		ll ans = std::numeric_limits<ll>::max();
		for (int i = 0; i < V.size()-1; ++i) {
			for (int j = i+1; j < V.size(); ++j) {
				vector<ll> Q;
				for (int k = 0; k < V.size(); ++k) {
					if (k != j && k != i) Q.push_back(V[k]);
 				}
				switch (W[I]) {
					case '+':
						Q.push_back(V[i]+V[j]);
						break;
					case '*':
						Q.push_back(V[i]*V[j]);
						break;
				}
				ans = min(ans, solve(Q, W, I+1));
			}
		}
		return ans;
	}

    void solve(istream& cin, ostream& cout) {
		vector<ll> V(4);
		vector<char> W(3);
		cin >> V >> W;
		cout << solve(V, W, 0) << endl;
    }
};
