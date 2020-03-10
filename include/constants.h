#pragma once

#include "storage_EXPORTS.h"

namespace azure {  namespace storage_lite {  namespace constants {

#define DAT(x, y) extern AZURE_STORAGE_API const char *x; const int x ## _size{ sizeof(y) / sizeof(char) - 1 };
#define DAT_TYPED(type, name, value) extern AZURE_STORAGE_API const type name;
#include "constants.dat"
#undef DAT
#undef DAT_TYPED

}}}  // azure::storage_lite::constants
