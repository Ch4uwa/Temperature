#ifndef PCH_H
#define PCH_H
// Global includes
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <limits>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <map>
#include <unordered_map>


// Macros
#define STREAM_MAX std::numeric_limits<std::streamsize>::max()
#if 1
#define LOG(x) std::cout<<"> "<<x<<"\n"
#else
#define LOG(x)
#endif // 0


#endif //PCH_H
