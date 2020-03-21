#include "../l/lib.h"

struct Node {
    int resId;
    int x;
    bool ser;
    vector<Node*> nodes;
};

class EKirchhoffsCurrentLoss {
public:
    int id; ll R;
    vector<ll> Ans;

    void put(Node* n, int val) {
        if (n->resId != -1) {
            Ans[n->resId] = R*val;
        } else if (n->ser) {
            for (Node*o:n->nodes) {
                if (o->x == n->x) { put(o, val); val = 0; } else put(o, 0);
            }
        } else {
            for (Node*o:n->nodes) put(o, val);
        }
    }

    Node* readRes(const string& S, int &i) {
        if (S[i] == '*') {
            ++i;
            return new Node{id++, 1};
        } else {
            Node* n = new Node{-1};
            ++i;
            while (true) {
                n->nodes.push_back(readRes(S, i));
                if (S[i] == 'S') { n->ser = true; ++i; }
                else if (S[i] == 'P') { n->ser = false; ++i; }
                else {
                    ++i;
                    if (n->ser) {
                        n->x = n->nodes[0]->x;
                        for (Node* o: n->nodes) n->x = min(n->x, o->x);
                    } else {
                        n->x = 0;
                        for (Node* o: n->nodes) n->x += o->x;
                    }
                    return n;
                }
            }
        }
    };

    void print(Node*n, ostream&cout) {
        cout << "[" << n->x << "]";
        if (n->resId != -1) {
            cout << n->resId;
        } else {
            for (int i = 0; i < n->nodes.size(); ++i) {
                if (i == 0) cout << "(";
                else cout << "PS"[n->ser] << " ";
                print(n->nodes[i], cout);
                cout << " )"[i==n->nodes.size()-1];
            }
        }
    }

    void solve(istream& cin, ostream& cout) {
        int T; cin >> T;
        for (int t = 0; t < T; ++t) {
            cin >> R;
            int bal = 0;
            string S;
            do {
                char c; cin >> c;
                S += c;
                if (c == '(') ++bal;
                else if (c == ')') --bal;
            } while (bal > 0);
            id = 0;
            int i = 0;
            Node *n = readRes(S, i);
//            print(n, cout);
            Ans.resize(id);
            put(n, n->x);
//            cout << n->x << endl;
            cout << "REVOLTING " << Ans;
        }
    }
};
