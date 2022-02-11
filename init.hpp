#include <stdio.h>
#include <filesystem>
#include <utility>
#include <vector>
#include <string>
#include <map>
using std::map;
using std::min;
using std::pair;
using std::stoul;
using std::string;
using std::vector;
using std::to_string;
using std::runtime_error;
using std::filesystem::path;
namespace fs = std::filesystem;

bool inRange(int value, int low, int high) {
    return value >= low && value <= high;
}