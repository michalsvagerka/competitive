#include "../l/lib.h"
// #include "../l/mod.h"

class enchanted {
public:
	multiset<pair<char,char>> parse(string &s, string &t) {
		int n = s.size();
		multiset<pair<char,char>> r;
		for (int i = 0; i < n; ++i) {
			r.insert({s[i],t[n-1-i]});
		}
		return r;
	}

    void solve(istream& cin, ostream& cout) {
		string S1, S2, T1, T2; cin >> S1 >> S2 >> T1 >> T2;
		auto s = parse(S1,S2), t = parse(T1,T2);
		cout << (s==t ? "Yes" : "No") << endl;
    }
};
