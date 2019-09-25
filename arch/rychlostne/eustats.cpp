#include "../l/lib.h"

class eustats {
public:
    struct Node { Node *l, *r; int cnt; };

    int M;
    vector<Node*> Root;

    Node* build(int N) {
        if (N == 1) return new Node{nullptr,nullptr,0};
        else return new Node{build(N/2),build(N/2),0};
    }

    Node* put(Node *n, int l, int r, int v) {
        if (l+1 == r) return new Node{nullptr,nullptr,n->cnt+1};
        else {
            int m = (l+r)/2;
            if (v < m) return new Node{put(n->l,l,m,v),n->r,n->cnt+1};
            else return new Node{n->l,put(n->r,m,r,v),n->cnt+1};
        }
    }

    int get(Node *n, int l, int r, int L, int R) {
        if (L <= l && R >= r) return n->cnt;
        else if (L >= r || R <= l) return 0;
        else return get(n->l, l, (l+r)/2, L, R) + get(n->r, (l+r)/2, r, L, R);
    }

    void add(int j) {
        Node *n = put(Root.back(), 0, M, j);
        Root.push_back(n);
    }

    int get(int t, int a, int b) {
        return t == 0 ? 0 : get(Root[t], 0, M, a, b);
    }

    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<pii> A(N); cin >> A;
        vector<int> B(N);
        for (int i = 0; i < N; ++i) B[i] = A[i].y;
        sort(A.begin(),A.end());
        sort(B.begin(),B.end());

        M = 1<<logceil(N);
        Root.push_back(build(M));
        for (int i = 0; i < N; ++i) {
            int j = lower_bound(B.begin(),B.end(),A[i].y) - B.begin();
            add(j);
        }

        vector<int> W{0,0,0,0};
        int Q; cin >> Q;
        for (int i = 0; i < Q; ++i) {
            int a, b, c, d;
            cin >> a >> b >> c >> d;
            a ^= W[i];
            b ^= W[i+1];
            c ^= W[i+2];
            d ^= W[i+3];
            if (a > b) swap(a, b);
            if (c > d) swap(c, d);
            int e = lower_bound(A.begin(),A.end(),pii{a,0})-A.begin();
            int f = upper_bound(A.begin(),A.end(),pii{b,1<<30})-A.begin();
            int g = lower_bound(B.begin(),B.end(),c)-B.begin();
            int h = upper_bound(B.begin(),B.end(),d)-B.begin();
            int ans = get(f, g, h) - get(e, g, h);
            cout << ans << '\n';
            W.push_back(ans);
        }
    }
};
