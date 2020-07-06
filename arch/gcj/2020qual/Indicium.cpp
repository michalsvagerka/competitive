#include "../l/lib.h"
#include "../l/random.h"
#include "../l/graph.h"
class Indicium {
public:
    vector<vector<int>> find(int N, int K) {

        if (N == 3 && K % 3 != 0) return {};
        if (K == N + 1 || K == N * N - 1) return {};

        random_int ID(0, N-1);
        vector2<int> A(N, N, -1);
        vector2<bool> U(N, N);
        vector<int> ID1(N), ID2(N);
        iota(ID1.begin(),ID1.end(),0);
        iota(ID2.begin(),ID2.end(),0);

        while (true) {
            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < N; ++j) {
                    U[i][j] = true;
                }
            }

            bool fail = false;

            for (int i = 0; i < N; ++i) {
                A[i][i] = 1;
            }
            for (int i = 0; i < K - N; ++i) {
                int j = -1;
                do {
                    j = ID(rng);
                } while (A[j][j] == N);
                A[j][j]++;
            }
            for (int i = 0; i < N; ++i) {
                U[i][A[i][i]-1] = false;
            }

            for (int i = 0; i < N; ++i) {
                shuffle(ID1.begin(), ID1.end(), rng);
                Bipartite B(N, N);

                for (int j = 0; j < N; ++j) {
                    if (i == j) {
                        B.addEdge(ID1[j], N + ID2[A[j][j]-1]);
                    } else {
                        for (int k = 0; k < N; ++k) {
                            if (U[j][k]) {
                                B.addEdge(ID1[j], N + ID2[k]);
                            }
                        }
                    }
                }

                B.calcMatching();
                if (B.matchingSize() != N) {
                    fail = true;
                    break;
                }
                for (int j = 0; j < N; ++j) {
                    if (i == j) continue;
                    for (int k = 0; k < N; ++k) {
                        if (B.matched(ID1[j]) == N + ID2[k]) {
                            A[i][j] = k + 1;
                            U[j][k] = false;
                        }
                    }
                }
            }
            if (fail) continue;

            int k = 0;
            for (int i = 0; i < N; ++i) {
                k += A[i][i];
            }

            int r = 0;
            for (int i = 0; i < N; ++i) {
                vector<bool> S(N, false);
                for (int j = 0; j < N; ++j) {
                    S[A[i][j]-1] = true;
                }
                r += count(S.begin(),S.end(),false) > 0;
            }


            int c = 0;
            for (int i = 0; i < N; ++i) {
                vector<bool> S(N, false);
                for (int j = 0; j < N; ++j) {
                    S[A[j][i]-1] = true;
                }
                c += count(S.begin(),S.end(),false) > 0;
            }
            if (k != K || c != 0 || r != 0) {
                return find(N, K);
            }

            return A;
        }
    }

    void solve(istream& cin, ostream& cout) {
//        vector<vector<vector<vector<int>>>> S(51);
//        for (int N = 2; N <= 50; ++N) {
//            cerr << N << '\n';
//            for (int K = N; K <= N*N; ++K) {
////                cerr << N << ' ' << K << endl;
//                find(N, K);
//            }
//
////            for (int i = N; i <= N*N; ++i) cerr << (!S[N][i].empty());
////            cerr << endl;
//        }
//        return;


        int T; cin >> T;
        for (int t = 0; t < T; ++t) {
            int N, K;
//            if (T == 101) {
//                random_int RN(45,50);
//                N = RN(rng);
//                random_int RK(N*N-20, N*N);
//                K = RK(rng);
//                cerr << N << ' ' << K << endl;
//            } else {
                cin >> N >> K;
//            }
            auto Sol = find(N, K);
            if (Sol.empty()) {
                cout << "Case #" << t+1 << ": IMPOSSIBLE\n";
            } else {
                cout << "Case #" << t+1 << ": POSSIBLE\n";
                for (auto s: Sol) {
                    cout << s;
                }
            }
        }
    }
};
