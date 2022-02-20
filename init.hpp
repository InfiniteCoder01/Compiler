#include <stdio.h>
#include <filesystem>
#include <algorithm>
#include <utility>
#include <format>
#include <vector>
#include <string>
#include <map>
using std::map;
using std::min;
using std::pair;
using std::stoul;
using std::format;
using std::string;
using std::remove;
using std::vector;
using std::to_string;
using std::make_pair;
using std::runtime_error;
using Path = std::filesystem::path;
namespace fs = std::filesystem;

inline bool inRange(int value, int low, int high) {
    return value >= low && value <= high;
}