#include "../l/lib.h"
// #include "../l/mod.h"

class TaskC {
public:

    vector<pair<int,pii>> Mem;

    int brute(int N, int c) {
        if (c == 0) return 0;
        if (Mem[c].x != -1) return Mem[c].x;
        Mem[c] = {10000, {0,0}};
        for (int x = 0; x < N; ++x) {
            for (int y = x+1; y < N; ++y) {
                int z = y + y - x;
                if (z < N) {
                    int d = c^(1<<x)^(1<<y)^(1<<z);
                    Mem[c] = min(Mem[c], {brute(N, d)+1, {x,y-x}});
                }
            }
        }
        return Mem[c].x;
    }

    int solve(int N, int c) {
        Mem.assign(1<<N, {-1,{-1,-1}});
        return brute(N, c);
    }

void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<int> A(N);
        cin >> A;
        int i = 0;
        vector<pair<pii,int>> S;
        auto add = [&](int a, int b, int c) {
            A[a] ^= 1;
            A[b] ^= 1;
            A[c] ^= 1;
            S.push_back({{a,b},c});
        };
        while (N - i >= 12) {
            if (A[i] == 0) ++i;
            else if (A[i+1] == 0 && A[i+2] == 0) {
                add(i, i+3, i+6);
                i += 3;
            } else if (A[i+1] == 1 && A[i+2] == 1) {
                add(i, i+1, i+2);
                i += 3;
            } else if (A[i+1] == 0 && A[i+2] == 1) {
                add(i, i+2, i+4);
                i += 3;
            } else {
                vector<int> Z(20);
                bool found = false;
                for (int d = 2; d <= 5 && !found; ++d) {
                    for (int e = 1; e <= 5 && !found; ++e) {
                        for (int j = 0; j < 6; ++j) Z[j] = A[i+j];
                        Z[0] ^= 1;
                        Z[1] ^= 1;
                        Z[d] ^= 1;
                        Z[1+e] ^= 1;
                        Z[d+d] ^= 1;
                        Z[1+e+e] ^= 1;
                        bool ok = true;
                        for (int j = 0; j < 6; ++j) ok &= Z[j] == 0;
                        if (ok) {
                            found = true;
                            add(i, i+d, i+d+d);
                            add(i+1, i+e+1, i+e+e+1);
                        }
                    }
                }

//                for (int j = 0; j < 6; ++j) {
//                    if (A[j] == 1) {
//                        cout << "Fail " << j << endl;
//                    }
//                }
//
//                if (!found) {
//                    cout << "Error\n";
//                    return;
//                }
                assert(found);
                i += 6;
            }
        }

        int g = min(12, N);
        int h = 0;
        for (int i = 0; i < g; ++i) {
            h ^= (A[N-1-i]<<i);
        }

        if (solve(g, h) != 10000) {
            while (h != 0) {
                int i = Mem[h].y.x;
                int d = Mem[h].y.y;
                add(N-1-i-d-d, N-1-i-d, N-1-i);
                h ^= (1<<i);
                h ^= (1<<(i+d));
                h ^= (1<<(i+d+d));
            }

            cout << "YES\n";
            cout << S.size() << endl;
            for (auto s: S) {
                cout << (s.x.x+1) << ' ' << (s.x.y+1) << ' ' << (s.y+1) << '\n';
            }
        } else {
            cout << "NO\n";
        }





//    for (int j = 3; j <= 12; ++j) {
//        map<int,int> Q;
//        for (int k = 0; k < (1<<j); ++k) {
//            Q[solve(j, k)]++;
//        }
//
//        cerr << j << endl;
//        for (pii q:Q) {
//            cerr << q << ' ';
//        }
//        cerr << endl;
//    }
}
};
