#include "../l/lib.h"
// #include "../l/mod.h"

class P8 {
public:
    struct Los {
        string first, last;
        vector<int> Q;
    };

    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<int> O(N);
        for (int j = 0; j < N; ++j) {
            string s; cin >> s;
            if (s[0] == 'b') O[j] = 0;
            else if (s[0] == 'o') O[j] = 1;
            else if (s[0] == 't') O[j] = 2;
            else {cout << "FAIL\n"; }
        }

        int M; cin >> M;
        vector<Los> L(M);
        for (int i = 0; i < M; ++i) {
            L[i].Q.resize(3);
            cin >> L[i].first >> L[i].last >> L[i].Q;
        }

        for (int i = 0; i < N; ++i) {
            stable_sort(L.begin(),L.end()-i,[&](const Los&a, const Los&b) { return a.Q[O[i]] < b.Q[O[i]]; });
            cout << L[N-i-1].first << endl;
            
        }
    }
};
