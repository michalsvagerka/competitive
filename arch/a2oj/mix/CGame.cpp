#include "../l/lib.h"
// #include "../l/mod.h"

class CGame {
public:
    void solve(istream& cin, ostream& cout) {
        int N, M, K; cin >> N >> M >> K;
        map<int, vector<pii>> Vert, Hor;
        for (int i = 0; i < K; ++i) {
            int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
            if (x1 == x2) {
                if (y1 > y2) swap(y1, y2);
                Hor[x1].emplace_back(y1,y2);
            } else {
                if (x1 > x2) swap(x1, x2);
                Vert[y1].emplace_back(x1,x2);
            }
        }

        int g = 0;
        vector<pair<pii, vector<pii>>> C;
        int bestLen = 0;
        pii from, to;
        if (N % 2 == 0) g ^= M;
        if (M % 2 == 0) g ^= N;
        for (int i = 1; i < N; ++i) if (Hor.find(i) == Hor.end()) {
            C.push_back({{-M,i},{{0,M}}});
            break;
        }
        for (int i = 1; i < M; ++i) if (Vert.find(i) == Vert.end()) {
            C.push_back({{N,i},{{0,N}}});
            break;
        }

        for (auto&h : Hor) {
            g ^= M;
            vector<pii> Ev;
            for (pii hh: h.y) { Ev.emplace_back(hh.x, 1); Ev.emplace_back(hh.y, -1); }
            Ev.emplace_back(M, 0);
            sort(Ev.begin(),Ev.end());
            int cnt = 0, last = 0, tot = 0;
            vector<pii> Z;
            for (pii ev: Ev) {
                if (!cnt && ev.x != last) {
                    Z.emplace_back(last,ev.x);
                    tot += ev.x - last;
                }

                cnt += ev.y;
                last = ev.x;
            }
            if (!Z.empty()) C.push_back({{-tot, h.x}, Z});

            g ^= tot;
        }

        for (auto&v : Vert) {
            g ^= N;
            vector<pii> Ev;
            for (pii vv: v.y) { Ev.emplace_back(vv.x, 1); Ev.emplace_back(vv.y, -1); }
            Ev.emplace_back(N, 0);
            sort(Ev.begin(),Ev.end());
            int cnt = 0, last = 0, tot = 0;
            vector<pii> Z;
            for (pii ev: Ev) {
                if (!cnt && ev.x != last) {
                    Z.emplace_back(last,ev.x);
                    tot += ev.x - last;
                }

                cnt += ev.y;
                last = ev.x;
            }

            if (!Z.empty()) C.push_back({{tot, v.x}, Z});
            g ^= tot;
        }

        if (g) {
            cout << "FIRST\n";
            for (auto&c : C) {
                int l = abs(c.x.x);
                if ((l^g) <= l) {
                    l = l - (l^g);
                    for (pii cc: c.y) {
                        if (l <= cc.y - cc.x) {
                            if (c.x.x < 0) {
                                cout << c.x.y << " 0 " << c.x.y << ' ' << cc.x + l << endl;
                            } else {
                                cout << "0 " << c.x.y << ' ' << cc.x + l << ' ' << c.x.y << endl;
                            }
                            break;
                        }
                        l -= cc.y - cc.x;
                    }
                    break;
                }
            }
        } else {
            cout << "SECOND\n";
        }

    }
};
