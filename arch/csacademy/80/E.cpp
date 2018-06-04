#include "../../../l/lib.h"
// #include "../l/mod.h"

class E {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<int> A(N); cin >> A;

        cout << A;
        flush(cout);
        int prev; cin >> prev;
        if (prev == 0) return;

        vector<int> C(N+1, 0), Q(N+1, 1);
        for (int a:A) C[a]++;
        vector<int> P(N, A.back());

        for (int i = 0; i < N-1; ++i) {
            rotate(A.begin(),A.begin()+1,A.end());
            cout << A;
            flush(cout);
            int cur; cin >> cur;
            if (cur == 0) return;
            P[(prev - cur + N - C[A.back()])/2 + C[A.back()] - Q[A.back()]] = A.back();
            Q[A.back()]++;
//            C[A.back()]--;
//            cerr << P;

            prev = cur;
        }

        cout << P;
        flush(cout);
        cin >> prev;

    }
};
