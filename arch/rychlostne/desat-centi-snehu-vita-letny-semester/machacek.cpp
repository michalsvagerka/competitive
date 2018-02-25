#include "../../../l/lib.h"
// #include "../l/mod.h"

class machacek {
public:
    vector<int> D; int N; string S;
    unordered_set<pair<pii,pair<string,bool>>> M;
    bool suboptimal, optimal;

    inline bool fails(const string &a, const string &b) const { return a+b < b+a; }

    void dp(int len, int usedMask, string prev, bool subopt) {
        if (usedMask == (1<<N)-1) {
            if (len == S.size()) {
                if (subopt) suboptimal = true;
                else optimal = true;
            }
            return;
        }

        if (M.find({{len,usedMask},{prev,subopt}}) != M.end()) return;
        M.insert({{len,usedMask},{prev,subopt}});

        if (S[len] == '0') return;

        int q = 0, z = 0;
        for (int i = 0; i < 5; ++i) {
            if (len+i == S.size()) break;
            q = q*10 + S[len+i]-'0';
            while (z < N && (D[z] < q || (usedMask&(1<<z)))) ++z;
            if (z == N) break;
            string t = to_string(q);
            dp(len+i+1, usedMask | (1<<z), t, subopt || fails(prev, t));
            if (optimal && suboptimal) return;
        }
    }


    void solve(istream& cin, ostream& cout) {
        int T; cin >> T;
        for (int t = 0; t < T; ++t) {
            M.clear();
            suboptimal = false;
            optimal = false;
            cin >> N;
            D.resize(N); cin >> D;
            sort(D.begin(),D.end());
            cin >> S;
            int l = 0;
            for (int d:D) {
                while (d>0) { d /= 10; ++l; }
            }
            if (S.size() > l) {
                cout << "invalid\n";
                continue;
            }

            dp(0,0,"99999",false);
//            cerr << M.size() << endl;
//            cerr << optimal << ' ' << suboptimal << endl;
            if (!optimal && !suboptimal) {
                cout << "invalid\n";
            } else if (!optimal) {
                cout << "suboptimal\n";
            } else if (!suboptimal) {
                cout << "optimal\n";
            } else {
                cout << "ambiguous\n";
            }
        }
    }
};
