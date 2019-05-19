#include "../l/lib.h"

class interrect {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<pair<pii,pii>> Ev;
        for (int i = 0; i < N; ++i) {
            int x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            if (y1 > y2) swap(y1, y2);
            Ev.push_back({{x1, 1},{y1,y2}});
            Ev.push_back({{x2, -1},{y1,y2}});
        }

        sort(Ev.begin(),Ev.end());
        set<int> S;
        for (auto &ev: Ev) {
            if (ev.x.y == -1) {
                S.erase(ev.y.x);
                S.erase(ev.y.y);
            }

            auto a = S.lower_bound(ev.y.x);
            auto b = S.lower_bound(ev.y.y);
            if (a != b) {
                cout << 1 << endl;
                return;
            }

            if (ev.x.y == 1) {
                S.insert(ev.y.x);
                S.insert(ev.y.y);
            }
        }



        cout << 0 << endl;

    }
};
