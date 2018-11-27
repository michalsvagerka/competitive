#include "../l/lib.h"
// #include "../l/primes.h"
//#include "../l/random.h"
//#include "../l/runtimemod.h"
#include "../l/suffixarray.h"

class TaskE {
public:
    void solve(istream& cin, ostream& cout) {
        string S, T; cin >> S >> T;
        int N = S.size(), M = T.size();
        int Z = count(S.begin(),S.end(),'0');
        int O = count(S.begin(),S.end(),'1');
        int zero = 0, one = 0;
        while (S[zero] == '1') zero++;
        while (S[one] == '0') one++;

        T += '$';
        SuffixArray<int, true, true> SS(T);

//        int E = 4;
//        LargePrimes LP;
//        vector<RField> A;
//        for (int i = 0; i < E; ++i) {
//            A.push_back(RField{random_int{21,301}(rng), LP[random_int{0,(int)LP.size()-1}(rng)]});
//        }

//        vector2<RField> H(E, M+1, 0), Pow(E, M+1, 1);
//        for (int j = 0; j < M; ++j) {
//            for (int i = 0; i < E; ++i) {
//                H[i][j+1] = H[i][j] * A[i] + T[j];
//                Pow[i][j+1] = Pow[i][j] * A[i];
//            }
//        }

//        cout << H;

        int ans = 0;
        for (int lZ = 1; lZ*Z < M; ++lZ) {
            if ((M - lZ*Z)%O != 0) continue;
            int lO = (M - lZ*Z)/O;
            int fZ = zero * lO, fO = one * lZ;
            int j = 0;
            if ((lO == lZ && SS.lcp(fZ, fO) >= lO)) continue;
            bool ok = true;
            for (char s: S) {
                if (s == '0') {
                    if (fZ != j && SS.lcp(fZ, j) < lZ) {
                        ok = false;
                        break;
                    }
                    else j += lZ;
                } else {
                    if (fO != j && SS.lcp(fO, j) < lO) { ok = false; break; }
                    else j += lO;
                }
            }
            ans += ok;

//            vector<vector<RField>> T(2);
//            int j = 0;
//            for (char s: S) {
//                vector<RField> Q(E, 0);
//                int ll = s=='0'?lZ:lO;
//                for (int l = 0; l < ll; ++l) {
//                    for (int i = 0; i < E; ++i) {
//                        Q[i] = Q[i] * A[i] + T[l + j];
//                    }
//                }
//                if (ZZ.empty()) {
//                    swap(Q, ZZ);
//                } else {
//                    if (ZZ != Q) {
//                        ok = false;
//                        break;
//                    }
//                }
//            }
        }
        cout << ans << '\n';
    }
};
