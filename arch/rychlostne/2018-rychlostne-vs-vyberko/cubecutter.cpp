#include "../../../l/lib.h"
// #include "../l/mod.h"

class cubecutter {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        int side = (N % 7 == 3) ? 4 : 6;
        vector<pair<pii,pii>> S;
        vector<pair<pii,pii>> O;
        if (N%7 == 3) {
            for (int x = 0; x < 4; ++x)
                for (int y = 0; y < 4; ++y)
                    for (int z = 0; z < 4; ++z) {
                        if (x < 3 && y < 3 && z < 3) continue;
                        O.push_back({{x, y}, {z, 1}});
                    }
            O.push_back({{0, 0}, {0, 3}});
        } else {
            int m = 1;
            for (int i = 0; i < 8; ++i) {
                if (m != N % 7) {

                    for (int x = 0; x < 3; ++x)
                        for (int y = 0; y < 3; ++y)
                            for (int z = 0; z < 3; ++z) {
                                    if (x < 2 && y < 2 && z < 2) continue;
                                    O.push_back({{x + 3 * (i & 1), y + 3 * ((i >> 1) & 1)},
                                                 {z + 3 * ((i >> 2) & 1), 1}});
                            }
                    m = (m+5)%7;
                    S.push_back({{3 * (i & 1), 3 * ((i >> 1) & 1)},
                                 {3 * ((i >> 2) & 1), 2}});
                } else {
                    O.push_back({{3 * (i & 1), 3 * ((i >> 1) & 1)},
                                  {3 * ((i >> 2) & 1), 3}});
                }
            }
        }

        while (S.size() + O.size() < N) {
            if (!S.empty()) {
                auto s = S.back();
                S.pop_back();
                int k = s.y.y/2;
                auto &Z = k%2 ? O : S;

                for (int x = 0; x < 2; ++x)
                    for (int y = 0; y < 2; ++y)
                        for (int z = 0; z < 2; ++z) {
                            Z.push_back({{s.x.x+x*k,s.x.y+y*k},{s.y.x+z*k,k}});
                        }
            } else {
                for (auto &s:S) { s.x.x *= 2; s.x.y *= 2; s.y.x *= 2; s.y.y *= 2; }
                for (auto &o:O) { o.x.x *= 2; o.x.y *= 2; o.y.x *= 2; o.y.y *= 2; S.push_back(o); }
                O.clear();
                side *= 2;
            }
        }

        cout << side << '\n';
        for (auto &o:O) S.push_back(o);
        ll vol = ll(side)*side*ll(side);
        for (auto &s: S) {
            vol -= ll(s.y.y) * s.y.y * ll(s.y.y);
//            for (auto &t: S) {
//                if (s!=t) {
//                    if (s.x.x + s.y.y <= t.x.x || t.x.x + t.y.y <= s.x.x ||
//                            s.x.y + s.y.y <= t.x.y || t.x.y + t.y.y <= s.x.y ||
//                            s.y.x + s.y.y <= t.y.x || t.y.x + t.y.y <= s.y.x) {
//
//                    } else {
//                        cout << "overlap " << s << ' ' << t << "\n";
//                    }
//                }
//            }
            cout << s.x.x << ' ' << s.x.y << ' ' << s.y.x << ' ' << s.y.y << '\n';
        }

//        if (vol != 0) {
//            cout << "remaining volume " << vol << endl;
//        }
    }
};
