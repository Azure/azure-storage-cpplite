#include "constants.h"

namespace azure {  namespace storage_lite {  namespace constants {

#define DAT(x, y) const char *x{ y };
#define DAT_TYPED(type, name, value) const type name{value};
#include "constants.dat"
#undef DAT
#undef DAT_TYPED

}}}  // azure::storage_lite
