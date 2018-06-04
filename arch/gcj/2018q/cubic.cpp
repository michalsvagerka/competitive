#include "../../../l/lib.h"
#include "../../../l/geo.h"

class cubic {
public:public:
    struct Calc {
        long double A;
        vector<long double> P,Q,R;

        void calc() {
//            if (A <= 1.414213) {
                R[2] = 0.5;
                long double ang = bshd(0.0, PI/4, [&](long double a) {
                    return sin(a) + cos(a) <= A;
                }, 1e-9);

                P[0] = sin(ang)/2;
                P[1] = cos(ang)/2;
                Q[0] = -cos(ang)/2;
                Q[1] = sin(ang)/2;
//            }
        }

        void read(istream& cin) {
            cin >> A;
            P = Q = R = vector<long double>(3, 0);
        }

        long double dist(vector<long double> A, vector<long double> B) {
            long double s = 0;
            for (int i = 0; i < A.size(); ++i) {
                s += (A[i]-B[i])*(A[i]-B[i]);
            }
            return sqrt(s);
        }

        long double angle(vector<long double> A, vector<long double> B) {
            long double s = 0;
            for (int i = 0; i < A.size(); ++i) {
                s += A[i]*B[i];
            }
            return s;
        }

        long double area() {
            vector<Point<long double>> Z;
            for (int i = -1; i < 2; i+=2) {
                for (int j = -1; j < 2; j+=2) {
                    for (int k = -1; k < 2; k += 2) {
                        Z.push_back({i*P[0]+j*Q[0]+k*R[0],i*P[2]+j*Q[2]+k*R[2]});
                    }
                }
            }
            auto R = convexhull(Z);
//            cerr << R << endl;
            return R.doubleSignedArea() / 2;

        }

        void write(ostream &cout) {

            cout << fixed << setprecision(8) << 2*(abs(P[0])+abs(Q[0])) << endl;

//            cout << area() << endl;
            cout << '\n';
//            cout << fixed << setprecision(15) << P << Q << R;
        }
    };


    void solve(istream& cin, ostream& cout) {
//        Polygon<ll> W;
//        W.push_back({0,0});
//        W.push_back({0,1});
//        W.push_back({1,1});
//        W.push_back({1,0});
//        cout << W.doubleSignedArea() << endl;
        ui T; cin >> T;
        vector<Calc> C(T);
        for (auto &c: C) c.read(cin);
        for (auto &c: C) c.calc();
        for (int t = 0; t < T; ++t) {
            cout << "Case #" << t+1 << ": ";
            C[t].write(cout);
        }
    }
};
