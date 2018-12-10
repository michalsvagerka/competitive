#include "../l/lib.h"
// #include "../l/mod.h"

class P9 {
public:
    
    int root(int s) {
        if (s < 10) return s;
        int x = 0;
        while (s) {
            x += s%10;
            s /= 10;
        }
        return root(x);
    }
    
    bool has(int x, int t) {
        if (x%10 == t) return true;
        if (x == 0) return false;
        return has(x/10, t);
    }
    
void solve(istream& cin, ostream& cout) {
    int N = 1e7;
    vector<bool> S(N+1, true);
    int X = 3, Y = 3;
    vector<bool> W(10, false);
    while (X) {
        int z = 0;
        for (int i = X; i <= N; i += X) {
            z += S[i];
            S[i] = false;
        }
        if (!W[Y]) {
            W[Y] = true;
            for (int i = 1; i <= N; ++i) {
                if (S[i] && has(i, Y)) {
                    S[i] = false;
                    z++;
                }
            }
        }
        
        X = z;
        Y = root(z);
        
        cout << z << ' ' << root(z) << endl;
    }

    cout << count(S.begin()+1,S.end(),true) << endl;
}
};
