#include "../l/lib.h"
#include "../l/mod.h"

typedef FieldMod T;

class heaps {
public:
    vector<int> R;
    vector<vector<int>> E;

    T eval(const vector<T>&P, int x) {
        T ans = 0;
        for (T p: P) { ans *= x; ans += p; }
        return ans;
    }

    vector<T> mul(const vector<T>&a, const vector<T>&b) {
        vector<T> r(a.size()+b.size()-1);
        for (int i = 0; i < a.size(); ++i) {
            for (int j = 0; j < b.size(); ++j) {
                r[i+j] += a[i] * b[j];
            }
        }
        return r;
    }

    void integral(vector<T>&a) {
        int n = a.size();
        for (int i = 1; i <= n; ++i) a[n-i] /= i;
        a.push_back(0);
    }

    int solve(int v, vector<T> &ans) {
        ans = {T{1}};
        int lo = R[v];

        for (int w: E[v]) {
            vector<T> Q;
            int ss = solve(w, Q);
            T tot = eval(Q, ss);
            for (auto &qq: Q) qq = -qq;
            Q.back() += tot;
            ans = mul(ans, Q);
            lo = min(lo, ss);
        }

        integral(ans);
        return lo;
    }

    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        R.resize(N);
        E.resize(N);
        int root = -1;
        for (int i = 0; i < N; ++i) {
            int p;
            cin >> R[i] >> p;
            --p;
            if (p != -1) E[p].push_back(i); else root = i;
        }

        vector<T> Sol;
        int ss = solve(root, Sol);
        T ans = eval(Sol, ss);
        for (int r:R) ans /= r;
        cout << ans << endl;
    }
};
