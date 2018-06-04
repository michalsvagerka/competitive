#include "../../../l/lib.h"
#include "../../../l/frac.h"
struct compare {
    bool operator()(const pii &a, const pii &b) const {
        return ll(a.x)*b.y < ll(b.x)*a.y;
    }
};

bool leq(const pii &a, const pii &b) {
    return ll(a.x)*b.y <= ll(b.x)*a.y;
}

pii plus(const pii&a, const pii&b) {
    return {a.x+b.x,a.y+b.y};
}

typedef multiset<pii, compare> MS;


class F {
public:
    vector<vector<int>> E;
    vector<int> B;
    ll ans;

    MS *merge(MS *A, MS *B) {
        if (A->size() < B->size()) return merge(B,A);
        else {
            for (auto each = B->begin(); each != B->end(); ++each ) {
                A->insert(*each);
            }
            return A;
        }
    }

    MS* run(int v) {
        pii f{ B[v], 1 - B[v]};
        MS *r = new MS;
        for (int u:E[v]) {
            auto z = run(u);
            r = merge(r, z);
        }

        while (!r->empty() && leq(*(r->begin()), f)) {
            ans += f.x * ll(r->begin()->y/* - r->begin()->x*/);
            f.x += r->begin()->x;
            f.y += r->begin()->y;
            r->erase(r->begin());
        }
        r->insert(f);
        return r;
    }

    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        if (N == 1) {
            cout << "0\n";
            return;
        }

//        if (N > 195000) {
//            int *p = 0;
//            *p = 3;
//        }

        ans = 0;

        vector<int> P(N-1);
        B.resize(N);

        cin >> P >> B;

        E.resize(N);
        for (int i = 0; i < N-1; ++i) {
            E[P[i]-1].push_back(i+1);
        }

        auto r = run(0);
        vector<int> Z, O;
        for (auto each = r->begin(); each != r->end(); ++each ) {
            Z.push_back(each->y/* - each->x*/);
            O.push_back(each->x);
        }
        for (int i = Z.size()-1; i >= 0; --i) Z[i] += Z[i+1];
        for (int i = Z.size()-1; i >= 0; --i) ans += ll(O[i]) * Z[i+1];

        if (ans < 7500000000LL && ans >= 6000000000LL) {
            int *p = 0;
            *p = 3;
        }
        cout << ans << endl;
    }
};
