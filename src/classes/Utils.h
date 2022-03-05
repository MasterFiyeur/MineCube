//
// Created by Arthur on 05/03/2022.
//

#include <string>
#include <sys/stat.h>

inline bool file_exists(const std::string& name) {
    struct stat buffer{};
    return (stat (name.c_str(), &buffer) == 0);
}