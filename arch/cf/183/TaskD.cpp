#include "../l/lib.h"
 #include "../l/runtimemod.h"

class TaskD {
public:
void solve(istream& cin, ostream& cout) {
    int N, X; cin >> N >> X;
    if (X == 2) {
        cout << -1 << endl;
        return;
    }
    
    if (N == 1) {
        cout << X-1 << endl;
        return;
    }

    N++;
    for (int i = 2; i*i <= N; ++i) {
        if (N%i == 0) {
            cout << -1 << endl;
            return;
        }
    }

    int M = N-1;
    vector<int> R;
    for (int i = 2; i*i <= M; ++i) {
        if (M%i==0) {
            R.push_back(i);
            while (M%i==0) M /= i;
        }
    }
    if (M != 1) R.push_back(M);

    for (int h = X-1; h >= 2; --h) {
        bool ok = true;
        for (int r:R) ok &= RField{h, N}.pow((N-1)/r) != 1;
        if (ok) {
            cout << h << endl;
            return;
        }
        
        
    }

    cout << -1 << endl;
}
};
