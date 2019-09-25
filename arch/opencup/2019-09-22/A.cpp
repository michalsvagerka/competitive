#include "../l/lib.h"
#include "../l/mod.h"
#include "../l/matrix.h"
#include "../l/random.h"

class A {
public:
    void solve(istream& cin, ostream& cout) {
        map<int, int> Q;
        random_int R(0, 1000000006);
        for (int i = 0; i < 3; ++i) {
            int j;
            do {
                j = R(rng);
            } while (Q.count(j));
            cout << "ask " << j << endl;
            int k; cin >> k;
            Q[j] = k;
        }
        while (true) {
            int N = Q.size() - 2;
            Matrix<FieldMod> A(N, N, 0);
            vector<FieldMod> B(N, 0);
            int i = 0;
            vector<pii> O;
            for (pii q: Q) {
                if (i >= N) {
                    O.push_back(q);
                } else {
                    B[i] = FieldMod{q.y};
                    FieldMod F = 1;
                    for (int j = 0; j < N; ++j) {
                        A[i][N - 1 - j] = F;
                        F *= q.x;
                    }
                    i++;
                }
            }
            auto C = A.solveFor(B);

//            cout << A << B << C;
            bool ok = true;
            for (pii o: O) {
                FieldMod R = 0;
                for (int j = 0; j < N; ++j) {
                    R *= o.x;
                    R += C[j];
                }

//                cout << o << ' ' << R << endl;
                ok &= R == FieldMod{o.y};
            }

            if (ok) {
                cout << "degree " << N-1 << endl;
//                cout << C;
                return;
            }

            int j;
            do {
                j = R(rng);
            } while (Q.count(j));
            cout << "ask " << j << endl;
            int k; cin >> k;
            Q[j] = k;
        }
    }
};
