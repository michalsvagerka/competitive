#include "../l/lib.h"

constexpr int INF = 2147483647;
constexpr int DEG = 200;

class TwoDistance {
public:
    long long findMinValue(int N, vector <int> edge, vector <int> val, int D, int seed) {
        vector<ll> A(2*N);
        A[0] = seed;
        for (int i = 1; i < 2*N; ++i)
            A[i] = (A[i-1] * 1103515245LL + 12345LL) % 2147483648LL;

        vector<int> V = val;
        for (int i = val.size(); i < N; ++i) V.push_back(A[i]);

        vector<int> E = edge;
        for (int i = edge.size(); i < N; ++i) {
            E.push_back(A[N + i] % min(i, D));
        }

        vector<vector<int>> F(N);
        for (int i = 1; i < N; ++i) {
            F[E[i]].push_back(i);
            F[i].push_back(E[i]);
        }

        vector<int> Ans(N, INF);
        for (int u = 0; u < N; ++u) {
            vector<pii> X;
            for (int j: F[u]) X.push_back({V[j], j});
            sort(X.begin(),X.end());
            int M = X.size();
            vector<int> Left(M+1, INF), Right(M+1, INF);
            for (int i = 1; i < M; ++i) {
                Left[i+1] = Left[i];
                if (X[i].x != X[i-1].x) {
                    Left[i+1] = min(Left[i+1], X[i].x - X[i-1].x - 1);
                }
            }
            for (int i = M-2; i >= 0; --i) {
                Right[i] = Right[i+1];
                if (X[i].x != X[i+1].x) {
                    Right[i] = min(Right[i], X[i+1].x - X[i].x - 1);
                }
            }

            for (int i = 0; i < M; ++i) {
                int j = X[i].y;
                Ans[j] = min(Ans[j], Left[i]);
                Ans[j] = min(Ans[j], Right[i+1]);
                if (i != 0 && i != M-1) {
                    int a = X[i-1].x;
                    int b = X[i+1].x;
                    if (a != b) {
                        Ans[j] = min(Ans[j], b - a - 1);
                    }
                }
            }
        }

        vector<multiset<int>> W(N);
        for (int i = 0; i < N; ++i) {
            for (int j : F[i]) {
                W[i].insert(V[j]);
            }
        }

        for (int i = 0; i < N; ++i) {
            if (F[i].size() >= DEG) {
                vector<int> S;
                for (int j : F[i]) {
                    for (int k : F[j]) {
                        if (i != k) S.push_back(V[k]);
                    }
                }
                sort(S.begin(),S.end());
                int M = S.size();
                for (int j = 0; j < M-1; ++j) {
                    if (S[j] != S[j+1]) Ans[i] = min(Ans[i], S[j+1]-S[j] - 1);
                }
            } else {
                for (int j : F[i]) {
                    multiset<int> *C = &W[j];
                    C->erase(C->find(V[i]));
                    for (int k : F[i]) {
                        if (j < k) {
                            multiset<int> *D = &W[k];
                            D->erase(D->find(V[i]));

                            multiset<int> *E = C, *F = D;
                            if (E->size() < F->size()) swap(E,F);
                            for (int x: *D) {
                                auto a = E->lower_bound(x);
                                auto b = E->upper_bound(x);
                                if (a != E->begin()) Ans[i] = min(Ans[i], x-*prev(a)-1);
                                if (b != E->end()) Ans[i] = min(Ans[i], *b-x-1);
                            }
                            
                            D->insert(V[i]);
                        }
                    }
                    C->insert(V[i]);
                }
            }
        }
        cerr << "done" << endl;

        ll tot = 0;
        for (int i = 0; i < N; ++i) {
            if (Ans[i] != INF) tot += Ans[i]+1;
        }

        return tot;
    }
    void solve(istream& cin, ostream& cout) {
        cout << findMinValue(3,{-1, 0, 1},{},3,2) << '\n';
        cout << findMinValue(5,{-1},{1, 2, 3, 4, 5},3,4) << '\n';
        cout << findMinValue(8,{-1},{},7,670614018) << '\n';
        for (int j = 1; j < 20; ++j) {

            cout << findMinValue(200000,{-1},{},j,589477399) << '\n';
        }
        cout << findMinValue(200000,{-1},{},2,589477399) << '\n';
        cout << findMinValue(200000,{-1},{},10,589477399) << '\n';
        cout << findMinValue(200000,{-1},{},20,589477399) << '\n';
        cout << findMinValue(200000,{-1},{},50,589477399) << '\n';
        cout << findMinValue(200000,{-1},{},84,589477399) << '\n';
        cout << findMinValue(200000,{-1},{},100,589477399) << '\n';
        cout << findMinValue(200000,{-1},{},200,589477399) << '\n';
        cout << findMinValue(200000,{-1},{},500,589477399) << '\n';
        cout << findMinValue(200000,{-1},{},400,589477399) << '\n';
        cout << findMinValue(200000,{-1},{},800,589477399) << '\n';
        cout << findMinValue(200000,{-1},{},1500,589477399) << '\n';
        cout << findMinValue(200000,{-1},{},3000,589477399) << '\n';
        cout << findMinValue(200000,{-1},{},5000,589477399) << '\n';
        cout << findMinValue(200000,{-1},{},10000,589477399) << '\n';
        cout << findMinValue(200000,{-1},{},20000,589477399) << '\n';
        cout << findMinValue(200000,{-1},{},50000,589477399) << '\n';
        cout << findMinValue(200000,{-1},{},100000,589477399) << '\n';
    }
};
