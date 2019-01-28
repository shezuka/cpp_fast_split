#include <explode.h>

exploder explode(const char *source, const char *delim, const size_t limit) {
    exploder r(source, std::strlen(source),
               delim, std::strlen(delim),
               limit);
    r.process();
    return r;
}
