#include "../../../l/lib.h"
#include "../../../l/util.h"

class tavasandpashmaks {
public:
    typedef pii Line;

    pair<ll,ll> inters(const Line&a, const Line&b) {
        return {a.x * b.x * ll(b.y - a.y), a.y * b.y * ll(a.x - b.x)};
    }

    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<pii> W(N); cin >> W;
        vector<pii> V = W;
        sort(V.begin(), V.end());
        V.erase(unique(V.begin(),V.end()), V.end());
        vector<Line> Sol{V[0]};
        int M = 1;
        for (pii v:V) {
            while (M >= 1 && ((Sol[M-1].y < v.y) || (Sol[M-1].y == v.y && Sol[M-1].x < v.x))) {
                Sol.pop_back();
                M -= 1;
            }


            while (M >= 2
                   && fractionGreaterOrEqual(inters(Sol[M-2], v), inters(Sol[M-1], v))
                   && !fractionGreaterOrEqual(inters(Sol[M-1], v), inters(Sol[M-2], v))) {

                Sol.pop_back();
                M -= 1;
            }

            Sol.push_back(v);
            M++;
        }

        vector<int> Z;
        for (int i = 0; i < N; ++i) {
            if (binary_search(Sol.begin(),Sol.end(),W[i])) Z.push_back(i+1);
        }
        cout << Z;
    }
};
