#include "../l/lib.h"
// #include "../l/mod.h"

class waclaw {
public:
    void solve(istream& cin, ostream& cout) {
		string S; cin >> S;
		vector<bool> X(3, false);
		vector<string> Ans;
		for (int i = S.size()-1; i > 0; --i) {
			if (S[i] == '4') {
				for (int j = 1; j <= 3; ++j) {
					stringstream ss; ss << S.substr(0, i) << j;
					Ans.push_back(ss.str());
				}
				break;
			}
			if (X[S[i]-'1']) continue;
			stringstream ss; ss << S.substr(0, i) << 4;
			X[S[i]-'1'] = true;
			Ans.push_back(ss.str());
		}
		sort(Ans.begin(), Ans.end());
		for (string &ans: Ans) cout << ans << '\n';
    }
};
