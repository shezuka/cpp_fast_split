#include <exploder.h>

const size_t exploder::_npos = static_cast<size_t >(0) - 1;

size_t exploder::allocate(char ***source,
                          size_t used_size,
                          size_t current_size,
                          size_t requested_size) {
    // no memory allocation required
    if (current_size != 0 && used_size < current_size) return current_size;

    if (*source == nullptr) *source = new char *[requested_size];
    if (used_size == 0) return requested_size;

    if (current_size > requested_size || current_size < requested_size) {
        size_t cycle_limit = current_size > requested_size
                             ? requested_size
                             : current_size;

        char **source_pointers = *source;
        char **new_pointers = new char *[requested_size];
        for (size_t i = 0; i < cycle_limit; i++)
            new_pointers[i] = source_pointers[i];
        delete[]source_pointers;
        *source = new_pointers;
    }

    return requested_size;
}

exploder::exploder(const char *source, size_t source_len,
                   const char *delim, size_t delim_len,
                   const size_t limit)
        : _source_len(source_len), _delim_len(delim_len), _limit(limit) {
    _source = new char[source_len + 1];
    strcpy(_source, source);

    _delim = new char[delim_len + 1];
    strcpy(const_cast<char *>(_delim), delim);
}

exploder::~exploder() {
    delete[]_source;
    delete[]_delim;
    delete[]_result;
}

bool exploder::is_limited() const {
    if (_limit == 0) return false;

    return _limit == (_result_len + 1);
}

void exploder::process() {
    size_t str_pos = 0;
    size_t delim_start_pos = _npos;
    size_t start = 0;
    size_t allocated_size = 0;

    while (str_pos < _source_len) {
        for (size_t i = 0; i < _delim_len; i++) {
            if (_delim[i] != _source[i + str_pos])
                break;

            if (i + 1 == _delim_len)
                delim_start_pos = str_pos;
        }

        if (is_limited() || (str_pos + 1) == _source_len) {
            allocate(&_result, _result_len, allocated_size, _result_len + 1);
            _result[_result_len++] = _source + start;
            break;
        } else if ((delim_start_pos != _npos) || (str_pos + 1 == _source_len && start < str_pos)) {
            if (start != delim_start_pos) {
                allocated_size = allocate(&_result, _result_len, allocated_size, allocated_size + 10);
                _source[delim_start_pos] = '\0';
                _result[_result_len++] = _source + start;
                start = delim_start_pos + _delim_len;
            }

            delim_start_pos = _npos;
        }

        str_pos++;
    }

    allocate(&_result, _result_len, allocated_size, _result_len);
}

const char *exploder::operator[](int index) const {
    return _result[index];
}

size_t exploder::size() const {
    return _result_len;
}
