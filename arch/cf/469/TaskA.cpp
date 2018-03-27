#include "../../../l/lib.h"
// #include "../l/mod.h"

class TaskA {
public:
    void solve(istream& cin, ostream& cout) {
        string S; cin >> S;
        vector<vector<int>> Q;
        vector<int> Good, Bad;
        for (int i = 0; i < S.size(); ++i) {
            char s = S[i];
            bool good = s - '0';
            if (good) {
                if (Good.empty()) {
                    cout << "-1\n";
                    return;
                } else {
                    int g = Good.back();
                    Good.pop_back();
                    Q[g].push_back(i+1);
                    Bad.push_back(g);
                }
            } else if (Bad.empty()) {
                Good.push_back(Q.size());
                Q.push_back({i+1});
            } else {
                int b = Bad.back();
                Bad.pop_back();
                Q[b].push_back(i+1);
                Good.push_back(b);
            }
        }

        if (!Bad.empty()) {
            cout << "-1\n";
            return;
        }

        cout << Q.size() << endl;
        for (auto &q:Q) {
            cout << q.size() << ' ' << q;
        }
    }
};
