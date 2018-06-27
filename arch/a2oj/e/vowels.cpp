#include "../../../l/lib.h"
// #include "../l/mod.h"

class vowels {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;

        vector<int> D(1<<24, 0);
        for (int i = 0; i < N; ++i) {
            string S; cin >> S;
            int u = 0;
            for (char c:S) u |= (1<<(c-'a'));
            u ^= (1<<24) - 1;
            D[u]++;
        }

        for (int i = 0; i < 24; ++i) {
            for (int j = 0; j < (1<<24); ++j) {
                if (j&(1<<i)) D[j^(1<<i)] += D[j];
            }
        }
        
        int ans = 0;
        for (int i = 0; i < (1<<24); ++i) {
            ans ^= (N-D[i])*(N-D[i]);
        }

        cout << ans << endl;
    }
};
