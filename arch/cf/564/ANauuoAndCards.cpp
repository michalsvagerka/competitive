#include "../l/lib.h"

class ANauuoAndCards {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<int> A(N), B(N);
        cin >> A >> B;

        int worst = N;
        for (int i = 0; i < N; ++i) {
            if (B[i] != 0) worst = max(worst, N + i - B[i] + 2);
        }
        
        int j = 0;
        while (j < N && B[j] != 1) ++j;
        if (j != N) {
            bool ok = true;
            for (int i = j; i < N; ++i) {
                ok &= (i-j) == B[i]-1; 
            }
            if (ok) {
                int ans = j;
                for (int i = 0; i < j; ++i) {
                    ok &= B[i] == 0 || N + i - B[i] + 2 <= ans;
                }
                if (ok) worst = min(worst, ans);
            }
        }
        
        cout << worst << endl;
    }
};
