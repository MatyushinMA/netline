#ifndef NETLINE_UTILS_MEDIAN_CPP
#define NETLINE_UTILS_MEDIAN_CPP

#include <vector>
#include <algorithm>

template<typename T>
constexpr T median(std::vector<T> v) {
    std::sort(v.begin(), v.end(), std::less<T>());
    if (v.size() % 2 == 0) {
        return (v[v.size()/2 - 1] + v[v.size()/2])/2;
    }
    else {
        return v[v.size()/2];
    }
}

#endif // NETLINE_UTILS_MEDIAN_CPP
