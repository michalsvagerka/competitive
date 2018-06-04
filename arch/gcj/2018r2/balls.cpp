#include "../../../l/lib.h"
// #include "../l/mod.h"

class balls {
public:
    struct Calc {

        int N;
        vector<int> A;
        bool possible;
        vector<string> C;

        void put(int r, int c, char d) {
            while (C.size() < r+1) C.push_back(string(N,'.'));
            C[r][c] = d;
        }

        void calc() {
            possible = A[0] >= 1 && A[N-1] >= 1;
            if (!possible) return;

            int sum = 0;
            for (int i = 0; i < N; ++i) {
                int left = sum;
                int right = sum + A[i];
                if (left < i) {
                    for (int k = 0; k < i - left; ++k) {
                        put(k, left + k, '\\');
                    }
                }
                if (right > i+1) {
                    for (int k = 0; k < right - i - 1; ++k) {
                        put(k, right - k - 1, '/');
                    }
                }
                sum = right;
            }

        }

        void read(istream& cin) {
            cin >> N;
            A.resize(N);
            cin >> A;
        }

        void write(ostream &cout) {
            if (possible) {
                cout << C.size() + 1 << '\n';
                for (auto &s:C) cout << s << '\n';
                cout << string(N,'.') << '\n';
            } else {
                cout << "IMPOSSIBLE" << '\n';
            }
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
