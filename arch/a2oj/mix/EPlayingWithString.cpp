#include "../l/lib.h"
// #include "../l/mod.h"

class EPlayingWithString {
public:
void solve(istream& cin, ostream& cout) {
    string S; cin >> S;
    int N = S.size();
    vector<bool> C(N, false);
    for (int i = 1; i < N-1; ++i) C[i] = S[i-1] == S[i+1];

    vector<int> G(N, 0);
    for (int len = 1; len < N; ++len) {
        set<int> M;
        for (int j = 0; j < len; ++j) {
            int l = max(0, j-1);
            int r = max(0, len-j-2);
            M.insert(G[l] ^ G[r]);
        }
        while (M.find(G[len]) != M.end()) ++G[len];
    }

    vector<pii> R;
    int i = 0, g = 0;
    while (i < N) {
        if (!C[i]) ++i;
        else {
            int j = i;
            while (j < N && C[j]) ++j;
            R.emplace_back(i,j);
            g ^= G[j-i];
            i = j;
        }
    }

    if (g == 0) {
        cout << "Second\n";
    } else {
        cout << "First\n";
        for (pii c: R) {
            int len = c.y-c.x;
            for (int j = 0; j < len; ++j) {
                int l = max(0, j-1);
                int r = max(0, len-j-2);
                if ((G[l] ^ G[r]) == (G[len] ^ g)) {
                    cout << c.x + j + 1 << endl;
                    return;
                }
            }
        }
    }
}
};
