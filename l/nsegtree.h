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
    inline ValueType get(ui x) { return get(x, x); }
    inline ValueType get(ui from, ui to) { return getInner(from, to, 1, n); }

    void pushAllDown() {
        ui s = n, t = 1;
        while (s) {
            for (ui i = t; i < (t<<1); ++i) pushTagDown(i, s);
            s >>= 1;
            t <<= 1;
        }
    }

    inline ValueType rawGet(ui x) { return T[n+x].x; }

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
            if (from == 0 && to == s-1) {
                return T[i].x;
            }
            pushTagDown(i, s);
            s >>= 1; i <<= 1;
            if (to & s) {
                to ^= s;
                if (from & s) {
                    from ^= s; i |= 1;
                } else {
                    auto a = getInner(from, s-1, i, s),
                            b = getInner(0, to, i|1, s);
                    return combineValues(a,b
                    );
                }
            }
        }
    }

    /** Returns lowest l such that pred(value[l,x]) returns true. The pred must be monotone!
     * If no suffix satisfies the condition, returns x+1 (i.e. empty interval).
     * If you want suffix of the whole array, use x == n-1 */
    template <typename Pred> ui longestSuffix(ui x, Pred pred) {
        ValueType value = nullValue;
        return longestSuffixInner2(x, 1, 0, n, value, pred);
    }

    template <typename Pred> ui longestSuffixInner(ui i, ui l, ui r, ValueType &curValue, Pred pred) {
        if (l + 1 != r) pushTagDown(i, r-l);
        ValueType nextValue = combineValues(T[i].x, curValue);
        if (pred(nextValue)) { curValue = nextValue; return l; }
        if (l + 1 == r) return r;
        ui s = longestSuffixInner(i << 1 | 1, (l + r) / 2, r, curValue, pred);
        if (s == (l+r)/2) {
            return longestSuffixInner(i << 1, l, (l + r) / 2, curValue, pred);
        } else {
            return s;
        }
    }

    template <typename Pred> ui longestSuffixInner2(ui x, ui i, ui l, ui r, ValueType &curValue, Pred pred) {
        if (x >= r-1) {
            return longestSuffixInner(i, l, r, curValue, pred);
        }

        if (l + 1 == r) {
            ValueType nextValue = combineValues(T[i].x, curValue);
            if (pred(nextValue)) { curValue = nextValue; return l; }
            else return r;
        }

        pushTagDown(i, r-l);
        ui m = (l+r)/2;
        if (x < m) {
            return longestSuffixInner2(x, i << 1, l, (l + r) / 2, curValue, pred);
        } else {
            ui s = longestSuffixInner2(x, i << 1 | 1, (l + r) / 2, r, curValue, pred);
            if (s == (l + r) / 2) {
                return longestSuffixInner(i << 1, l, (l + r) / 2, curValue, pred);
            } else {
                return s;
            }
        }
    }

    /** Returns highest r such that pred(value[x,r]) returns true. The pred must be monotone!
     * If no prefix satisfies the condition, returns x-1 (i.e. empty interval).
     * If you want prefix of the whole array, use x == 0.
     *
     * BEWARE: If the whole array satisfies the condition, you will get n (which is power of two)
     * and NOT the actual size. */
    template <typename Pred> ui longestPrefix(ui x, Pred pred) {
        ValueType value = nullValue;
        return longestPrefixInner2(x, 1, 0, n, value, pred) - 1;
    }

    template <typename Pred> ui longestPrefixInner(ui i, ui l, ui r, ValueType &curValue, Pred pred) {
        if (l + 1 != r) pushTagDown(i, r-l);
        ValueType nextValue = combineValues(T[i].x, curValue);
        if (pred(nextValue)) { curValue = nextValue; return r; }
        if (l + 1 == r) return l;
        ui s = longestPrefixInner(i << 1, l, (l + r) / 2, curValue, pred);
        return s == (l + r) / 2 ? longestPrefixInner(i << 1 | 1, (l + r) / 2, r, curValue, pred) : s;
    }

    template <typename Pred> ui longestPrefixInner2(ui x, ui i, ui l, ui r, ValueType &curValue, Pred pred) {
        if (x <= l) {
            return longestPrefixInner(i, l, r, curValue, pred);
        }

        if (l + 1 == r) {
            ValueType nextValue = combineValues(T[i].x, curValue);
            if (pred(nextValue)) { curValue = nextValue; return r; }
            else return l;
        }

        pushTagDown(i, r-l);
        ui m = (l+r)/2;
        if (x >= m) {
            return longestPrefixInner2(x, i << 1 | 1, m, r, curValue, pred);
        } else {
            ui s = longestPrefixInner2(x, i << 1, l, m, curValue, pred);
            return s == m ? longestPrefixInner(i << 1 | 1, m, r, curValue, pred) : s;
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
template <typename F> F LMinOp(F a, F b) { return std::min(a, b); }
template <typename F> F LMaxOp(F a, F b) { return std::max(a, b); }
template <typename T> T LSumOp(T a, T b) { return a + b; }
template <typename T> void LAssignOp(T &a, T b) { if (b != 0) a = b; };
template <typename T> void LAssignOp2(T &a, T b, ui) { if (b != 0) a = b; };
template <typename T> void LAssignMultOp(T &a, T b, ui s) { if (b != 0) a = b*s; };

template<typename T> using LAddMaxTree = LSegTree<T, T, LAddOp<T>, LAddOp2<T>, LMaxOp<T>>;
template<typename T> using LAddMinTree = LSegTree<T, T, LAddOp<T>, LAddOp2<T>, LMinOp<T>>;

template<typename T> using AddSumTree = LSegTree<T, T, LAddOp<T>, LAddOp2<T>, LSumOp<T>>;
template<typename T> using AssignSumTree = LSegTree<T, T, LAssignOp<T>, LAssignMultOp<T>, LSumOp<T>>;
template<typename T> using AssignMaxTree = LSegTree<T, T, LAssignOp<T>, LAssignOp2<T>, LMaxOp<T>>;
template<typename T> using AssignMinTree = LSegTree<T, T, LAssignOp<T>, LAssignOp2<T>, LMinOp<T>>;
