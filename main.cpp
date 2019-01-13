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

template<typename Func, typename ...Args>
void test(const size_t test_count, Func func, Args ...args) {
    size_t avg = 0;
    for (size_t i = 0; i < test_count; i++) {
        auto start = current_nanoseconds();
        func(args...);
        avg += duration_val(current_nanoseconds() - start);
    }
    avg /= test_count;

    cout << "Test iterations: " << test_count << endl;
    cout << "AVG Time: " << avg << "ns" << endl
         << endl << endl;
}

vector<string> stl_explode(const string &source) {
    istringstream iss(source);
    return vector<string>(istream_iterator<string>(iss), istream_iterator<string>());
}

int main() {
    const size_t test_count = 10000;

//    string base = "space split a simple string";
    string base = "space split a simple string space split a simple string space split a simple string space split a simple string space split a simple string ";
    const char *base_str = base.c_str();

    test(test_count, explode, base_str, " ", 3);
    test(test_count, stl_explode, base);

    return 0;
}
