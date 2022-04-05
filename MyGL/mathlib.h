#pragma once
#ifndef _MATH_LIB_H_
#define _MATH_LIB_H_
//#include "math.h"
#include "glm/glm.hpp"
#include "glm/vec3.hpp"
#include "glm/vec2.hpp"
#include "glm/vec4.hpp"
#include "glm/mat2x2.hpp"
#include "glm/mat2x3.hpp"
#include "glm/mat2x4.hpp"
#include "glm/mat3x2.hpp"
#include "glm/mat3x3.hpp"
#include "glm/mat3x4.hpp"
#include "glm/mat4x2.hpp"
#include "glm/mat4x3.hpp"
#include "glm/mat4x4.hpp"
#include "glm/common.hpp"
#include "glm/exponential.hpp"
#include "glm/integer.hpp"
#include "glm/matrix.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/quaternion.hpp"
using namespace glm;


typedef glm::vec3 Vector3;
typedef glm::vec4 Vector4;
typedef glm::mat4 Matrix4x4;

const Vector3 VEC3_FORWARD = glm::vec3(0,0,-1);
const Vector3 VEC3_BACK = glm::vec3(0, 0, 1);
const Vector3 VEC3_UP = glm::vec3(0, 1, 0);
const Vector3 VEC3_DOWN = glm::vec3(0, -1, 0);
const Vector3 VEC3_RIGHT = glm::vec3(1, 0, 0);
const Vector3 VEC3_LEFT = glm::vec3(-1, 0, 0);
const Vector3 VEC3_ONE = glm::vec3(1, 1, 1);
const Vector3 VEC3_ZERO = glm::vec3(0, 0, 0);
const Vector4 VEC4_POINT = glm::vec4(0,0,0,1);
const Matrix4x4 MAT4_IDENTITY = glm::mat4(1);

#endif // !_MATH_LIB_H_
