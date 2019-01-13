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

    const size_t _limit;

    char **_result = nullptr;
    size_t _result_len = 0;

    bool is_limited() const;

    void process();

public:
    explicit exploder(const char *source, size_t source_len,
                      const char *delim, size_t delim_len,
                      const size_t limit = 0);

    ~exploder();

    const char *operator[](int index) const;

    size_t size() const;

    friend exploder explode(const char *source, const char *delim, const size_t limit);
};

#endif //FAST_SPLIT_SPLITTER_H
