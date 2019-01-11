#include "../l/lib.h"
 #include "../l/primes.h"

constexpr int G = 7001;
class FAlexAndATVShow {
public:
    void solve(istream& cin, ostream& cout) {
//        vector<bool> S(G, true);
//        for (int i = 2; i <= G; ++i) {
//            if (S[i]) {
//                for (int j = 2*i; j <= G; ++j) S[j] = false;
//            }
//        }
        

        Moebius M{G};
        vector<bool> S(G+1, false);
        for (pii m: M) {
            if (m.x <= G) {
                S[m.x] = true;
            }
        }
        
        
        vector<bitset<G>> LO(G), HI(G);
        for (int i = 1; i < G; ++i) {
            for (int j = 1; j < G; ++j) {
                if (i%j==0) {
                    LO[i][j] = true;
                    if (S[i/j]) HI[j][i] = true;
                }
            }
        }

        int N, Q; cin >> N >> Q;
        vector<bitset<G>> R(N);
        for (int q = 0; q < Q; ++q) {
            int t, x;
            cin >> t >> x;
            --x;
            if (t == 1) {
                int v; cin >> v;
                R[x] = LO[v];
            } else if (t == 2) {
                int y, z; cin >> y >> z;
                --y; --z;
                auto s = R[y] ^ R[z];
                R[x] = s;
            } else if (t == 3) {
                int y, z; cin >> y >> z;
                --y; --z;
                auto s = R[y] & R[z];
                R[x] = s;
            } else {
                int v; cin >> v;
                cout << ((R[x] & HI[v]).count()%2);
            }
        }
        cout << endl;
    }
};
