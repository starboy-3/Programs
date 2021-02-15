#include<algorithm>

template<typename It, typename OutputIt>
OutputIt SidewaysMerge(It first1, It last1, It first2, It last2, OutputIt out) {
    if (last2 == first2 && last1 == first1) {
        return out;
    } else if (last2 == first2) {
        return std::copy(first1, last1, out);
    } else if (last1 == first1) {
        while (first2 != last2) {
            *out++ = *--last2;
        }
        return out;
    }
    --last2;
    --first2;
    while (first1 != last1 || first2 != last2) {
        if (first1 == last1) {
            while (first2 != last2) {
                *out++ = *last2--;
            }
            return out;
        } else if (first2 == last2) {
            while (first1 != last1) {
                *out++ = *first1++;
            }
            return out;
        }
        if (*first1 < *last2) {
            *out++ = *first1++;
        } else if (*first1 > *last2) {
            *out++ = *last2--;
        } else {
            *out++ = *first1++;
            *out++ = *last2--;
        }
    }
    return out;
}
