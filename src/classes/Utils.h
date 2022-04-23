//
// Created by Arthur on 05/03/2022.
//

#pragma once

#include <string>
#include <sys/stat.h>
#include <math.h>

static bool file_exists(const std::string& name) {
    struct stat buffer{};
    return (stat (name.c_str(), &buffer) == 0);
}

static Vector3 normalize(Vector3 v) {
    float length = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
    return { v.x / length, v.y / length, v.z / length };
}

static bool operator<(const Vector3& o1, const Vector3 o2) {
    if (o1.x != o2.x) return o1.x < o2.x;
    if (o1.y != o2.y) return o1.y < o2.y;
    return o1.z < o2.z;
}

static bool operator==(const Vector3& o1, const Vector3 o2) {
    return o1.x == o2.x && o1.y == o2.y && o1.z == o2.z;
}

static Vector3 operator+(const Vector3& o1, const Vector3 o2) {
    return (Vector3) {o1.x + o2.x, o1.y + o2.y, o1.z + o2.z};
}

static Vector3 operator-(const Vector3& o1, const Vector3 o2) {
    return (Vector3) {o1.x - o2.x, o1.y - o2.y, o1.z - o2.z};
}