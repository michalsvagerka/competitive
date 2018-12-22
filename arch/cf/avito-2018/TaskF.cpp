#include "../l/lib.h"
 #include "../l/random.h"

class TaskF {
public:
    int N, T;
    vector<int> Y, Z;

    void gen() {
        random_int R(0, 1);
        int t = 0;
        Y.resize(N);
        for (int i = 0; i < N; ++i) {
            if (t == T) Y[i] = 0;
            else if (t + (N-i) == T) t += Y[i] = 1;
            else t += Y[i] = R(rng);
        }
        Z = Y;
    }

    int ask(istream &cin, ostream&cout, int l, int r) {
        cout << "? " << l << ' ' << r << endl;
        int f; cin >> f; return f;
//        random_int R(0, 1);
//        if (R(rng) == 0) {
//            for (int i = 0; i < r; ++i) {
//                Y[i] = 1-Y[i];
//            }
//        } else {
//            for (int i = l-1; i < N; ++i) {
//                Y[i] = 1-Y[i];
//            }
//        }
//
//        return count(Y.begin(),Y.end(),1);
    }

    void answer(ostream&cout, vector<int> X) {
        cout << "! ";
        for (int x:X) cout << x;
        cout << endl; flush(cout);
//        cout << X;
//        cout << Z;
//        cout << (X==Z) << endl;

    }


    void solve(istream& cin, ostream& cout) {
        cin >> N >> T;
//        gen();
//        cout << Y;

        vector<int> X(N);
        int f, t = T, p = 0;
        int s = 0;
        for (int i = 0; i < N-1; ++i) {
            bool known = false;
            for (int j = 0; j < 15; ++j) {
                ask(cin, cout, i+2, N);
                f = ask(cin, cout, i+2, N);
                if (f != t) {
                    known = true;
                    if ((t - p) + (i - p) + 1 == f) {
                        X[i] = 0;
                    } else {
                        X[i] = 1;
                        p++;
                    }

                    // don't forget we swapped all
                    p = (i+1)-p;
                    t = f;
                    break;
                }
            }

            if (!known) {
                // it is apparently balanced
                X[i] = p==i/2;

                // we don't know what we did to it, but who the hell cares
                p = (i+1)/2;
            }

//            cout << "p is " << p << endl;
            s += X[i];
        }

        X[N-1] = T - s;
        answer(cout, X);
    }
};
