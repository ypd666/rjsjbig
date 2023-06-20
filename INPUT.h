#ifndef INPUT_H
#define INPUT_H
#include <cstring>
#include <fstream>
    class INPUT {

    std::istream* st;

public:
    INPUT() = default;
    INPUT(std::istream& in) : st(&in) {}
    INPUT& operator=(std::istream& str) {
        st = &str;
        return *this;
    }
    explicit operator bool() {
        return st->good();
    }
    template <typename T>
    friend INPUT& operator>>(INPUT& in, const T& t) {
        *in.st >> t;
        return in;
    }
    friend void getline(INPUT& in, std::string& s) {
        std::getline(*in.st, s);
    }
};

#endif
