#include "../l/lib.h"
#include "../l/graph.h"

class DSortingAGrid {
public:
    void solve(istream& cin, ostream& cout) {
        int N, M; cin >> N >> M;
        vector2<int> A(N, M); cin >> A;
        vector2<int> B(N, M, -1), C(N, M, -1);
        for (int i = 0; i < M; ++i) {
            Bipartite G(N, N);
            for (int j = 0; j < N; ++j) {
                for (int k = 0; k < M; ++k) {
                    if (A[j][k] != 0) {
                        int a = (A[j][k] - 1)/M;
                        G.addEdge(j, a+N);
                    }
                }
            }
            
            G.calcMatching();
            for (int j = 0; j < N; ++j) {
                int b = G.matched(j) - N;
                int lo = b*M + 1;
                int hi = b*M + M;
                for (int k = 0; k < M; ++k) {
                    if (A[j][k] >= lo && A[j][k] <= hi) {
                        B[j][i] = A[j][k];
                        A[j][k] = 0;
                        break;
                    }
                }
            }
        }
        
//        for (int i = 0; i < N; ++i) {
//            int lo = i*M + 1;
//            int hi = i*M + M;
//            Bipartite G(M, M);
//            for (int j = 0; j < N; ++j) {
//                for (int k = 0; k < M; ++k) {
//                    if (A[j][k] >= lo && A[j][k] <= hi) {
//                        for (int l = 0; l < M; ++l) {
//                            if (B[j][l] == -1) {
//                                G.addEdge(A[j][k] - lo, M + l);
//                            }
//                        }
//                    }
//                }
//            }
//            G.calcMatching();
//            cerr << "MATCH " << G.matchingSize() << endl;
////            for (int i = 0; i < M; ++i) cout << ' ' << G.matched(i) - M;
////            cout << endl;
//
//            for (int j = 0; j < N; ++j) {
//                for (int k = 0; k < M; ++k) {
//                    if (A[j][k] >= lo && A[j][k] <= hi) {
//                        int a = A[j][k] - lo;
//                        int b = G.matched(a) - M;
//                        assert(b >= 0 && b < M);
//                        B[j][b] = A[j][k];
//                    }
//                }
//            }
//            for (auto &b: B) cerr << b;
//        }

        for (int i = 0; i < M; ++i) {
            vector<int> S(N);
            for (int j = 0; j < N; ++j) {
                S[j] = B[j][i];
            }
            sort(S.begin(),S.end());
            for (int j = 0; j < N; ++j) {
                C[j][i] = S[j];
            }
        }

        for (auto &b: B) cout << b;
        for (auto &c: C) cout << c;
    }
};
