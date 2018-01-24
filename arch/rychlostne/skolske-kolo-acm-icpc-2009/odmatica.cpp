#include "../l/lib.h"
#include "../l/matrix.h"

const double pi = std::acos(-1);

class odmatica {
public:
    Matrix<double> rot2(int parts) {
        double x = sqrt(3);
        if (parts == 4) return {{1./x,-2./x},{2./x,-1./x}};
        double angle = (2 * pi) / parts;
        return {{cos(angle), -sin(angle)}, {sin(angle),cos(angle)}};
    }


    Matrix<double> rot3(int parts) {
        double angle = (2 * pi) / parts;

        bool z = parts!=3;
        double c = cos(angle), uuo = (1-c)/(2+z), us = sin(angle)/sqrt(2+z);
        return {{z*uuo + c,  z*uuo - us, z*uuo + us},
                {z*uuo + us, uuo + c,  uuo - z*us},
                {z*uuo - us, uuo + z*us, c + uuo}};
    }

    void solve(istream& cin, ostream& cout) {
        int N, K; cin >> N >> K;
        auto m2 = rot2(K), m3 = rot3(K);
        Matrix<double> res(N,N);
        for (int r = 0; r+1 < N; r+=2) {
            for (int i = 0; i < 2; ++i) {
                for (int j = 0; j < 2; ++j) {
                    res[r+i][r+j] = m2[i][j];
                }
            }
        }
        if (N&1) {
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    res[N-3+i][N-3+j] = m3[i][j];
                }
            }
        }

        cout << fixed << setprecision(10);

        if (true) {
            int *p = 0;
            for (int r = 0; r < N; ++r) {
                for (int c = 0; c < N; ++c) {
                    if (abs(res[r][c] - 1) < 1e-6) {
                        cout << "Failbase " << r << ' ' << c << endl;
                        *p = 0;
                    }
                }
            }

            auto tst = res;
            for (int i = 2; i < K; ++i) {
                tst = tst*res;
                bool fail = true;
                for (int r = 0; r < N; ++r) {
                    for (int c = 0; c < N; ++c) {
                        fail &= (abs(tst[r][c] - (r==c)) < 1e-6);
                    }
                }
                if (fail) {
                    cout << "Failpow " << i << endl << tst << endl;
                    *p = 0;
                }
            }
            tst = tst*res;
            for (int r = 0; r < N; ++r) {
                for (int c = 0; c < N; ++c) {
                    if (abs(tst[r][c] - (r == c)) > 1e-8) {
                        cout << "Failres " << r << ' ' << c << endl;
                        *p = 0;
                    }
                }
            }
        }


        cout << res;
    }
};
