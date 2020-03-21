#include "../l/lib.h"

class AOstapAndGrasshopper {
public:
    void solve(istream& cin, ostream& cout) {
        int N, K; cin >> N >> K;
        string S; cin >> S;
        int a = S.find('G');
        int b = S.find('T');
        if (a>b) swap(a,b);

        if ((b-a)%K != 0) {
            cout << "NO\n";
            return;
        }

        for (int i = a + K; i < b; i += K) {
            if (S[i] == '#') {
                cout << "NO\n";
                return;
            }
        }
        cout << "YES\n";
    }
};
