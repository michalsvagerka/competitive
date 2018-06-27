#include "../../../l/lib.h"
 #include "../../../l/primes.h"

class numbers {
public:
    vector<int> P;
    int A, B;

    int count(int prime, int A, int B, bool parity, bool fresh) {
        if (A == B) return 0;
        int ans = fresh ? parity ? (B - A) : (A - B) : 0;
        if (prime < P.size()) {
            ans += count(prime + 1, A, B, parity, false);
            ans += count(prime + 1, A/P[prime], B/P[prime], !parity, true);
        }
        return ans;
    }


    void solve(istream& cin, ostream& cout) {
        int K;
        cin >> A >> B >> K;
        if (K > B) {
            cout << "0\n";
            return;
        }

        for (int i = 2; i*i <= K; ++i) {
            if (K%i == 0) {
                cout << "0\n";
                return;
            }
        }

        A = (A-1)/K;
        B = B/K;

        P = Sieve{(ui)min(B, K-1)}.primes();

        int ans = count(0, A, B, true, true);
        cout << ans << endl;

    }
};
