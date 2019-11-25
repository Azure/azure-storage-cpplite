#pragma once

#include "storage_EXPORTS.h"

namespace azure {  namespace storage_lite {  namespace constants {

#define DAT(x, y) extern AZURE_STORAGE_API const char *x; const int x ## _size{ sizeof(y) / sizeof(char) - 1 };
#include "constants.dat"
#undef DAT

}}}  // azure::storage_lite::constants