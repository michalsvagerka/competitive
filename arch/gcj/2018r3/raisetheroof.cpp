#include "../../../l/lib.h"
 #include "../../../l/matrix.h"
#include "../../../l/frac.h"
#include "../../../l/random.h"

typedef long double T;

class raisetheroof {
public:
struct Calc {
    int N;
    vector<pair<pair<int,ll>,pair<ll,ll>>> E;
    vector<int> A;
    vector<bool> U;

    bool test(int i) {
        if (i == N) return true;

        vector<int> Z;
        for (int i = 0; i < N; ++i) if (!U[i]) Z.push_back(i);
        random_int R(0, int(Z.size())-1);

        int att = 0;
        do {
            int r = R(rng);
            int k = Z[r];

            bool ok = true;
            if (i > 3) {
                Matrix<T> M(3, 3);
                vector<T> F(3);
                vector<int> Z{A[i - 2], A[i - 1], k};
                for (int j = 0; j < 3; ++j) {
                    M[j][0] = E[Z[j]].x.y;
                    M[j][1] = E[Z[j]].y.x;
                    M[j][2] = 1;
                    F[j] = E[Z[j]].y.y;
                }

                auto S = M.solveFor(F);

                T a = S[0];
                T b = S[1];
                T d = S[2];
                T c = -1;
                for (int l = 0; l <= i - 3 && ok; ++l) {
                    if (a * E[A[l]].x.y + b * E[A[l]].y.x + c * E[A[l]].y.y + d < 0) {
                        ok = false;
                    }
                }
            }
            if (ok) {
                U[k] = true;
                A[i] = k;
                if (test(i+1)) {
                    return true;
                }
                U[k] = false;
            }
            if (att++ > 5) return false;
        } while (true);
    }


    void calc() {
        U = vector<bool>(N, false);
        A = vector<int>(N, -1);
        bool t = test(0);
        cerr << t << endl;
        for (int &a:A) a++;
    }

    void read(istream& cin) {
        cin >> N;
        E.resize(N);
        for (int i = 0; i < N; ++i) {
            E[i].x.x = i+1;
            cin >> E[i].x.y >> E[i].y;
        }
    }

    void write(ostream &cout) {
        cout << A;
    }
};


void solve(istream& cin, ostream& cout) {
    ui T; cin >> T;
    for (int t = 1; t <= T; ++t) {
        Calc c;
        c.read(cin);
        c.calc();
        cout << "Case #" << t << ": ";
        c.write(cout);
    }
}
};
