#include "../../../l/lib.h"
// #include "../l/mod.h"

class TaskB {
public:
    string morph(const string &A) {
        if (A.size()%2) return A;
        string B(A.begin(),A.begin()+A.size()/2);
        string C(A.begin()+A.size()/2,A.end());
        B = morph(B);
        C = morph(C);
        if (B < C) return B+C;
        else return C+B;
    }

void solve(istream& cin, ostream& cout) {
    string A, B; cin >> A >> B;
    A = morph(A);
    B = morph(B);
    if (A==B) cout << "YES\n";
    else cout << "NO\n";
}
};
