#include "../l/lib.h"
#include "../l/primes.h"

class primesplit {
public:
    map<int,int> D;
    int best;
    vector<int> P;
    vector<vector<int>> A;
    vector<vector<int>> B;

    void solve(int N, ostream& cout, int diff, int t) {

        for (int i = 0; i < min(15, (int)P.size()); ++i) {
            int p = P[P.size()-1-i];
            if (t&(1<<i)) {
                diff += p;
                A[0].push_back(p);
            } else {
                diff -= p;
                A[1].push_back(p);
            }
        }

        if (abs(diff) < best) {
            best = abs(diff);
            B = A;
        }

        for (int i = min(15, (int)P.size())-1; i >= 0; --i) {
            if (t&(1<<i)) {
                A[0].pop_back();
            } else {
                A[1].pop_back();
            }
        }
    }

    void solve(int N, ostream& cout) {
        best = 100;
        A.clear(); A.resize(2);

        P = Sieve{ui(N-1)}.primes();
        reverse(P.begin(),P.end());
        int diff = 0;
        for (int i = 0; i < int(P.size())-15; ++i) {
            int p = P[i];
            if (diff < 0) {
                A[0].push_back(p);
                diff += p;
            } else {
                A[1].push_back(p);
                diff -= p;
            }
        }

        for (int i = 0; i < (1<<15); ++i) {
            solve(N, cout, diff, i);
        }

        cout << best << endl;
        cout << B[0].size() << endl << B[0];
        cout << B[1].size() << endl << B[1];
    }

void solve(istream& cin, ostream& cout) {
    int N; cin >> N;
    solve(N, cout);
//    for (int i = 2; i < 1000000; ++i) {
//        solve(i, cout);
//        if (i%10000 == 0) cerr << i << endl;
//    }
}
};
