#include "../../../l/lib.h"
// #include "../l/mod.h"

class TaskA {
public:
void solve(istream& cin, ostream& cout) {
    int H; cin >> H;
    vector<int> A(H+1); cin >> A;
    for (int h = 0; h < H; ++h) {
        if (A[h] > 1 && A[h+1] > 1) {
            int s = 0;
            vector<int> C,D;
            for (int i = 0; i <= H; ++i) {
                for (int j = 0; j < A[i]; ++j) {
                    C.push_back(s);
                    D.push_back(s - (i==h+1 && j!=0) );
                }
                s += A[i];
            }
            cout <<  "ambiguous\n" << C << D;
            return;
        }
    }
    cout << "perfect\n";

}
};
