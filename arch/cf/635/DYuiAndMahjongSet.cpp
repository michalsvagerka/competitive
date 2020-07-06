#include "../l/lib.h"

class DYuiAndMahjongSet {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        bool test = false;
        vector<int> X, O;
        if (N < 0) {
            test = true;
            N = -N;
            X.resize(N);
            cin >> X;
            O = X;
        }

        vector<int> Added(N, 0);
        auto query = [&](int x) {
            if (test) {
                if (x != -1) {
                    Added[x]++;
                    X[x]++;
                }
                int a = 0, b = 0;
                for (int i = 0; i < N; ++i) a += X[i]*(X[i]-1)*(X[i]-2)/6;
                for (int i = 0; i < N-2; ++i) b += X[i]*X[i+1]*X[i+2];
                return pii{a,b};
            } else {
                if (x != -1) {
                    Added[x]++;
                    cout << "+ " << x + 1 << endl;
                }
                int a, b;
                cin >> a >> b;
                return pii{a, b};
            }
        };
        pii a = query(-1);
        int begTriple = a.x;
        vector<int> Cnt(N, -1);
        vector<int> Tria(10000, -1);
        for (int i = 0; i < 105; ++i) {
            Tria[i*(i-1)/2] = i;
        }

        vector<int> Diff(N, -1);
        for (int i = 0; i < N-1; ++i) {
            pii b = query(i);
            Diff[i] = b.y - a.y;
            int diff = b.x - a.x;
            if (diff != 0) Cnt[i] = Tria[diff]-Added[i]+1;
            a = b;
        }


//        cout << begTriple << endl;
        for (int i = 0; i < N-1; ++i) {
            if (Cnt[i] != -1) {
                begTriple -= Cnt[i]*(Cnt[i]-1)*(Cnt[i]-2)/6;
            }
        }

//        cout << begTriple << endl;
        for (int j = 3; j <= 100; ++j) {
            if (j*(j-1)*(j-2)/6 == begTriple) {
                Cnt[N-1] = j;
            }
        }
//        cout << "CNT " << Cnt << endl;


        int maxSize = 1;
        vector<vector<int>> Opts{{}};
        for (int i = 0; i < N; ++i) {
            vector<vector<int>> NewOpts;
            auto check = [&](const vector<int>&O, int add) {
//                cout << "check " << O << ' ' << add << endl;
                if (i >= 2) {
                    // check diff for i-2
                    if (Diff[i-2] != -1) {
                        int exp = 0;
                        if (i >= 4) exp += (O[i - 4] + Added[i - 4]) * (O[i - 3] + Added[i - 3]);
                        if (i >= 3) exp += (O[i - 3] + Added[i - 3]) * (O[i - 1]);
                        exp += O[i - 1] * add;
//                    cout << exp << ' ' << add << ' ' << Diff[i] << endl;
                        if (exp != Diff[i - 2]) return;
                    }
                }

                NewOpts.push_back(O);
                NewOpts.back().push_back(add);
            };
            for (const auto &o: Opts) {
                if (Cnt[i] != -1) check(o, Cnt[i]);
                else {
                    check(o, 0);
                    check(o, 1);
                    if (i == N-1) check(o, 2);
                }
            }
            swap(Opts,NewOpts);
            maxSize = max(maxSize, int(Opts.size()));
//            cout << "Opts " << i << endl;
//            cout << Opts;
        }

        // check last constraint
        vector<vector<int>> NewOpts;
        for (const auto&O: Opts) {
            int exp1 = 0, exp2 = 0;
            exp1 += (O[N-3]+Added[N-3])*(O[N-2]+Added[N-2]);
            exp2 += (O[N-4]+Added[N-4])*(O[N-3]+Added[N-3]);
            exp2 += (O[N-3]+Added[N-3])*(O[N-1]);
            if (Diff[N-1] != -1 && exp1 != Diff[N-1]) continue;
            if (Diff[N-2] != -1 && exp2 != Diff[N-2]) continue;
            NewOpts.push_back(O);
        }

        pii e = query(0);
        Opts.clear();
        for (const auto&O: NewOpts) {
            if (a.x+(O[0]+Added[0]-1)*(O[0]+Added[0]-2)/2 != e.x) continue;
            if (a.y+(O[1]+Added[1])*(O[2]+Added[2]) != e.y) continue;
            Opts.push_back(O);
        }
        swap(Opts, NewOpts);

        auto answer = [&](const vector<int>&answer) {
            if (test) {
                if (NewOpts.size() > 1) {
                    cout << "FAIL TOO MANY OPTS " << NewOpts << '\n';
                }
                if (answer != O) {
                    cout << "FAIL\n" << answer << O;
                } else {
                    cout << "OK\n";
                }
                if (maxSize > 100) {
                    cout << "MAXSIZE" << maxSize << '\n';
                }
            } else {
                cout << "! " << answer << flush;
            }
        };

        answer(NewOpts.back());
    }
};
