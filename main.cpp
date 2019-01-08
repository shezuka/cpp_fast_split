#include <iostream>
#include <cstring>
#include <string>
#include <chrono>
#include <sstream>
#include <vector>
#include <iterator>
#include <fstream>

using namespace std::chrono;

inline auto current_millis() {
    return std::chrono::high_resolution_clock::now();
}

template<typename T>
inline size_t time_res(T val) {
    return duration_cast<nanoseconds>(val).count();
}

inline
size_t reserve(char ***source, const size_t needed_size, const size_t current_size, const size_t current_used_size) {
    if (*source == nullptr) {
        *source = new char *[needed_size];
        return needed_size;
    }

    if (current_used_size == current_size && current_size < needed_size) {
        char **tmp = *source;
        *source = new char *[needed_size];
        for (size_t i = 0; i < current_size; i++)
            *(*source + i) = *(tmp + i);
        delete[]tmp;
    }

    return needed_size;
}

size_t fast_split(char ***result, const char *_source, const char *delim) {
    static auto npos = static_cast<size_t>(0) - 1;

    size_t size = 0;
    size_t start = 0;
    size_t str_pos = 0;
    size_t delim_start_pos = npos;
    size_t reserved_size = 10;

    if (*result != nullptr) {
        delete[] *result;
        *result = nullptr;
    }

    reserved_size = reserve(result, reserved_size, size, size);

    const auto source_len = strlen(_source);
    const auto delim_len = strlen(delim);

    char *source = new char[source_len + 1];
    strcpy(source, _source);

    while (str_pos < source_len) {
        for (size_t i = 0; i < delim_len && (str_pos + i) < source_len; i++) {
            if (source[str_pos + i] != delim[i])
                break;

            if (i + 1 == delim_len)
                delim_start_pos = str_pos;
        }

        if (delim_start_pos != npos) {
            source[delim_start_pos] = '\0';

            reserved_size = reserve(result, reserved_size + 10, reserved_size, size++);
            *(*result + size - 1) = (source + start);

            start = delim_start_pos + delim_len;
            str_pos = start;
            delim_start_pos = npos;
        }

        str_pos++;
    }

    reserve(result, size + 1, reserved_size, size);
    *(*result + (size++)) = (source + start);

    return size;
}

#define TEST_FUNCTION_SPEED(CYCLES, MSG, FUNC, ...) \
{\
    size_t accum = 0;\
    std::cout << MSG << std::endl;\
    for (size_t i = 0; i < CYCLES; i++) {\
        auto start = current_millis();\
        FUNC(__VA_ARGS__);\
        accum += time_res(current_millis() - start);\
    }\
    std::cout << "Cycles: " << CYCLES << "\r\nAVG Time " << (accum / CYCLES) << " nanoseconds\r\n\r\n";\
}

void test_stl_lib(const std::string &base) {
    std::istringstream iss(base);

    auto start = current_millis();
    std::vector<std::string> results(std::istream_iterator<std::string>{iss},
                                     std::istream_iterator<std::string>());
}

int main() {
    const static size_t test_count = 10000000;

    std::string base;

    char **result = nullptr;

    base = "L a";
    std::cout << "SPLITTING STRING BY SPACES: \"" << base << "\"\r\n";
    TEST_FUNCTION_SPEED(test_count, "Working with memory directly", fast_split, &result, base.c_str(), " ");
    TEST_FUNCTION_SPEED(test_count, "Working with C++17 STL library", test_stl_lib, base);

    std::cout << "==========================\r\n\r\n";
    base = "Splitting another string with spaces\r\nAnd with new lines";
    std::cout << "SPLITTING STRING BY SPACES: \"" << base << "\"\r\n";
    TEST_FUNCTION_SPEED(test_count, "Working with memory directly", fast_split, &result, base.c_str(), " ");
    TEST_FUNCTION_SPEED(test_count, "Working with C++17 STL library", test_stl_lib, base);

    return 0;
}
