#ifdef _WIN32
#include <io.h>
#define access _access_s
#else
#include <unistd.h>
#endif
#include "fmt/include/fmt/core.h"
#include "fmt/include/fmt/format.h"
#include "fmt/include/fmt/format-inl.h"
#include "fmt/include/fmt/color.h"
#include "fmt/src/format.cc"
