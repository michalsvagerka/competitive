#include "../../../l/lib.h"
#include "../../../l/mod.h"

typedef Field<998244353> FF;

class EBalancedBinarySearchTrees {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        
        for (int i = 2; i <= 21; ++i) {
            vector<int> S(1<<i, 0);
            int M = 1<<i;
            for (int j = M/2-1; j >= 1; --j) {
                S[j] = S[2*j] + S[2*j+1] + 1;
            }
            
            auto add = [&](int x) {
                while (x != 0) {
                    S[x]++;
                    x /= 2;    
                }
            };

            for (int j = M/4-1; j >= 1; --j) {
               //  S[j] = S[2*j] + S[2*j+1] + 1;
                if (S[2*(2*j+1)]%2 == 0) {
                    add(2*j+1);
                }
                if (S[2*(2*j)+1]%2 == 1) {
                    add(2*j);
                }
            }
            
            if (S[1] == N) {
                cout << 1 << endl;
                return;
            }
            
            if (S[1]+1 == N) {
                cout << 1 << endl;
                return;
            }
            
        }
        cout << 0 << endl;
    }
};
