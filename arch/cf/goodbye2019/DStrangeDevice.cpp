#include "../../../l/lib.h"

class DStrangeDevice {
public:
    void solve(istream& cin, ostream& cout) {
        int K, N; cin >> N >> K;
        if (K == 1) {
            cout << "! " << 1 << endl;
            return;
        }
        vector<int> A(N, -1);
        vector<bool> Q(N, false);
        for (int i = 0; i < K-1; ++i) Q[i] = true;
        for (int i = K-1; i < N; ++i) {
            Q[i] = true;
            cout << "?";
            for (int j = 0; j < N; ++j) if (Q[j]) cout << ' ' << j+1;
            cout << endl;
            int a, b; cin >> a >> b;
            --a;
            A[a] = b;
            Q[a] = false;
        }
        assert(count(Q.begin(),Q.end(),false) == N-K+1);
        if (K <= count(Q.begin(),Q.end(),false)) {
            cout << "?";
            int v = 0;
            vector<int> Last;
            for (int j = 0; j < N; ++j) {
                if (!Q[j] && v < K) {
                    assert(A[j] != -1);
                    Last.push_back(A[j]);
                    cout << ' ' << j+1;
                    ++v;
                }
            }
            assert(Last.size() == K);
            cout << endl;
            int a, b; cin >> a >> b;
            sort(Last.begin(),Last.end());
            for (int i = 0; i < N; ++i) {
                if (Last[i] == b) {
                    cout << "! " << i+1 << endl;
                    return;
                }
            }
            assert(false);
        } else {
            vector<int> Other, Mine;
            for (int i = 0; i < N; ++i) if (Q[i]) Other.push_back(i); else Mine.push_back(i);
            assert(Mine.size() >= 2);
            Mine.resize(2);
            assert(A[Mine[0]] != -1);
            assert(A[Mine[1]] != -1);
            if (A[Mine[0]] > A[Mine[1]]) swap(Mine[0],Mine[1]);
            int ans = 1;
            for (int i = 0; i < K-1; ++i) {
                cout << "? " << Mine[0]+1 << ' ' << Mine[1]+1;
                for (int j = 0; j < K-1; ++j) if (i!=j) cout << ' ' << Other[j]+1;
                cout << endl;
                int a, b; cin >> a >> b;
                --a;
                assert(a == Mine[0] || a == Mine[1]);
                if (a == Mine[1]) ans++;
            }

            cout << "! " << ans << endl;
            return;
        }
    }
};
