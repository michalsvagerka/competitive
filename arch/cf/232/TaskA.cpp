#include "../l/lib.h"
 #include "../l/mod.h"

class TaskA {
public:
void solve(istream& cin, ostream& cout) {
    auto F = FieldMod::fact(40000);
    auto I = FieldMod::invfact(40000);


    int N; cin >> N;
    vector<int> A(N); cin >> A;
    map<int,int> P;
    for (int a:A) {
        for (int i = 2; i * i <= a; ++i) {
            while (a%i == 0) {
                a /= i;
                P[i]++;
            }
        }
        if (a != 1) P[a]++;
    }

    FieldMod ans = 1;
    for (auto &p:P) {
        ans *= F[p.y + N - 1] * I[p.y] * I[N-1];
    }
    cout << ans << endl;

}
};
