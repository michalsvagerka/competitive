#include "../l/lib.h"

class DAlexAndJulian {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<ll> A(N); cin >> A;
        sort(A.begin(),A.end());
        vector<ll> B = A;

        vector<ll> Keep;
        ll f = 1;
        while (!A.empty()) {
            vector<ll> O, E;
            for (ll a: A) {
                if (a&1) O.push_back(a);
                else E.push_back(a/2);
            }

            if (O.size() > Keep.size()) {
                for (ll&o: O) o *= f;
                Keep = O;
            }

            swap(E, A);
            f *= 2;
        }
        
        vector<ll> Ans;
        set_difference(B.begin(),B.end(),Keep.begin(),Keep.end(), back_inserter(Ans));

        cout << Ans.size() << '\n' << Ans;
    }
};
