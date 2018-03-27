#include <numeric>
#include "../../../l/lib.h"
#include "../../../l/mod.h"

class F {
public:
    void solve(istream& cin, ostream& cout) {
        auto F = FieldMod::fact(65536);

        int N, M; cin >> N >> M;
        vector<int> Q(M); cin >> Q;
        vector<bool> Z(1+(1<<N), false);
        for (int q:Q) Z[q] = true;

        if (Z[2]) {
            cout << 0 << endl;
            return;
        }
//
//        if (N == 16) {
//            return;
//        }


        vector<FieldMod> S(1<<N, 0);
        for (int i = 0; i < N; ++i) {
            S[1<<i] = 1;
        }

        for (int j = 3; j <= (1<<N); ++j) {
            vector<FieldMod> R(1<<N, 0);
            for (int i = 0; i < (1<<N); ++i) {
                if (!Z[j]) {
                    for (int k = 0; k < N; ++k) {
                        if ((i & (1 << k)) == 0) {
                            R[i | (1 << k)] += S[i];
                        }
                    }
                }

                R[i] += S[i] * (2 + i - j);
            }
            swap(R,S);
        }

        cout << S[(1<<N)-1] * FieldMod{2}.pow(N*(N+1)/2) << endl;


//        if (N == 3) {
//            int cnt = 0;
//            vector<int> A(1<<N);
//            iota(A.begin(),A.end(),1);
//            do {
//                vector<int> B = A;
//                while (B.size() > 1) {
//                    vector<int> C(B.size()/2);
//                    for (int i = 0; i < B.size()/2; i++) {
//                        if (B[2*i] == 1 || B[2*i+1] == 1) {
//                            int other = B[2*i+(B[2*i]==1)];
//                            if (Z[other]) C[i] = other; else C[i] = 1;
//                        } else {
//                            C[i] = min(B[2*i], B[2*i+1]);
//                        }
//                    }
//                    swap(B,C);
//                }
//                if (B[0] == 1) {
//                    cnt++;
//                    //cout << A;
//                }
//            } while (next_permutation(A.begin(),A.end()));
//            cout << cnt << endl;
//        }
    }
};
