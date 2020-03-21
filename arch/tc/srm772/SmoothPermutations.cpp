#include "../l/lib.h"
#include "../l/runtimemod.h"
#include "../l/segtree.h"

class SmoothPermutations {
public:
    long long countPermutations(int T, int M, int MX, int seed, vector <int> prefN, vector <int> prefK, vector <int> prefX) {
        vector<int> A(3*T);
        A[0] = seed;
        for (int i = 1; i < 3*T; ++i) {
            A[i] = (A[i-1] * 1103515245LL + 12345) % 2147483648LL;
        }

        vector<int> N(T), K(T), X(T);
        int LEN = prefN.size();
        for (int i = 0; i < LEN; ++i) {
            N[i] = prefN[i];
            K[i] = prefK[i];
            X[i] = prefX[i];
        }

        for (int i = LEN; i < T; ++i) {
            N[i] = (A[i] % MX) + 1;
            K[i] = (A[T+i] % N[i]) + 1;
            X[i] = (A[2*T+i] % N[i]) + 1;
        }

        MOD = M;
        auto F = RField::fact(MX+1);

        vector<RField> W(MX+1);
        for (int i = 0; i <= MX ; ++i) W[i] = RField{i};
        SetMulTree<RField> ST;
        ST.setup(W, RField{0});

        ll tot = 0;
        for (int i = 0; i < T; ++i) {
            if (K[i] > X[i]) continue;
            RField ans = ST.get(X[i]-K[i]+1, X[i]) * F[N[i]-K[i]];
            tot += (int)ans;
        }
        
        return tot;
    }

    void solve(istream& cin, ostream& cout) {
        cout << countPermutations(3,100,5,4,{5,4},{3,2},{5,2}) << endl;
        cout << countPermutations(100,1,47,47,{},{},{}) << endl;
        cout << countPermutations(100,999999937,123456,47,{},{},{}) << endl;
    }
};
