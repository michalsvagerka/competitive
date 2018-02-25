#include "../../../l/lib.h"
// #include "../l/mod.h"

class indivisible {
public:
    vector<int> R;
    vector<int> Z;
    int E;

    bool test(int min, int max, int need) {
        if (need == 0) return true;
        if (E < need) return false;
        while (Z[min]) ++min;
        E--;
        for (int i = 2*min; i <= max; i+=min) {
            if (!Z[i]++) E--;
        }
        R.push_back(min);
        if (test(min+1, max, need-1)) return true;
        R.pop_back();

        for (int i = 2*min; i <= max; i+=min) {
            if (!--Z[i]) E++;
        }
        if (test(min+1, max, need)) return true;
        ++E;
        return false;
    }

    void brute(int N) {
        Z.resize(N+1);
        fill(Z.begin(),Z.end(),0);
        Z[0] = Z[1] = 1;
        int lo = 2;
        while (4*lo*lo <= N) lo*= 2;
        E = N-lo+1;
        test(lo, N, (N+1)/2);
    }

    void smart(int N) {
        vector<bool> Q(N+1, false);
        for (int i = N; i > N/2; --i) {
            Q[i] = true;
        }

        for (int i = N-N%2; i > 0; i-=2) {
            if (Q[i]) {
                bool ok = true;
                for (int j = 3*i/2; j <= N; j+=i/2) {
                    if (Q[j]) { ok = false; break; }
                }
                if (ok) {
                    Q[i/2] = true;
                    Q[i] = false;
                }
            }
        }

        for (int i = 0; i <= N; ++i) {
            if (Q[i]) R.push_back(i);
        }
    }

    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        if (N == 1) { cout << "1\n"; return; }
//        brute(N);
        smart(N);
        for (int r:R) cout << r << endl;
    }
};
