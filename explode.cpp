#include "explode.h"

exploder explode(const char *source, const char *delim) {
    exploder r(source, std::strlen(source),
               delim, std::strlen(delim));
    r.process();
    return r;
}
