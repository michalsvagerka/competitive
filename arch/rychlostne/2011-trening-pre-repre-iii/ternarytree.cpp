#include "../l/lib.h"
// #include "../l/mod.h"

class ternarytree {
public:
    void solve(istream& cin, ostream& cout) {
        int K; cin >> K;
        int l = 1;
        for (int i = 0; i < K - 1; ++i) {
            l *= 3;
        }
        vector<int> Z((3*l-1)/2+1,0);
        vector<int> Q(l), A(l,4);
        cin >> Q;
        for (int j = 0; j < l; ++j) {
            Z[Q[j] + (l-1)/2] = j + 1;
        }

        for (int k = 1; k < K; ++k) {
            l /= 3;
            for (int x = 0; x < l; ++x) {
                int y = x + (l-1)/2 + 1;
//                cerr << y << ' ' << Z[3*y-1] << ' ' << Z[3*y] << ' ' << Z[3*y+1] << endl;

                int a = Z[3*y-1];
                int b = Z[3*y];
                int c = Z[3*y+1];
                if (a > b && a > c) {
                    A[b-1] = 0;
                    A[c-1] = 1;
                    Z[y] = a;
                } else {
                    A[a-1] = 0;
                    A[min(b,c)-1] = 1;
                    Z[y] = max(b,c);
                }
//                cerr << a << ' ' << b << ' ' << c << endl;
            }
        }
        A[Z[1]-1] = 1;

//        cout << Z;
        cout << A;
    }
};
