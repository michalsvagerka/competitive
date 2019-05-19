#include "../l/lib.h"

class pottery {
public:
    void solve(istream& cin, ostream& cout) {
//        int N = 20;
//        int R = 99;
//
//        vector<double> A(100, 0);
//        A[0] = 1.0;
//        for (int i = 0; i < 99; ++i) {
//
//            vector<double> B(100, 0);
//            for (int j = 0; j < 99; ++j) {
//                if (j != 0) B[j] += A[j-1] * 0.05;
//                B[j] += A[j] * 0.95;
//            }
//            swap(A,B);
//        }
//
//        cout << A;
//
        int T; cin >> T;

//        ofstream os;
//        os.open("log",  std::ofstream::out);
        for (int t = 0; t < T; ++t) {
            for (int i = 1; i <= 60; ++i) {
                int d; cin >> d;
                if (d == -1) return;
                cout << 1 + i%15 << ' ' << i << endl;
            }

            vector<vector<int>> E(20);
            vector<int> C(20);
            for (int i = 1; i <= 20; ++i) {
                int d; cin >> d;
                if (d == -1) return;
                cout << i << ' ' << 0 << endl;
                int s; cin >> s;
                E[i-1].resize(s);
                cin >> E[i-1];
            }

            vector<bool> Good(20);
            for (int i = 0; i < 20; ++i) {
                C[i] = E[i].size();
                bool good = true;
                for (int j = 0; j < C[i]; ++j) for (int k = j+1; k < C[i]; ++k) good &= E[i][j] != E[i][k];
                Good[i] = good;
            }

//             << Good << C;
            
            int best = 100;
            int bestI = -1;
            for (int i = 19; i >= 0; --i) {
                if (Good[i] && C[i] < best) {
                    best = C[i];
                    bestI = i;
                }
            }


//            os << bestI+1 << endl;

            int a = 19;
            for (int g = 1; g <= 10; ++g) {
                for (int i = 19; i >= 0; --i) {
                    while (a > 0 && i != bestI && C[i] <= best + g) {
                        int d;
                        cin >> d;
                        if (d == -1) return;
                        cout << i + 1 << ' ' << 100-a << endl;

                        --a;
                        ++C[i];
                    }
                }
            }

            int d; cin >> d;
            if (d == -1) return;
            cout << bestI+1 << ' ' << 100 << endl;
        }

    }
};
