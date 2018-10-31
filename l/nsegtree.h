#include "lib.h"

template <typename ValueType, typename TagType,
          void (*combineTag)(TagType&, TagType),
          void (*applyTag)(ValueType&, TagType, ui),
          ValueType (*combineValues)(ValueType,ValueType)>
struct LSegTree {
    LSegTree(const vector<ValueType> & data, const ValueType& nullValue, const TagType& nullTag)
            : n(1<<logceil(data.size())), nullValue(nullValue), nullTag(nullTag), T(2*n, {nullValue, nullTag}) {
        for (int i = 0; i < data.size(); ++i) T[n+i].x = data[i];
        for (ui i = n-1; i > 0; i--) T[i].x = combineValues(T[i<<1].x,T[i<<1|1].x);
    }

    LSegTree(ui size, const ValueType& nullValue, const TagType& nullTag)
         : n(1<<logceil(size)), nullValue(nullValue), nullTag(nullTag), T(2*n, {nullValue, nullTag}) {
        for (ui i = n-1; i > 0; i--) T[i].x = combineValues(T[i<<1].x,T[i<<1|1].x);
    }

    inline void put(ui x, const TagType &n) { put(x, x, n); }
    inline void put(ui from, ui to, TagType v) { putInner(from, to, v, 1, n); }

    inline ValueType operator[](pair<ui,ui> x) { return get(x.x, x.y); }
    inline ValueType operator[](ui x) { return get(x, x); }
    inline ValueType get(ui x) const { return get(x, x); }
    inline ValueType get(ui from, ui to) { return getInner(from, to, 1, n); }

    void putInner(ui from, ui to, TagType v, ui i, ui s) {
        vector<int> Q;
        ui r = i;
        while (true) {
            if (from == 0 && to == s - 1) {
                applyTag(T[i].x, v, s);
                combineTag(T[i].y, v);
                break;
            }
            pushTagDown(i, s);
            s >>= 1;
            i <<= 1;
            if (from & s) {
                from ^= s;
                to ^= s;
                i ^= 1;
            } else if (to & s) {
                putInner(0, to ^ s, v, i | 1, s);
                to = s - 1;
            }
        }

        while (i != r) {
            T[i >> 1].x = combineValues(T[i].x, T[i^1].x);
            i >>= 1;
        }
    }


    ValueType getInner(ui from, ui to, ui i, ui s) {
        while (true) {
            if (from == 0 && to == s-1) return T[i].x;
            pushTagDown(i, s);
            s >>= 1; i <<= 1;
            if (to & s) {
                to ^= s;
                if (from & s) {
                    from ^= s; i |= 1;
                } else {
                    return combineValues(
                            getInner(from, s-1, i, s),
                            getInner(0, to, i|1, s)
                    );
                }
            }
        }
    }

    void pushTagDown(ui i, ui s) {
        applyTag(T[i<<1].x, T[i].y, s>>1);
        applyTag(T[i<<1|1].x, T[i].y, s>>1);
        combineTag(T[i << 1].y, T[i].y);
        combineTag(T[i << 1 | 1].y, T[i].y);
        T[i].y = nullTag;
    }

    ui n;
    ValueType nullValue;
    TagType nullTag;
    vector<pair<ValueType, TagType>> T;
};


template <typename F> void LAddOp(F &a, F b) { a += b; }
template <typename F> void LAddOp2(F &a, F b, ui) { a += b; }
//template <typename F> void LAddOp2(F &a, F b, ui x) { a += b * x; }
template <typename F> F LMinOp(F a, F b) { return std::min(a, b); }
template <typename F> F LMaxOp(F a, F b) { return std::max(a, b); }

//template <typename F> struct AddOp { F operator()(F a, F b) { return a+b; }};
//template <typename F> struct MinOp { F operator()(F a, F b) { return std::min(a,b); }};
//template <typename F> struct MaxOp { F operator()(F a, F b) { return std::max(a,b); }};
//template <typename F> struct MultiplyOp { F operator()(F a, F b) { return a*b; }};
//template <typename F> struct MultOp { F operator()(F a, ui b) { return a*b; }};
//template <typename F> struct IdempOp { F operator()(F a, ui b) { return a; }};
//template <typename F> struct InverseOp { F operator()(F a, F b) { return b?b-a:a; }};

//template<typename T> using LAddSumTree = LSegTree<T, T, LAddOp<T>, LAddMultOp2<T>, LAddOp<T>>;
template<typename T> using LAddMaxTree = LSegTree<T, T, LAddOp<T>, LAddOp2<T>, LMaxOp<T>>;
template<typename T> using LAddMinTree = LSegTree<T, T, LAddOp<T>, LAddOp2<T>, LMinOp<T>>;
//template<typename T> using LAssignMinTree = LSegTree<T, MinOp<T>, Lazy<T, MinOp<T>, IdempOp<T>>>;
//template<typename T> using AssignMaxTree = SegTree<T, MaxOp<T>, Lazy<T, MaxOp<T>, IdempOp<T>>>;
//template<typename T> using XorTree = SegTree<T, AddOp<T>, Lazy<T, InverseOp<T>, MultOp<T>>>;

//template<typename T> using SetMinTree = SegTree<T, MinOp<T>>;
//template<typename T> using SetMaxTree = SegTree<T, MaxOp<T>>;
//template<typename T> using SetMulTree = SegTree<T, MultiplyOp<T>>;
