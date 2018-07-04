#include "../../../l/lib.h"
 #include "../../../l/avl.h"

class TaskD {
public:
void solve(istream& cin, ostream& cout) {
    int N; cin >> N;
    map<int, avl<int,int>> A, R;
    for (int n = 0; n < N; ++n) {
        int a,t,x; cin >> a >> t >> x;
        if (a == 1) {
            A[x].insert(t, t);
        } else if (a == 2) {
            R[x].insert(t, t);
        } else {
            cout << A[x].smaller(t) - R[x].smaller(t) << '\n';
        }
    }

}
};
