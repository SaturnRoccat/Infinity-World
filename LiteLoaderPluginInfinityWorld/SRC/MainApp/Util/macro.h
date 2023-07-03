#pragma once
#ifdef NDEBUG
#define DEBUG_ONLY_CODE(code)
#else
#define DEBUG_ONLY_CODE(code) code
#endif