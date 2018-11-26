#include "../l/lib.h"
// #include "../l/mod.h"

class ECandyPiles {
public:
void solve(istream& cin, ostream& cout) {
    int N; cin >> N;
    vector<int> A(N);
    cin >> A;
    sort(A.begin(),A.end());
    reverse(A.begin(),A.end());
    int i = 0;
    while (i < N && A[i] > i) i++;
    
    --i;
    int s = A[i] - i;
    int v = i;
    while (v < N && A[v] > i) ++v;
    int t = v - i;
    if (s % 2 == 1 && t % 2 == 1) {
        cout << "Second\n";
    } else {
        cout << "First\n";
    }
}
};
