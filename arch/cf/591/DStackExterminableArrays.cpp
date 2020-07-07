#include "../../../l/lib.h"
#include "../../../l/random.h"

class DStackExterminableArrays {
public:
    struct Node {
        int cnt;
        Node* par;
        map<int, Node*> next;
    };

    void solve(istream& cin, ostream& cout) {
        int Q;
//        Q = 10000000;
//        int w = 0;
        cin >> Q;
        random_int R{100};
        for (int q = 0; q < Q; ++q) {
            int N;
//            N = 50;
            cin >> N;
            vector<int> A(N);
            cin >> A;
//            for (int i = 0; i < N; ++i) {
//                A[i] = R(rng)%2;
//            }
//
//
//            map<vector<int>, int> C;
//            C[{}]++;
//
//            int cnt = 0, cnt2 = 0;
//            for (int i = 0; i < N; ++i) {
//                vector<int> S;
//                for (int j = i; j < N; ++j) {
//                    if (!S.empty() && S.back() == A[j]) S.pop_back();
//                    else S.push_back(A[j]);
//                    if (S.empty()) cnt++;
//                }
//            }
//
//            vector<int> S;
//            for (int i = 0; i < N; ++i) {
//                if (!S.empty() && S.back() == A[i]) S.pop_back();
//                else S.push_back(A[i]);
//                cnt2 += C[S];
//                C[S]++;
//            }

            Node *root = new Node{1, nullptr};
            Node *cur = root;

            vector<int> T;

            ll ans = 0;
            for (int i = 0; i < N; ++i) {
                if (!T.empty() && T.back() == A[i]) {
                    cur = cur->par;
                    T.pop_back();
                } else {
                    auto it = cur->next.find(A[i]);
                    if (it == cur->next.end()) {
                        cur->next[A[i]] = new Node{0, cur};
                    }
                    cur = cur->next[A[i]];
                    T.push_back(A[i]);
                }

                ans += cur->cnt;
                cur->cnt++;
            }


//            cerr << cnt << ' ' << ans << endl;
//            if (cnt != ans) {
//                cerr << "FAIL " << cnt << ' ' << ans << ' ' << A;
//                return;
//            }
//
//            w += ans != 0;
//            if (q % 100 == 99) cerr << q+1  << ' ' << w << endl;
            cout << ans << '\n';
        }
    }
};
