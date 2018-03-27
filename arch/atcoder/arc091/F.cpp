#include "../../../l/lib.h"
// #include "../l/mod.h"

class F {
public:
    map<pii, int> G;

    int fastgrundy(int a, int k) {
        //cerr << "fg " << a << ' ' << k << endl;
        if (a < k) return 0;
        if (a % k == 0) return a/k;
        // if (a == k + 1) return 0;

        else {
            int sub = a/k + 1;
            int cnt = max(1, (a%k)/sub);
            return fastgrundy(a - cnt*sub, k);
        }
    }

    int grundy(int a, int k) {
        if (a < k) return 0;
        // if (a % k == 0) return a/k;
        // if (a == k + 1) return 0;
        auto it = G.find({a,k});
        if (it != G.end()) return it->y;

        set<int> gr;
        for (int i = 1; i <= a/k; ++i) {
            gr.insert(grundy(a-i, k));
        }

        int z = 0;
        while (gr.find(z) != gr.end()) z++;
        return G[{a,k}] = z;
    }


    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        int g = 0;
        for (int i = 0; i < N; ++i) {
            int a,k; cin >> a >> k;
//            grundy(100, k);
            g ^= fastgrundy(a,k);
//            int z = 0, w = 0;
//            for (auto&g:G) {
//                cout << g.x.x << ':' << g.y << ':' << fastgrundy(g.x.x, g.x.y) << ' ';
//                if (++z % g.x.y != 1) {
//                    if (++w % g.x.y != 2 && w != 1) {
//                        cout << g.x.x << ':' << g.y << ' ';
//                    }
//                }
//            }
//            cout << endl;
//            G.clear();
        }
        if (g == 0) {
            cout << "Aoki\n";
        } else {
            cout << "Takahashi\n";
        }
    }
};
