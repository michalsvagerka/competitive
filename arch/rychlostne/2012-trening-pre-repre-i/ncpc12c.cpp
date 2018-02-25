#include "../../../l/lib.h"
#include "../../../l/avl.h"

class ncpc12c {
public:
    void solve(istream& cin, ostream& cout) {
        string S;
        avl<int,int> T;
        while (cin >> S) {
            if (S == "#") {
                int N = T.size();
                int O = N/2;
                int V = T.select(O)->v;
                T.remove(V);
                cout << V << '\n';
            } else {
                stringstream ss(S);
                int K; ss >> K;
                T.insert(K, K);
            }
        }
    }
};
