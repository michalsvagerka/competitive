#include "../l/lib.h"
// #include "../l/mod.h"

class zlatykluc {
public:
	typedef pair<int, pii> point;
	typedef pair<point, point> edge;

	bool read(istream &cin, vector<edge>&K) {
		int N; cin >> N;
		if (N == 0) return false;

		point cur{0,{0,0}};
		map<int, point> M;
		for (int i = 0; i < N; ++i) {
			string s; cin >> s;

			point d{0,{0,0}};
			if (s[0] == '-') {
				if (s[1] == 'x') d.x = -1;
				else if (s[1] == 'y') d.y.x = -1;
				else d.y.y = -1;
			} else if (s[0] == '+') {
				if (s[1] == 'x') d.x = 1;
				else if (s[1] == 'y') d.y.x = 1;
				else d.y.y = 1;
			} else {
				stringstream ss(s);
				int n; ss >> n;
				if (M.find(n) != M.end()) {
					cur = M[n];
				} else {
					M[n] = cur;
				}
				continue;
			}

			point next{cur};
			next.x += d.x;
			next.y.x += d.y.x;
			next.y.y += d.y.y;
			K.push_back({cur, next});
			K.push_back({next, cur});
			cur = next;
		}
		return true;
	}

	point rotate(point &p, int r) {
		if (r==0) {
			return {-p.y.x, {p.x, p.y.y}};
		} else if (r==1) {
			return {-p.y.y, {p.y.x,p.x}};
		} else {
			return {p.x, {-p.y.y, p.y.x}};
		}
	}

	void normalize(vector<edge>&E) {
		int mx = 100000, my = 100000, mz = 100000;

		for (edge e:E) {
			mx = min(mx, e.x.x);
			my = min(my, e.x.y.x);
			mz = min(mz, e.x.y.y);
			mx = min(mx, e.y.x);
			my = min(my, e.y.y.x);
			mz = min(mz, e.y.y.y);
		}
		for (edge&e: E) {
			e.x.x -= mx;
			e.x.y.x -= my;
			e.x.y.y -= mz;
			e.y.x -= mx;
			e.y.y.x -= my;
			e.y.y.y -= mz;
		}
		sort(E.begin(), E.end());
	}

	vector<edge> rotate(const vector<edge> &E, int r) {
		vector<edge> R;
		for (edge e: E) {
			R.push_back({rotate(e.x, r), rotate(e.y,r)});
		}
		normalize(R);
		return R;
	}

	void print(vector<edge> &a) {
		for(edge e:a) {
			cerr << e.x.x << ' ' << e.x.y.x << ' ' << e.x.y.y << ' '  << e.y.x << ' ' << e.y.y.x << ' ' << e.y.y.y << ' ';
 		}
		cerr << endl;
	}

	bool issame(vector<edge> &a, vector<edge> &b, int i) {
		if (i==3) {
//			print(a);
			return a == b;
		}

		if (issame(a,b,i+1)) return true;
		for (int j = 0; j < 3; ++j) {
			a=rotate(a,i);
			if (issame(a,b,i+1)) return true;
		}
		return false;

	}

    void solve(istream& cin, ostream& cout) {
		vector<edge> A, B;
		while (true) {
			A.clear();
			B.clear();
			if (!read(cin, A)) return;
			if (!read(cin, B)) return;

			//cerr << A.size() << ' ' << B.size() << endl;
			normalize(B);
//			print(B);

			cout << (A.size() == B.size() && issame(A,B,0) ? "SAME" : "DIFFERENT") << endl;
		}
    }
};
