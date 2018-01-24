#include "../l/lib.h"
// #include "../l/mod.h"

class digsaw {
public:
    ui N, T;
    int lo, hi;
    vector<ui> C,Z,Y;
    vector<vector<ui>> P,R;
    vector<vector<vector<ui>>> D;

    ui find(ui mask) {
        for (ui i = 0; i < 5; ++i) Y[i] = Z[4-i];
        for (ui i = 0; i < N; ++i) {
            if (mask&(1<<i)) continue;
            if (Z == P[i] || Y == P[i]) return i;
        }
        return N;
    }

    bool canBuild(ui i, ui mask) {
        if (i == N) return true;

        for (int r = 0; r < 5; ++r) Z[r] = R[r][i];
        ui f = find(mask);
        if (f != N && canBuild(i+1, mask|(1<<f))) return true;
        if (i+5 > N) return false;

        for (ui r = 0; r < 5; ++r) {
            for (ui c = 0; c < 5; ++c) Z[c] = R[r][i+c];
            f = find(mask);
            if (f == N) return false;
            mask |= (1<<f);
        }

        return canBuild(i+5, mask);
    }

    bool canBuild(int number) {
        ui t = 0;
        for (ui i = 0; 4*i < N; ++i) {
            for (int c = 0; c < 3; ++c) {
                for (int r = 0; r < 5; ++r) {
                    t += (R[r][N-4*i-3+c] = D[number%10][r][c]);
                }
            }
            number /= 10;
        }
        if (t != T) return false;
        return canBuild(0,0);
    }

    void solve(istream& cin, ostream& cout) {
        cin >> N; T = 0;
        if (N == 3) { lo = 0; hi = 9; }
        else if (N == 7) { lo = 10; hi = 99; }
        else if (N == 11) { lo = 100; hi = 999; }
        else { lo = 1000; hi = 9999; }

        D = {{{1,1,1},{1,0,1},{1,0,1},{1,0,1},{1,1,1}},
             {{0,0,1},{0,0,1},{0,0,1},{0,0,1},{0,0,1}},
             {{1,1,1},{0,0,1},{1,1,1},{1,0,0},{1,1,1}},
             {{1,1,1},{0,0,1},{1,1,1},{0,0,1},{1,1,1}},
             {{1,0,1},{1,0,1},{1,1,1},{0,0,1},{0,0,1}},
             {{1,1,1},{1,0,0},{1,1,1},{0,0,1},{1,1,1}},
             {{1,1,1},{1,0,0},{1,1,1},{1,0,1},{1,1,1}},
             {{1,1,1},{0,0,1},{0,0,1},{0,0,1},{0,0,1}},
             {{1,1,1},{1,0,1},{1,1,1},{1,0,1},{1,1,1}},
             {{1,1,1},{1,0,1},{1,1,1},{0,0,1},{1,1,1}}
        };
        for (ui i = 0; i < 10; ++i) {
            ui x = 0;
            for (auto&d:D[i]) for (auto&dd:d) x += dd;
            C.push_back(x);
        }

        P.resize(N);
        R = vector2<ui>(5,N);
        Z.resize(5); Y.resize(5);

        for (ui i = 0; i < N; ++i) {
            for (ui j = 0; j < 5; ++j) {
                char c;
                cin >> c;
                T += c == 'X';
                P[i].push_back(c == 'X');
            }
        }

        for (int q = hi; q >= lo; --q) {
            if (canBuild(q)) {
                cout << q << endl;
                return;
            }
        }

        cout << -1 << endl;
    }
};
