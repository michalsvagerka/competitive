#include "../../../l/lib.h"
// #include "../l/mod.h"

class liegesoflegendre {
public:

    int odd(int g) {
        return (g < 5)?g-2*(g>1):(g % 2 == 1)?0:1+(odd(g/2)==1);
    }

    int even(int g) {
        return (g < 3)?g:(g%2==0);
    }

    void solve(istream& cin, ostream& cout) {
        vector<int> G(100), H(G.size());
        G[0] = H[0] = 0;
        for (int i = 1; i < G.size(); ++i) {
            int g1 = G[i-1];
            int g2 = i%2==0 ? G[i/2] : -1;
            if (g1 != 0 && g2 != 0) {
                G[i] = 0;
            } else if (g1 != 1 && g2 != 1) {
                G[i] = 1;
            } else {
                G[i] = 2;
            }

            int g3 = H[i-1];
            int g4 = i%2==0 ? 0 : -1;
            if (g3 != 0 && g4 != 0) {
                H[i] = 0;
            } else if (g3 != 1 && g4 != 1) {
                H[i] = 1;
            } else {
                H[i] = 2;
            }
        }

        int N, K; cin >> N >> K;
        int g = 0;
        for (int i = 0; i < N; ++i) {
            int a; cin >> a;
            g ^= K % 2 ? odd(a) : even(a);
        }

        cout << (g ? "Kevin" : "Nicky") << endl;
    }
};
