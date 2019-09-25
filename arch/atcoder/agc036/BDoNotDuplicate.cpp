#include "../l/lib.h"

class BDoNotDuplicate {
public:
    void solve(istream& cin, ostream& cout) {
        int N; ll K;
        cin >> N >> K;
        vector<int> A(N); cin >> A;
        for (int&a: A) --a;
        vector<int> Next(200000, N), Edge(N, 2*N);
        for (int i = N-1; i >= 0; --i) {
            Next[A[i]] = N + i;
        }
        for (int i = N-1; i >= 0; --i) {
            Edge[i] = Next[A[i]];
            Next[A[i]] = i;
        }

        int period = 1;
        int j = -1;
        do {
            j++;
            j = Edge[j];
            if (j >= N) {
                j -= N;
                period++;
            }
        } while (j != N-1);

        --K;
        K %= period;

        j = -1;
        while (true) {
            j++;
            if (j == N) {
                j = 0;
                if (K == 0) {
                    break;
                } else {
                    --K;
                }
            }
            if (K == 0 && Edge[j] >= N) {
                break;
            } else {
                j = Edge[j];
                if (j >= N) {
                    j -= N;
                    K--;
                }
            }
        }

        vector<bool> U(200000, false);
        vector<int> Ans;
        for (int i = j; i < N; ++i) {
            if (U[A[i]]) {
                while (Ans.back() != A[i]) {
                    U[Ans.back()] = false;
                    Ans.pop_back();
                }

                U[A[i]] = false;
                Ans.pop_back();
            } else {
                U[A[i]] = true;
                Ans.push_back(A[i]);
            }
        }

        for (int&a: Ans) ++a;
        cout << Ans;
//        cout << period << endl;
    }
};
