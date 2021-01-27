#include <iostream>
#include <string>

std::pair<size_t, size_t> FindVowels(const std::string& text, size_t pos) {
    size_t cnt = 0;
    size_t n = text.size();
    size_t start = -1;
    bool conseq = false;
    for (size_t i = pos; i < n; ++i) {
        if (tolower(text[i]) == 'a' || tolower(text[i]) == 'e' || tolower(text[i]) == 'i'
            || tolower(text[i]) == 'o' || tolower(text[i]) == 'y' || tolower(text[i]) == 'u') {
            if (start == std::string::npos) {
                start = (i);
            }
            conseq = true;
            ++cnt;
        } else if (conseq) {
            return {start, cnt};
        }
    }
    return {start, cnt};
}
