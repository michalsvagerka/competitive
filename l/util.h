struct UnionFind {
	UnionFind(size_t N) : P(N, -1), comp(N) {}
	int find(int x) { while (P[x]>=0){x = P[x];}return x; }
	bool united(int x, int y) { return find(x) == find(y); }
	bool unite(int x, int y) { x=find(x);y=find(y);if(x==y){return false;}--comp;if(x<y){swap(x,y);}P[x]+=P[y];P[y]=x;return true;}
	vector<int> P;
	size_t comp;
};