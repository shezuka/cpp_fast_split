#include "explode.h"

#include <iostream>
#include <chrono>
#include <cstring>
#include <string>
#include <vector>
#include <sstream>
#include <iterator>

using namespace std;
using namespace std::chrono;

inline system_clock::time_point current_nanoseconds() {
    return high_resolution_clock::now();
}

template<typename T>
size_t duration_val(T v) {
    return static_cast<size_t>(duration_cast<nanoseconds>(v).count());
}

int main() {
    string base = "space split a simple string";
    const char *base_str = base.c_str();

    auto e = explode(base_str, " ", 3);
    for (size_t i = 0; i < e.size(); i++) {
        cout << e[i] << endl;
    }

    return 0;
}
