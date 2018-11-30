#include "../l/lib.h"
// #include "../l/mod.h"

class DHalfReflector {
public:
    void solve(istream& cin, ostream& cout) {
        int N, K; cin >> N >> K;
        string S; cin >> S;
//        if (N == 1) {
//            if (K % 2 == 0) cout << S << endl;
//            else cout << "AB"[S[0] == 'A'] << endl;
//            return;
//        }

        deque<int> W;
        for (int i = 0; i < N; ++i) {
            if (i > 0 && S[i-1] == S[i]) W.back()++;
            else W.push_back(1);
        }
        bool firstA = S[0] == 'A';
        int R = W.size();
        for (int i = 0; i < min(2*N + K%2, K); ++i) {

            if (firstA) {
                if (W.front() == 1) {
                    --R;
                    W.pop_front();
                    W.front()++;
                } else {
                    ++R;
                    W.front()--;
                    W.push_front(1);
                }
                firstA = false;
            } else {
                if (W.front() == 1) {
                    W.pop_front(); --R;
                } else {
                    W.front()--; firstA = true;
                }
                if (W.size()%2==firstA) W.back()++;
                else { W.push_back(1); ++R; }
            }
        }

        stringstream ss;
        while (!W.empty()) {
            ss << string(W.front(), "BA"[firstA]);
            W.pop_front();
            firstA = !firstA;
        }
        cout << ss.str() << '\n';

//        for (int i = 0; i < K; ++i) {
//            int j = 0; int left = 1;
//            while (in(0, j, N)) {
//                bool straight = S[j] == 'B';
//                S[j] = "BA"[straight];
//                if (straight) j += left;
//                else { j -= left; left = -left; }
//            }
//        }
//        cout << S << '\n';
    }
};
