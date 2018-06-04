#include "../../../l/lib.h"
#include "../../../l/primes.h"

class jzzhuandapples {
public:
    void solve(istream& cin, ostream& cout) {
        ui N; cin >> N;
        if (N < 4) {
            cout << "0\n";
            return;
        }

        vector<bool> M(N+1, false);

        vector<int> Sol;
        auto P = Sieve{N/2}.primes();
        reverse(P.begin(),P.end());
        for (int p: P) {
            Sol.push_back(p);
            M[p] = true;
            for (int k = 3*p; k <= N; k += p) {
                if (!M[k]) {
                    Sol.push_back(k);
                    M[k] = true;
                }
            }
            if (Sol.size()%2) {
                M[2*p] = true;
                Sol.push_back(2*p);
            }
        }

        cout << Sol.size() / 2 << endl;
        for (int i = 0; i < Sol.size(); i+=2) {
            cout << Sol[i] << ' ' << Sol[i+1] << '\n';
        }
    }
};
