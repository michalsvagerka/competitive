#include "../../../l/lib.h"
#include "../../../l/fenwick.h"

class CKIntegers {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<int> P(N); cin >> P;
        vector<int> I(N);
        for (int i = 0; i < N; ++i) {
            P[i]--;
            I[P[i]] = i;
        }

        int lo = I[0], hi = I[0];
        vector<ll> Ans(N, 0);
        set<int> Left{I[0]}, Right;
        Fenwick<ll> Other(N, 0LL), SumPos(N, 0LL), Corr(N, 0LL);
        for (int i = 0; i < N; ++i) {
            if (P[i] != 0) {
                Other.add(i, 1);
                SumPos.add(i, i);
            }
        }
        Corr.add(I[0], 1);
        
        ll swp = 0;
        for (int i = 1; i < N; ++i) {
            int j = I[i];
            lo = min(lo, j);
            hi = max(hi, j);
            if (j > *Left.rbegin()) Right.insert(j);
            else Left.insert(j);
            if (Right.size() > Left.size()) {
                int x = *Right.begin();
                Left.insert(x);
                Right.erase(Right.begin());
            } else if (Left.size() >= Right.size() + 2) {
                int x = *Left.rbegin();
                Right.insert(x);
                Left.erase(x);
            }

            Other.add(j, -1);
            SumPos.add(j, -j);
            swp += i - Corr.sum(j);
            Corr.add(j, 1);

            int mid = *Left.rbegin();
            ll left = Other.range(lo, mid);
            ll sumLeft = SumPos.range(lo, mid);
            ll right = Other.range(mid, hi);
            ll sumRight = SumPos.range(mid, hi);
//            cout<<lo<<' '<<mid<<' '<<hi<<' '<<endl;
            Ans[i] = sumLeft - left * ll(lo) - (left)*(left-1)/2;
            Ans[i] += right * ll(hi) - sumRight - (right)*(right-1)/2;
            Ans[i] += swp;
        }
        cout << Ans;
    }
};
