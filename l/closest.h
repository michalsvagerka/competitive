#ifndef MAJK_CLOSEST_H
#define MAJK_CLOSEST_H

// A divide and conquer program in C++ to find the smallest distance from a
// given set of points.

#include "geo.h"

template<typename T>
class Closest {

    T bruteForce(typename vector<Point<T>>::const_iterator Pxb, typename vector<Point<T>>::const_iterator Pxe) {
        T ans = numeric_limits<T>::max();
        for (auto i = Pxb; i != Pxe; ++i)
            for (auto j = next(i); j != Pxe; ++j)
                ans = min(ans, i->squaredDistance(*j));
        return ans;
    }

    T stripClosest(const vector<Point<T>> & strip, T d) {
        T ans = d;
        for (int i = 0; i < strip.size(); ++i)
            for (int j = i + 1; j < strip.size() && (strip[j].y - strip[i].y)*(strip[j].y - strip[i].y) < ans; ++j)
                ans = min(ans, strip[i].squaredDistance(strip[j]));
        return ans;
    }

    T closestUtil(typename vector<Point<T>>::const_iterator Pxb, typename vector<Point<T>>::const_iterator Pxe, vector<Point<T>> & Py) {
        int N = distance(Pxb, Pxe);
        if (N <= 3) return bruteForce(Pxb, Pxe);
        
        int mid = N / 2;
        Point<T> midPoint = Pxb[mid];

        vector<Point<T>> Pyl, Pyr;
        for (auto&p : Py) (p.x <= midPoint.x ? Pyl : Pyr).push_back(p);

        T dl = closestUtil(Pxb, Pxb + mid, Pyl);
        T dr = closestUtil(Pxb + mid, Pxe, Pyr);
        T d = min(dl, dr);

        vector<Point<T>> strip;
        int j = 0;
        for (auto &p: Py) {
            if ((p.x - midPoint.x)*(p.x - midPoint.x) < d) strip.push_back(p);
        }

        return min(d, stripClosest(strip, d));
    }

public:
    // Assumption: All x coordinates are distinct.
    T minSquareDist(const vector<Point<T>> &P) {
        vector<Point<T>> PX = P, PY = P;
        sort(PX.begin(),PX.end());
        sort(PY.begin(),PY.end(),[&](const Point<T>&a, const Point<T>&b) { return a.y < b.y; });
        return closestUtil(PX.begin(),PX.end(), PY);
    }

};

#endif //MAJK_CLOSEST_H
