#include "../l/lib.h"
// #include "../l/mod.h"

class Volcanoes {
public:
void solve(istream& cin, ostream& cout) {
    int N, M; cin >> N >> M;
    map<int, set<int>> CH;
    for (int i = 0; i < M; ++i) {
        int x,y; cin >> x >> y;
        CH[x].insert(y);
    }

    vector<pii> S{{1, 1}};
    int lastX = 0;
    for (auto &ch: CH) {
        if (ch.x > lastX + 1) {
            S = {{S[0].x, N}};
        }

        vector<pii> T;
        auto it = ch.y.begin();
        for (pii s:S) {
            while (it != ch.y.end() && *it <= s.y) {
                if (s.x <= *it) {
                    if (s.x < *it) T.emplace_back(s.x, *it - 1);
                    s.x = *it + 1;
                }
                ++it;
            }
            if (s.x <= s.y) {
                if (it != ch.y.end()) s.y = *it - 1; else s.y = N;
                T.emplace_back(s.x,s.y);
            }
        }

        S.clear();
        for (pii t:T) {
            if (S.empty() || S.back().y < t.x) S.push_back(t);
        }
        if (S.empty()) break;

//        cout << ch.x << ':' << S;
        lastX = ch.x;
    }

    if (S.empty() || (lastX == N && S.back().y != N)) {
        cout << "-1\n";
    } else { cout << 2*N-2<< endl; }
}
};
