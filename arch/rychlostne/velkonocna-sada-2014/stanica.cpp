#include "../l/lib.h"
// #include "../l/mod.h"

class stanica {
public:
    void solve(istream& cin, ostream& cout) {
        ui N; cin >> N;
        map<int, pair<vector<int>,vector<int>>>  E;
        for (ui i = 0; i < N; ++i) {
            int z,k; cin >> z >> k;
            E[z].x.push_back(i);
            E[k].y.push_back(i);
        }
        int last = 0;
        set<int> current;
        vector<int> alone(N, 0);
        unordered_map<pii, int> together;
        for (auto &e: E) {
            int len = e.x - last;

            if (current.size() == 1 || current.size() == 2) {
                vector<int> a;
                for (int v:current) a.push_back(v);
                if (a.size() == 1) {
                    alone[a[0]] += len;
                } else if (a.size() == 2) {
                    together[{a[0], a[1]}] += len;
                }
            }

            for (int add:e.y.x) current.insert(add);
            for (int rem: e.y.y) current.erase(rem);

            last = e.x;
        }

        int ans = 0;
        for (auto &tog: together) {
            ans = max(ans, tog.y + alone[tog.x.x] + alone[tog.x.y]);
        }
        sort(alone.begin(),alone.end());
        reverse(alone.begin(),alone.end());
        ans = max(ans, alone[0] + alone[1]);
        cout << ans << endl;
    }
};
