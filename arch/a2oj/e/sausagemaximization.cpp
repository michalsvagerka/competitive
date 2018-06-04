#include "../../../l/lib.h"
// #include "../l/mod.h"


struct Node {
    Node *ch[2];
};

constexpr int bits = 40;

class sausagemaximization {
public:


    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<ll> P(N+1, 0);
        Node root = {nullptr, nullptr};
        for (int i = 0; i < N; ++i) {
            ll a; cin >> a;
            P[i+1] = P[i] ^ a;
        }

        ll ans = 0;


        for (int i = 0; i <= N; ++i) {
            Node *cur = &root;
            ll X = P[i];
            for (int b = bits-1; b >= 0; b--) {
                int q = (X >> b) & 1;
                if (!cur->ch[q]) cur->ch[q] = new Node{nullptr,nullptr};
                cur = cur->ch[q];
            }

            cur = &root;
            X = P[N] ^ P[i];

            ll V = 0;
            for (int b = bits-1; b >= 0; b--) {
                ll q = 1 ^ ((X >> b) & 1);
                if (!cur->ch[q]) q ^= 1;
                cur = cur->ch[q];
                V |= q << b;
            }

            ans = max(ans, V^X);

        }
        cout << ans << endl;

    }
};
