#include "../l/lib.h"
#include "../l/consttree.h"
#include "../l/fenwick.h"

constexpr int LOGN = 17;

class EGoodSubsegments {
public:
    int N;
    vector<int> P;
    ConstTree<int, MinQOp<int>> Min{{0}};
    ConstTree<int, MaxQOp<int>> Max{{0}};
    vector<vector<pii>> Range;
    vector<vector<int>> ListId;
    vector<vector<pii>> FullRange;
    vector<vector<int>> G;
    vector<vector<int>> Pairs;

    void prepare(int l, int r, int depth) {
        if (l+1 >= r) {
            return;
        }
        int m = (l+r)/2;
        for (int i = l; i < r; ++i) FullRange[depth][i] = {l,r};

        int loA = N, hiA = 0, loB = N, hiB = 0;
        map<int, int> LL, LH, RL, RH;
        auto add = [&](map<int,int>&W, int s, int t) {
            auto it = W.find(s);
            if (it != W.end()) {
                G[it->y].push_back(t);
            } else {
                int g = G.size();
                G.push_back({t});
                W[s] = g;
            }
        };
        int bb = m;
        for (int a = m-1; a >= l; --a) {
            loA = min(loA, P[a]);
            hiA = max(hiA, P[a]);
            while (bb < r && P[bb] > loA && P[bb] < hiA) ++bb;
            if (hiA - loA + 1 == bb - a && bb != m) {
                Pairs[bb-1].emplace_back(a);
            }

            add(LL, loA - a, a);
            add(LH, hiA + a, a);
        }
        int aa = m-1;
        for (int b = m; b < r; ++b) {
            loB = min(loB, P[b]);
            hiB = max(hiB, P[b]);
            while (aa >= l && P[aa] > loB && P[aa] < hiB) --aa;
            if (hiB - loB + 1 == b - aa && aa != m-1) {
                Pairs[b].emplace_back(aa+1);
            }
            add(RL, loB + b, b);
            add(RH, hiB - b, b);
        }

        auto run = [&](const map<int, int>&A, const map<int, int>&B, int type, function<bool(int,int)> cmp, bool left) {
            for (auto &a: A) {
                auto it = B.find(a.x);
                if (it != B.end()) {
                    const auto &b = G[it->y];
                    const auto &e = G[a.y];
                    if (b.empty()) continue;
                    int s = b.size()-1;
                    for (int i = 0; i < e.size(); ++i) {
                        int lo = Min.get(left ? e[i] : m, left ? m-1 : e[i]);
                        int hi = Max.get(left ? e[i] : m, left ? m-1 : e[i]);
                        int c = bsl(0, s, [&](int x) {
                            return type ?
                                   cmp(Min.get(left ? m : b[x], left ? b[x] : m-1), lo)
                                   : cmp(Max.get(left ? m : b[x], left ? b[x] : m-1), hi);
                        });
                        int d = bsh(0, s, [&](int x) {
                            return type ?
                                   cmp(Max.get(left ? m : b[x], left ? b[x] : m-1), hi)
                                   : cmp(Min.get(left ? m : b[x], left ? b[x] : m-1), lo);
                        });

                        if (c != -1 && d != -1 && c <= d) {
                            Range[depth][e[i]] = pii{c, d};
                            ListId[depth][e[i]] = it->y;
                        }
                    }
                }
            }
        };

        run(LL, RH, 0, greater<int>(), true);
        run(LH, RL, 1, less<int>(), true);
        run(RL, LH, 0, greater<int>(), false);
        run(RH, LL, 1, less<int>(), false);

        prepare(l, m, depth+1);
        prepare(m, r, depth+1);
    }

    void solve(istream& cin, ostream& cout) {
        cin >> N;
        P.resize(N);
        cin >> P;
        Range = vector2<pii>(LOGN, N, {-1,-1});
        ListId = vector2<int>(LOGN, N, -1);

        FullRange = vector2<pii>(LOGN, N);
        Min = ConstTree<int, MinQOp<int>>{P};
        Max = ConstTree<int, MaxQOp<int>>{P};
        Pairs.resize(N);

        prepare(0, N, 0);

        int Q; cin >> Q;
        int S = max(2, int(sqrt(N)));
        vector<ll> Ans(Q, 0);
        vector<vector<pii>> ByR(N);
        vector<vector<pair<pii, int>>> Queries(N/S+1); // bucket -> {{right, left}, query}, sorted by right
        for (int i = 0; i < Q; ++i) {
            int l, r; cin >> l >> r; --l; --r;
            Queries[l / S].push_back({{r, l}, i});
            Ans[i] = r - l + 1;
            ByR[r].push_back({l, i});
        }

        ll cur;
        int left, right;
        auto putLeft = [&](int diff) {
            if (diff == 1) left -= 1;

            for (int i = 0; i < LOGN; ++i) {
                if (Range[i][left].x == -1) continue;
                int mid = (FullRange[i][left].x + FullRange[i][left].y)/2;

                int d = 0;
                if (mid > right || mid <= left) {
                    // mid is out of range, nothing to add
                } else if (FullRange[i][left].y > right) {
                    // add intersection Range[t][i][left] with [0,right)
                    auto &g = G[ListId[i][left]];
                    if (g.empty()) continue;
                    int r = bsh(0, (int)g.size()-1, [&](int x) { return g[x] <= right; });
                    d = r >= Range[i][left].x ? (min(r, Range[i][left].y) - Range[i][left].x + 1) : 0;
                } else {
                    // add all
                    d = (Range[i][left].y - Range[i][left].x + 1);
                }
                cur += diff == 1 ? d : -d;
            }

            if (diff == -1) left += 1;
        };

        auto putRight = [&](int diff) {
            if (diff == 1) right += 1;

            for (int i = 0; i < LOGN; ++i) {
                if (Range[i][right].x == -1) continue;

                int mid = (FullRange[i][right].x + FullRange[i][right].y)/2;
                int d = 0;
                if (mid > right || mid < left) {
                    // mid is out of range, nothing to add
                } else if (FullRange[i][right].x < left) {
                    // add intersection Range[t][i][left] with [0,right)
                    auto &g = G[ListId[i][right]];
                    if (g.empty()) continue;
                    int r = bsh(0, (int)g.size()-1, [&](int x) { return g[x] >= left; });
                    d = (r >= Range[i][right].x) ? (min(r, Range[i][right].y) - Range[i][right].x + 1) : 0;
                } else {
                    // add all
                    d = (Range[i][right].y - Range[i][right].x + 1);
                }
                cur += diff == 1 ? d : -d;
            }


            if (diff == -1) right -= 1;
        };

        Fenwick<ll> F(N, 0LL);
        for (int i = 0; i < N; ++i) {
            for (int p: Pairs[i]) {
                F.add(p, 1);
            }
            for (pii q: ByR[i]) {
                Ans[q.y] += F.range(q.x, i);
            }
        }

        for (int block = 0; block <= N/S; ++block) {
            auto &queries = Queries[block];
            sort(queries.begin(),queries.end());

            left = right = block * S;
            cur = 0LL;
            for (auto &query: queries) {
                int r = query.x.x, l = query.x.y;
                while (r > right) putRight(1);
                while (l > left) putLeft(-1);
                while (l < left) putLeft(1);

                Ans[query.y] += cur;
            }
        }

        for (ll ans: Ans) {
            cout << ans << '\n';
        }
    }
};
