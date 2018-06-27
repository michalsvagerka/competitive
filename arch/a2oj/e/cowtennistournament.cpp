#include "../../../l/lib.h"
 #include "../../../l/segtree.h"

// NICE TRICK!!
class cowtennistournament {
public:
    void solve(istream& cin, ostream& cout) {
        int N, K; cin >> N >> K;
        vector<int> A(N); cin >> A;
        sort(A.begin(),A.end());

        vector<vector<int>> Add(N), Remove(N);
        for (int k = 0; k < K; ++k) {
            int a, b; cin >> a >> b;
            int i = distance(A.begin(),lower_bound(A.begin(),A.end(),a));
            int j = distance(A.begin(),upper_bound(A.begin(),A.end(),b)) - 1;

            if (in(0,i,N) && in(0,j,N) && i < j) {
                Add[i].push_back(j);
                Remove[j].push_back(i);
            }
        }

        ll ans = ll(N)*ll(N-1)*ll(N-2)/6;
        XorTree<int> T;
        T.setup(N, 0);
        for (int i = 0; i < N; ++i) {
            for (int a:Add[i]) T.put(i,a,1);
            int w = 0;
            if (i != 0) w += i - T.get(0, i-1);
            if (i != N-1) w += T.get(i+1, N-1);

            for (int r:Remove[i]) T.put(r,i,1);

            ans -= ll(w)*ll(w-1)/2;
        }

        cout << ans << '\n';
    }
};
