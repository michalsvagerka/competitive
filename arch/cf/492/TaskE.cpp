#include "../../../l/lib.h"
 #include "../../../l/mod.h"


class TaskE {
public:
    unordered_map<int, int> P, Q;
    int u,v,p,deep;
    int shift;

    void gen(int x, int prev, int l) {
        if (P.find(x) != P.end()) return;
        P[x] = prev;
        if (l == deep) return;

        for (int y = x-shift; y <= x+shift; ++y) {
            if (y != 0) {
                int r = Ring::div(1, y < 0 ? y + p : y, p);
                gen(r, x, l + 1);
            }
        }
    }

    vector<int> calc(int e) {
        vector<int> ans;
        while (P[e] != -1) {
            ans.push_back(3);
            int r = Ring::div(1, e, p);
            for (int s = -shift; s <= shift; ++s) {
                if ((P[e]+s+p)%p == r) {
                    for (int i = 0; i < abs(s); ++i) {
                        ans.push_back(1 + (s < 0));
                    }
                    break;
                }
            }
            e = P[e];
        }
        return ans;
    }

void solve(istream& cin, ostream& cout) {
    cin >> u >> v >> p;
    for (deep = 1; deep <= 6; ++deep) {
        shift = min(p-1, 100/deep-1);
        P.clear(); Q.clear();
        gen(u, -1, 0);
        swap(P,Q);
        gen(v, -1, 0);
        for (pii q:Q) {
            auto it = P.find(q.x);
            if (it != P.end()) {
                vector<int> a1 = calc(q.x);
                for (int&a:a1) {
                    if (a!=3) a = 3-a;
                }
                swap(P,Q);
                vector<int> a2 = calc(q.x);
                reverse(a2.begin(),a2.end());

                for (int&a:a1) a2.push_back(a);
                cout << a2.size() << '\n';
                cout << a2;

                return;
            }
        }
    }
}
};
