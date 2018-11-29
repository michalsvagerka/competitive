#include "../l/lib.h"
// #include "../l/mod.h"

class DDecrementing {
public:
    map<vector<int>, bool> Mem;



    bool won(const vector<int> &V) {
        auto it = Mem.find(V);
        if (it != Mem.end()) return it->y;

        int N = V.size();

        ll s = 0;
        for (int j : V) s += j;
        int parity = (s-N)%2;
        if (V[0] == 1) return parity;


        vector<int> GPref(N), GSuf(N);
        GPref[0] = V[0];
        GSuf[N-1] = V[N-1];
        for (int i = 1; i < N; ++i) GPref[i] = gcd(GPref[i-1], V[i]);
        for (int i = N-2; i >= 0; --i) GSuf[i] = gcd(GSuf[i+1], V[i]);

        for (int i = 0; i < N; ++i) {
            int g = V[i]-1;
            if (i != 0) g = gcd(g, GPref[i-1]);
            if (i != N-1) g = gcd(g, GSuf[i+1]);
            if (g != 1) {
                vector<int> W = V;
                W[i]--;
                for (int j = 0; j < V.size(); ++j) W[j] /= g;
                if (!won(W)) return Mem[V] = true;
            }
        }
        return Mem[V] = parity;
    }


    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<int> A(N); cin >> A;
        cout << (won(A) ? "First" : "Second") << endl;
//        cout << "Lost\n";
//        for (auto&m:Mem) { if (!m.y) cout << m.x; }
//        cout << "Won\n";
//        for (auto&m:Mem) { if (m.y) cout << m.x; }
    }
};
