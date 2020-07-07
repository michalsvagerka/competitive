#include "../../../l/lib.h"

class HNumberOfComponents {
public:
    int N, Q;
    vector<int> A;

    void build(vector<pii>&block, int from, int to) {

        block.clear();
        for (int i = from; i < to; ++i) {
            pii c = {A[i],A[i]};
            while (!block.empty() && block.back().x < c.y) {
                c = {min(block.back().x, c.x), max(block.back().y, c.y)};
                block.pop_back();
            }
            block.push_back(c);
        }
    }

    vector<vector<pii>> Blocks;

    struct BlockGroup {
        int blockId;
        int from, to;
        int lo, hi;
    };

    void solve(istream& cin, ostream& cout) {
        cin >> N >> Q;
        A.resize(N);
        cin >> A;

        int S = 2048;
        int B = (N+S-1)/S;
        Blocks.resize(B);
        for (int i = 0; i < B; ++i) {
            build(Blocks[i], i*S, min(i*S+S, N));
        }
        vector<unordered_map<int, int>> CacheL(B);
        vector<unordered_map<int, int>> CacheR(B);
        for (int q = 0; q < Q; ++q) {
            int p, x; cin >> p >> x;
            --p;
            int b = p/S;
            A[p] = x;
            build(Blocks[b], b*S, min(N, b*S+S));
            CacheL[b].clear();
            CacheR[b].clear();

            vector<BlockGroup> Groups;
            for (int i = 0; i < B; ++i) {
                auto &block = Blocks[i];
                if (Groups.empty() || Groups.back().lo >= block[0].y) {
                    Groups.push_back(BlockGroup{i, 0, (int)block.size(), block.back().x, block[0].y});
                } else {
                    int j;
                    if (Groups.back().lo < block[(int)block.size()-1].y) {
                        j = (int)block.size()-1;
                    } else {
                        auto it = CacheR[i].find(Groups.back().lo);
                        if (it != CacheR[i].end()) j = it->y;
                        else j = CacheR[i][Groups.back().lo] = bsh(0, (int)block.size()-1, [&](int x) { return Groups.back().lo < block[x].y; });
                    }
                    BlockGroup BG{-1, 0, 1, block.back().x, block[0].y};
                    while (!Groups.empty() && Groups.back().lo < BG.hi) {
                        auto &last = Groups.back();
                        if (last.blockId == -1) {
                            BG.lo = min(BG.lo, last.lo);
                            BG.hi = max(BG.hi, last.hi);
                            Groups.pop_back();
                        } else {
                            auto &lastB = Blocks[last.blockId];
                            if (lastB[last.from].x < BG.hi) {
                                BG.lo = min(BG.lo, last.lo);
                                BG.hi = max(BG.hi, last.hi);
                                Groups.pop_back();
                            } else {
                                auto it = CacheL[last.blockId].find(BG.hi);
                                int s = (it != CacheL[last.blockId].find(BG.hi)) ? it->y : CacheL[last.blockId][BG.hi] = bsl(last.from, last.to - 1, [&](int x) { return lastB[x].x < BG.hi; });
                                BG.lo = min(BG.lo, lastB[last.to-1].x);
                                BG.hi = max(BG.hi, lastB[s].y);
                                last.lo = lastB[s-1].x;
                                last.hi = lastB[last.from].y;
                                last.to = s;
                            }
                        }
                    }
                    Groups.push_back(BG);
                    if (j+1 != (int)block.size()) {
                        Groups.push_back(BlockGroup{i, j+1, (int)block.size(), block.back().x, block[j+1].y});
                    }
                }
            }

            int ans = 0;
            for (BlockGroup&bg: Groups) ans += bg.to - bg.from;
            cout << ans << '\n';
        }
    }
};
