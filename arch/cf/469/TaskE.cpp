#include <numeric>
#include "../../../l/lib.h"
// #include "../l/mod.h"

class TaskE {
public:
    vector<int> Ans;
    vector<int> Cur;

    void solve(const vector<int> &V, int b) {
        if (b == 18) {
            if (V.size() == 1 && V[0] == 0) {
                if (Ans.empty() || Ans.size() > Cur.size()) {
                    Ans = Cur;
                }
            }
            return;
        }

        bool hasOdd = false;
        vector<int> Z;
        for (int v:V) {
            if (v%2==0) Z.push_back(v/2); else hasOdd = true;
        }
        if (hasOdd) {
            Cur.push_back(-(1<<b));
            Z.clear();
            for (int v:V) Z.push_back(v%2==0?v>>1:(v+1)>>1);
            Z.erase(unique(Z.begin(),Z.end()),Z.end());
            solve(Z,b+1);
            Cur.pop_back();

            Cur.push_back((1<<b));
            Z.clear();
            for (int v:V) Z.push_back(v%2==0?v/2:(v-1)/2);
            Z.erase(unique(Z.begin(),Z.end()),Z.end());
            solve(Z,b+1);
            Cur.pop_back();

        } else {
            solve(Z,b+1);
        }
    }

    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<int> A(N); cin >> A;
        sort(A.begin(),A.end());
        A.erase(unique(A.begin(),A.end()),A.end());
        vector<int> cur{};
        solve(A,0);

        cout << Ans.size() << '\n' << Ans;
    }
};
