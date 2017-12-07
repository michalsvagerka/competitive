#include "lib.h"

template <typename Cost> class Hungary {
public:
	Hungary(const vector<vector<Cost>> &cost)
			: cost(cost), n(cost.size()), max_match(0), lx(n,0), ly(n,0), q(n), xy(n, -1), yx(n, -1), S(n), T(n), slack(n), slackx(n), prev(n) {};

	Cost maxCost() {
		for (int x = 0; x < n; x++) lx[x] = *max_element(cost[x].begin(), cost[x].end());

		while (max_match != n) augment();

		Cost ret = 0;
		for (int x = 0; x < n; x++) ret += cost[x][xy[x]];
		return ret;
	}

	Cost minCost() {
		for (auto &c:cost) for (auto&cc:c) cc = -cc;
		return -maxCost();
	}

	vector<vector<Cost>> cost;
	int n, max_match;
	vector<Cost> lx, ly, q, slack, slackx;
	vector<int> xy, yx, prev;
	vector<bool> S,T;

	int find_augmenting_path(int &x, int wr) {
		int rd = 0;
		while (true) {
			while (rd < wr) {
				x = q[rd++];
				for (int y = 0; y < n; y++)
					if (cost[x][y] == lx[x] + ly[y] && !T[y]) {
						if (yx[y] == -1) return y;
						T[y] = true;
						q[wr++] = yx[y];
						add_to_tree(yx[y], x);
					}
			}

			update_labels();
			wr = rd = 0;
			for (int y = 0; y < n; y++) {
				if (!T[y] && slack[y] == 0) {
					if (yx[y] == -1) {
						x = slackx[y];
						return y;
					} else {
						T[y] = true;
						if (!S[yx[y]]) {
							q[wr++] = yx[y];
							add_to_tree(yx[y], slackx[y]);
						}
					}
				}
			}
		}
	}

	void augment() {
		int x, root;
		int wr = 0;
		fill(S.begin(), S.end(), false);
		fill(T.begin(), T.end(), false);
		fill(prev.begin(), prev.end(), -1);
		for (x = 0; x < n; x++) {
			if (xy[x] == -1) {
				q[wr++] = root = x;
				prev[x] = -2;
				S[x] = true;
				break;
			}
		}
		for (int y = 0; y < n; y++) {
			slack[y] = lx[root] + ly[y] - cost[root][y];
			slackx[y] = root;
		}

		int y = find_augmenting_path(x, wr);
		max_match++;
		for (int cx = x, cy = y, ty; cx != -2; cx = prev[cx], cy = ty) {
			ty = xy[cx];
			yx[cy] = cx;
			xy[cx] = cy;
		}
	}

	void update_labels() {
		Cost delta = std::numeric_limits<Cost>::max();
		for (int y = 0; y < n; y++) if (!T[y]) delta = min(delta, slack[y]);
		for (int x = 0; x < n; x++) if (S[x]) lx[x] -= delta;
		for (int y = 0; y < n; y++) if (T[y]) ly[y] += delta;
		for (int y = 0; y < n; y++) if (!T[y]) slack[y] -= delta;
	}

	void add_to_tree(int x, int prevx) {
		S[x] = true;
		prev[x] = prevx;
		for (int y = 0; y < n; y++) {
			if (lx[x] + ly[y] - cost[x][y] < slack[y]) {
				slack[y] = lx[x] + ly[y] - cost[x][y];
				slackx[y] = x;
			}
		}
	}

};