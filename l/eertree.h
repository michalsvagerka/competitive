template <typename Char> class Eertree {
public:
    struct Node {
        int length; // number of characters in palindrome
        int suffix; // longest suffix that is also a palindrome
        int start; // index of first character of first occurrence of this
        int count; // number of occurences of this palindrome as longest palindrome suffix
        int chain; // number of suffixes that are also a palindrome
        unordered_map<Char, int> edges; // insert edges
    };

    explicit Eertree()
            : V{{0, 1, 0, 0, 0, {}},{-1, 1, 0, 0, 0, {}}}, cur(1), len(0) {}

    explicit Eertree(const string &s)
            : Eertree() { insertAll(s); }

    void follow_back(Char ch) {
        while (true) {
            int k = V[cur].length;
            if (len - k - 2 >= 0 && C[len - k - 2] == ch) break;
            cur = V[cur].suffix;
        }
    }

    void insertAll(const string &v) {
        for (char ch : v) insertChar(ch);
    }

    void insertChar(Char ch) {
        C.push_back(ch);
        ++len;
        follow_back(ch);

        auto it = V[cur].edges.find(ch);
        if (it != V[cur].edges.end()) {
            cur = it->y;
            V[cur].count++;
        } else {
            V[cur].edges[ch] = V.size();
            int l = V[cur].length;
            if (cur == 1) {
                V.push_back({1, 0, len-1, 1, 1, {}});
            } else {
                cur = V[cur].suffix;
                follow_back(ch);
                V.push_back({l + 2, V[cur].edges[ch], len - l - 2, 1, V[V[cur].edges[ch]].chain+1, {}});
            }
            cur = V.size()-1;
        }
    }

    void print(ostream& os) const {
        for (int i = 2; i < V.size(); ++i) {
            os << V[i].chain << ';' << V[i].count << '*';
            for (int j = V[i].start; j < V[i].start + V[i].length; ++j) os << C[j];
            os << " \n"[i==V.size()-1];
        }
    }

public:
    vector<Char> C;
    vector<Node> V;
    int cur, len;
};