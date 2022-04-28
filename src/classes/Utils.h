//
// Created by Arthur on 05/03/2022.
//

#pragma once

#include <string>
#include <sys/stat.h>
#include <cmath>
#include <iostream>

#define DAY_LENGTH 20
#define DAY_LENGTH_D (double) DAY_LENGTH
#define HOUR_LENGTH 24.0f / DAY_LENGTH

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

static Color floatToColor(const float f[4]) {
    return {(unsigned char) (f[0]*255), (unsigned char) (f[1]*255), (unsigned char) (f[2]*255), (unsigned char) (f[3]*255)};
}

static void colorToFloat(const Color c, float* f) {
    f[0] = (float) c.r / 255.0f;
    f[1] = (float) c.g / 255.0f;
    f[2] = (float) c.b / 255.0f;
    f[3] = (float) c.a / 255.0f;
}
