#ifndef FAST_SPLIT_SPLITTER_H
#define FAST_SPLIT_SPLITTER_H

#include <cstring>
#include <string>

class exploder {
    static const size_t _npos;

    static size_t allocate(char ***source,
                           size_t used_size,
                           size_t current_size,
                           size_t requested_size);

private:
    char *_source;
    const char *_delim;

    const size_t _source_len;
    const size_t _delim_len;

    char **_result = nullptr;
    size_t _result_len = 0;

    void process();

public:
    explicit exploder(const char *source, size_t source_len,
                      const char *delim, size_t delim_len);

    ~exploder();

    const char *operator[](int index) const;

    size_t size() const;

    friend exploder explode(const char *source, const char *delim);
};

#endif //FAST_SPLIT_SPLITTER_H
