#include "lib.h"

template<typename T> struct Fenwick {
	explicit Fenwick(ui N=0, T t=T()):N(1u<<logceil(N)),F(this->N,t),t(t){}
	explicit Fenwick(const vector<T>&A, T t=T()):N(1u<<logceil(A.size())),F(A),t(t){
        F.resize(N); fill(F.begin()+A.size(),F.end(),t);
		for(int i=0;i<N;i++){int j=i+lsb(i+1);if(j<N)F[j]+=F[i];}}
	void add(int i, T v){while(i<=N){F[i]+=v;i+=lsb(i+1);}}
	T sum(int i)const{T sum(t);while(i){sum+=F[i-1];i-=lsb(i);}return sum;}
	T range(int i,int j)const{j++; T s(t);while(j>i){s+=F[j-1];j-=lsb(j);}while(i>j){s-=F[i-1];i-=lsb(i);}return s;}
	T get(int i)const{return range(i,i);}
	void set(int i, T v) {add(i, v-get(i)); }
	constexpr int lsb(int i)const{return i&-i;}
    ui N;vector<T> F;T t;
};

template<typename F>struct NoCombine {
    const int NOCOMB=-2;
    void setup(ui){}void op(F&p,F n,ui,ui,ui){p=n;}F up(F l,F r,ui){return l==r?l:NOCOMB;}
    void down(F&u,F&l,F&r,ui,ui,ui){if(u!=NOCOMB){l=r=u;}u=NOCOMB;}};
template<typename F,typename Op>struct Persistent{Op o;void setup(ui){}void op(F&p,F n,ui,ui, ui){p=n;}F up(F l, F r, ui){return o(l,r);}void down(F&,F&,F&,ui,ui, ui b) {}};

template<typename F,typename SetOp,typename CombineOp,typename PowerOp>struct LazyProp{
    void setup(ui s){this->s=s;L=new F[s]();}
    void down(F&u,F&l,F&r,ui i,ui a,ui b){op(l,L[i],2*i,a,(a+b)/2);op(r,L[i],2*i+1,(a+b)/2,b);L[i]=0;}
    void op(F&p,F n,ui i,ui a,ui b){p=sop(p,pop(n,b-a));if(i<this->s)this->L[i]=sop(this->L[i],n);}
    F up(F l,F r,ui){return cop(l,r);}SetOp sop;CombineOp cop;PowerOp pop;F*L;ui s;
};

template <typename F> struct AddOp { F operator()(F a, F b) { return a+b; }};
template <typename F> struct MultOp { F operator()(F a, F b) { return a*b; }};
template <typename F> struct IdempOp { F operator()(F a, F b) { return a; }};
template <typename F> struct MinOp { F operator()(F a, F b) { return std::min(a,b); }};
template <typename F> struct MaxOp { F operator()(F a, F b) { return std::max(a,b); }};

template <typename F, typename Combine> struct SegTree {
	void setup(ui s, F def) {
		size = 1<<logceil(s);
		T = vector<F>(2*size, def);
		for (ui i = size-1; i > 0; i--) T[i] = op.up(T[2*i],T[2*i+1], i);
		op.setup(2*size);
	}

	void setup(vector<F> & data, F def = F()) {
		size = 1<<logceil(data.size());
		T = vector<F>(2*size, def);
		copy(data.begin(), data.end(), T.begin() + size);
		for (ui i = size-1; i > 0; i--) T[i] = op.up(T[2*i],T[2*i+1], i);
		op.setup(2*size);
	}

	inline void put(ui x, F n) { put(x, x, n); }
	inline void put(ui from, ui to, F n) { put2(from, to+1, n, 1, 0, size); }
	inline F get(ui x) { return get(x, x); }
	inline F get(ui from, ui to) { return get2(from, to+1, 1, 0, size); }

	void put2(ui from, ui to, F n, ui i, ui a, ui b) {
		if (from <= a && to >= b) { op.op(T[i], n, i, a, b); return; }
		if (from >= b || to <= a) { return; }
		op.down(T[i], T[2*i], T[2*i+1], i, a, b);
		put2(from, to, n, 2*i, a, (a+b)/2);
		put2(from, to, n, 2*i+1, (a+b)/2, b);
 		T[i] = op.up(T[2*i], T[2*i+1], i);
	}

	F get2(ui from, ui to, ui i, ui a, ui b) {
		if (from <= a && to >= b) { return T[i]; }
		op.down(T[i], T[2*i], T[2*i+1], i, a, b);
		if (to <= (a+b)/2) { return get2(from, to, 2*i, a, (a+b)/2); }
		else if (from >= (a+b)/2) { return get2(from, to, 2*i+1, (a+b)/2, b); }
		else return op.up(get2(from, to, 2*i, a, (a+b)/2), get2(from, to, 2*i+1, (a+b)/2, b), i);
	}

	ui size;
	vector<F> T;
	Combine op;
};

template<typename T> using SetGetTree = SegTree<T, NoCombine<T>>;
template<typename T> using AddSumTree = SegTree<T, LazyProp<T, AddOp<T>, AddOp<T>, MultOp<T>>>;
template<typename T> using AddMaxTree = SegTree<T, LazyProp<T, AddOp<T>, MaxOp<T>, IdempOp<T>>>;
template<typename T> using AddMinTree = SegTree<T, LazyProp<T, AddOp<T>, MinOp<T>, IdempOp<T>>>;
template<typename T> using AssignMinTree = SegTree<T, LazyProp<T, MinOp<T>, MinOp<T>, IdempOp<T>>>;
template<typename T> using AssignMaxTree = SegTree<T, LazyProp<T, MaxOp<T>, MaxOp<T>, IdempOp<T>>>;

template<typename T> using SetMinTree = SegTree<T, Persistent<T, MinOp<T>>>;
template<typename T> using SetMaxTree = SegTree<T, Persistent<T, MaxOp<T>>>;
