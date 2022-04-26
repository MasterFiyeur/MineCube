//
// Created by Arthur on 05/03/2022.
//

#pragma once

#include <string>
#include <sys/stat.h>
#include <math.h>
#include <iostream>

static bool file_exists(const std::string& name) {
    struct stat buffer{};
    return (stat (name.c_str(), &buffer) == 0);
}

static Vector3 normalize(Vector3 v) {
    float length = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
    return { v.x / length, v.y / length, v.z / length };
}

static float norm(Vector3 v) {
    return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

static float dotProduct(Vector3 v1, Vector3 v2) {
    float result = (v1.x*v2.x + v1.y*v2.y + v1.z*v2.z);
    return result;
}

static Vector3 crossProduct(Vector3 v1, Vector3 v2) {
    float x = v1.y * v2.z - v1.z * v2.y;
    float y = v1.z * v2.x - v1.x * v2.z;
    float z = v1.x * v2.y - v1.y * v2.x;
    return { x, y, z };
}

static std::string Vector3toChar(Vector3 v) {
    char res[50];
    snprintf(res, sizeof res, "%.1f,%.1f,%.1f", v.x, v.y, v.z);
    return res;
}

static std::ostream& operator<<(std::ostream& out, const Vector3& v) {
    out << "(" << Vector3toChar(v) << ")";
    return out;
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

static Vector3 operator*(const Vector3& o1, const int v) {
    return (Vector3) {o1.x*v, o1.y*v, o1.z*v};
}