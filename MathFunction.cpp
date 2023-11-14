﻿#include "MathFunction.h"

#include <assert.h>

#define _USE_MATH_DEFINES
#include <math.h>

// ベクトルの加法
Vector3 Add(const Vector3& v1, const Vector3& v2) {
	Vector3 result;
	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;
	return result;
}

// ベクトルの減法
Vector3 Subtract(const Vector3& v1, const Vector3 v2) {
	Vector3 result;
	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;
	return result;
}

// スカラー倍
Vector3 Multiply(const float& k, Vector3 v1) {
	Vector3 result;
	result.x = k * v1.x;
	result.y = k * v1.y;
	result.z = k * v1.z;
	return result;
}

// 内積
float Dot(const Vector3& v1, const Vector3& v2) {
	float result;
	result = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	return result;
}

// 長さ(ノルム)
float Length(const Vector3& v1) {
	float result;
	result = sqrtf(Dot(v1, v1));
	return result;
}

// 正規化
Vector3 Normalize(const Vector3& v1) {
	Vector3 result = { 0, 0, 0 };
	float length = Length(v1);
	if (length != 0.0f) {
		result.x = v1.x / length;
		result.y = v1.y / length;
		result.z = v1.z / length;
	}

	return result;
}

// ベクトル変換
Vector3 TransformNormal(const Vector3& v, const Matrix4x4& m) {
	Vector3 result{
		v.x * m.m[0][0] + v.y * m.m[1][0] + v.z * m.m[2][0],
		v.x * m.m[0][1] + v.y * m.m[1][1] + v.z * m.m[2][1],
		v.x * m.m[0][2] + v.y * m.m[1][2] + v.z * m.m[2][2] };

	return result;
}

// クロス積
Vector3 Cross(const Vector3& v1, const Vector3& v2) {
	Vector3 result;
	result.x = (v1.y * v2.z) - (v1.z * v2.y);
	result.y = (v1.z * v2.x) - (v1.x * v2.z);
	result.z = (v1.x * v2.y) - (v1.y * v2.x);

	return result;
}

Vector3 GetXAxis(const Matrix4x4& m)
{
	return Vector3(m.m[0][0], m.m[0][1], m.m[0][2]);
}

Vector3 GetYAxis(const Matrix4x4& m)
{
	return Vector3(m.m[1][0], m.m[1][1], m.m[1][2]);
}

Vector3 GetZAxis(const Matrix4x4& m)
{
	return Vector3(m.m[2][0], m.m[2][1], m.m[2][2]);
}

Vector3 Inverse(const Vector3& v)
{
	Vector3 result;

	result = Multiply(-1.0f, v);

	return result;
}

Matrix4x4 Add(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 result;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			result.m[i][j] = m1.m[i][j] + m2.m[i][j];
		}
	}

	return result;
}

Matrix4x4 Subtract(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 result;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			result.m[i][j] = m1.m[i][j] - m2.m[i][j];
		}
	}

	return result;
}

// 行列の積
Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 result;
	for (int line = 0; line < 4; line++) {
		for (int j = 0; j < 4; j++) {
			result.m[line][j] = 0;
		}
	}
	for (int line = 0; line < 4; line++) {
		for (int column = 0; column < 4; column++) {
			result.m[line][column] =
				m1.m[line][0] * m2.m[0][column] + m1.m[line][1] * m2.m[1][column] +
				m1.m[line][2] * m2.m[2][column] + m1.m[line][3] * m2.m[3][column];
		}
	}
	return result;
}

// 逆行列
Matrix4x4 Inverse(const Matrix4x4& m) {
	Matrix4x4 result;
	float A = m.m[0][0] * m.m[1][1] * m.m[2][2] * m.m[3][3] +
		m.m[0][0] * m.m[1][2] * m.m[2][3] * m.m[3][1] +
		m.m[0][0] * m.m[1][3] * m.m[2][1] * m.m[3][2] -

		m.m[0][0] * m.m[1][3] * m.m[2][2] * m.m[3][1] -
		m.m[0][0] * m.m[1][2] * m.m[2][1] * m.m[3][3] -
		m.m[0][0] * m.m[1][1] * m.m[2][3] * m.m[3][2] -

		m.m[0][1] * m.m[1][0] * m.m[2][2] * m.m[3][3] -
		m.m[0][2] * m.m[1][0] * m.m[2][3] * m.m[3][1] -
		m.m[0][3] * m.m[1][0] * m.m[2][1] * m.m[3][2] +

		m.m[0][3] * m.m[1][0] * m.m[2][2] * m.m[3][1] +
		m.m[0][2] * m.m[1][0] * m.m[2][1] * m.m[3][3] +
		m.m[0][1] * m.m[1][0] * m.m[2][3] * m.m[3][2] +

		m.m[0][1] * m.m[1][2] * m.m[2][0] * m.m[3][3] +
		m.m[0][2] * m.m[1][3] * m.m[2][0] * m.m[3][1] +
		m.m[0][3] * m.m[1][1] * m.m[2][0] * m.m[3][2] -

		m.m[0][3] * m.m[1][2] * m.m[2][0] * m.m[3][1] -
		m.m[0][2] * m.m[1][1] * m.m[2][0] * m.m[3][3] -
		m.m[0][1] * m.m[1][3] * m.m[2][0] * m.m[3][2] -

		m.m[0][1] * m.m[1][2] * m.m[2][3] * m.m[3][0] -
		m.m[0][2] * m.m[1][3] * m.m[2][1] * m.m[3][0] -
		m.m[0][3] * m.m[1][1] * m.m[2][2] * m.m[3][0] +

		m.m[0][3] * m.m[1][2] * m.m[2][1] * m.m[3][0] +
		m.m[0][2] * m.m[1][1] * m.m[2][3] * m.m[3][0] +
		m.m[0][1] * m.m[1][3] * m.m[2][2] * m.m[3][0];

	result.m[0][0] =
		(1 / A) * (m.m[1][1] * m.m[2][2] * m.m[3][3] + m.m[1][2] * m.m[2][3] * m.m[3][1] +
			m.m[1][3] * m.m[2][1] * m.m[3][2] - m.m[1][3] * m.m[2][2] * m.m[3][1] -
			m.m[1][2] * m.m[2][1] * m.m[3][3] - m.m[1][1] * m.m[2][3] * m.m[3][2]);
	result.m[0][1] =
		(1 / A) * (-m.m[0][1] * m.m[2][2] * m.m[3][3] - m.m[0][2] * m.m[2][3] * m.m[3][1] -
			m.m[0][3] * m.m[2][1] * m.m[3][2] + m.m[0][3] * m.m[2][2] * m.m[3][1] +
			m.m[0][2] * m.m[2][1] * m.m[3][3] + m.m[0][1] * m.m[2][3] * m.m[3][2]);
	result.m[0][2] =
		(1 / A) * (m.m[0][1] * m.m[1][2] * m.m[3][3] + m.m[0][2] * m.m[1][3] * m.m[3][1] +
			m.m[0][3] * m.m[1][1] * m.m[3][2] - m.m[0][3] * m.m[1][2] * m.m[3][1] -
			m.m[0][2] * m.m[1][1] * m.m[3][3] - m.m[0][1] * m.m[1][3] * m.m[3][2]);
	result.m[0][3] =
		(1 / A) * (-m.m[0][1] * m.m[1][2] * m.m[2][3] - m.m[0][2] * m.m[1][3] * m.m[2][1] -
			m.m[0][3] * m.m[1][1] * m.m[2][2] + m.m[0][3] * m.m[1][2] * m.m[2][1] +
			m.m[0][2] * m.m[1][1] * m.m[2][3] + m.m[0][1] * m.m[1][3] * m.m[2][2]);
	result.m[1][0] =
		(1 / A) * (-m.m[1][0] * m.m[2][2] * m.m[3][3] - m.m[1][2] * m.m[2][3] * m.m[3][0] -
			m.m[1][3] * m.m[2][0] * m.m[3][2] + m.m[1][3] * m.m[2][2] * m.m[3][0] +
			m.m[1][2] * m.m[2][0] * m.m[3][3] + m.m[1][0] * m.m[2][3] * m.m[3][2]);
	result.m[1][1] =
		(1 / A) * (m.m[0][0] * m.m[2][2] * m.m[3][3] + m.m[0][2] * m.m[2][3] * m.m[3][0] +
			m.m[0][3] * m.m[2][0] * m.m[3][2] - m.m[0][3] * m.m[2][2] * m.m[3][0] -
			m.m[0][2] * m.m[2][0] * m.m[3][3] - m.m[0][0] * m.m[2][3] * m.m[3][2]);
	result.m[1][2] =
		(1 / A) * (-m.m[0][0] * m.m[1][2] * m.m[3][3] - m.m[0][2] * m.m[1][3] * m.m[3][0] -
			m.m[0][3] * m.m[1][0] * m.m[3][2] + m.m[0][3] * m.m[1][2] * m.m[3][0] +
			m.m[0][2] * m.m[1][0] * m.m[3][3] + m.m[0][0] * m.m[1][3] * m.m[3][2]);
	result.m[1][3] =
		(1 / A) * (m.m[0][0] * m.m[1][2] * m.m[2][3] + m.m[0][2] * m.m[1][3] * m.m[2][0] +
			m.m[0][3] * m.m[1][0] * m.m[2][2] - m.m[0][3] * m.m[1][2] * m.m[2][0] -
			m.m[0][2] * m.m[1][0] * m.m[2][3] - m.m[0][0] * m.m[1][3] * m.m[2][2]);
	result.m[2][0] =
		(1 / A) * (m.m[1][0] * m.m[2][1] * m.m[3][3] + m.m[1][1] * m.m[2][3] * m.m[3][0] +
			m.m[1][3] * m.m[2][0] * m.m[3][1] - m.m[1][3] * m.m[2][1] * m.m[3][0] -
			m.m[1][1] * m.m[2][0] * m.m[3][3] - m.m[1][0] * m.m[2][3] * m.m[3][1]);
	result.m[2][1] =
		(1 / A) * (-m.m[0][0] * m.m[2][1] * m.m[3][3] - m.m[0][1] * m.m[2][3] * m.m[3][0] -
			m.m[0][3] * m.m[2][0] * m.m[3][1] + m.m[0][3] * m.m[2][1] * m.m[3][0] +
			m.m[0][1] * m.m[2][0] * m.m[3][3] + m.m[0][0] * m.m[2][3] * m.m[3][1]);
	result.m[2][2] =
		(1 / A) * (m.m[0][0] * m.m[1][1] * m.m[3][3] + m.m[0][1] * m.m[1][3] * m.m[3][0] +
			m.m[0][3] * m.m[1][0] * m.m[3][1] - m.m[0][3] * m.m[1][1] * m.m[3][0] -
			m.m[0][1] * m.m[1][0] * m.m[3][3] - m.m[0][0] * m.m[1][3] * m.m[3][1]);
	result.m[2][3] =
		(1 / A) * (-m.m[0][0] * m.m[1][1] * m.m[2][3] - m.m[0][1] * m.m[1][3] * m.m[2][0] -
			m.m[0][3] * m.m[1][0] * m.m[2][1] + m.m[0][3] * m.m[1][1] * m.m[2][0] +
			m.m[0][1] * m.m[1][0] * m.m[2][3] + m.m[0][0] * m.m[1][3] * m.m[2][1]);
	result.m[3][0] =
		(1 / A) * (-m.m[1][0] * m.m[2][1] * m.m[3][2] - m.m[1][1] * m.m[2][2] * m.m[3][0] -
			m.m[1][2] * m.m[2][0] * m.m[3][1] + m.m[1][2] * m.m[2][1] * m.m[3][0] +
			m.m[1][1] * m.m[2][0] * m.m[3][2] + m.m[1][0] * m.m[2][2] * m.m[3][1]);
	result.m[3][1] =
		(1 / A) * (m.m[0][0] * m.m[2][1] * m.m[3][2] + m.m[0][1] * m.m[2][2] * m.m[3][0] +
			m.m[0][2] * m.m[2][0] * m.m[3][1] - m.m[0][2] * m.m[2][1] * m.m[3][0] -
			m.m[0][1] * m.m[2][0] * m.m[3][2] - m.m[0][0] * m.m[2][2] * m.m[3][1]);
	result.m[3][2] =
		(1 / A) * (-m.m[0][0] * m.m[1][1] * m.m[3][2] - m.m[0][1] * m.m[1][2] * m.m[3][0] -
			m.m[0][2] * m.m[1][0] * m.m[3][1] + m.m[0][2] * m.m[1][1] * m.m[3][0] +
			m.m[0][1] * m.m[1][0] * m.m[3][2] + m.m[0][0] * m.m[1][2] * m.m[3][1]);
	result.m[3][3] =
		(1 / A) * (m.m[0][0] * m.m[1][1] * m.m[2][2] + m.m[0][1] * m.m[1][2] * m.m[2][0] +
			m.m[0][2] * m.m[1][0] * m.m[2][1] - m.m[0][2] * m.m[1][1] * m.m[2][0] -
			m.m[0][1] * m.m[1][0] * m.m[2][2] - m.m[0][0] * m.m[1][2] * m.m[2][1]);

	return result;
}

Matrix4x4 Transpose(const Matrix4x4& m) {
	Matrix4x4 result;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			result.m[i][j] = m.m[j][i];
		}
	}
	return result;
}

// 平行移動行列
Matrix4x4 MakeTranslateMatrix(const Vector3& translate) {
	Matrix4x4 result;
	for (int line = 0; line < 4; line++) {
		for (int column = 0; column < 4; column++) {
			if (line == column) {
				result.m[line][column] = 1;
			}
			else {
				result.m[line][column] = 0;
			}
		}
	}

	result.m[3][0] = translate.x;
	result.m[3][1] = translate.y;
	result.m[3][2] = translate.z;

	return result;
}

// 拡大縮小行列
Matrix4x4 MakeScaleMatrix(const Vector3& scale) {
	Matrix4x4 result;
	for (int line = 0; line < 4; line++) {
		for (int column = 0; column < 4; column++) {
			if (line == column) {
				result.m[line][column] = 1;
			}
			else {
				result.m[line][column] = 0;
			}
		}
	}

	result.m[0][0] = scale.x;
	result.m[1][1] = scale.y;
	result.m[2][2] = scale.z;

	return result;
}

// 座標変換
Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix) {
	Vector3 result;
	result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + vector.z * matrix.m[2][0] +
		1.0f * matrix.m[3][0];
	result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + vector.z * matrix.m[2][1] +
		1.0f * matrix.m[3][1];
	result.z = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + vector.z * matrix.m[2][2] +
		1.0f * matrix.m[3][2];
	float w = vector.x * matrix.m[0][3] + vector.y * matrix.m[1][3] + vector.z * matrix.m[2][3] +
		1.0f * matrix.m[3][3];
	assert(w != 0.0f);
	result.x /= w;
	result.y /= w;
	result.z /= w;
	return result;
}

// X軸回転行列
Matrix4x4 MakeRotateXMatrix(float radian) {
	Matrix4x4 result;
	for (int line = 0; line < 4; line++) {
		for (int column = 0; column < 4; column++) {
			if (line == column) {
				result.m[line][column] = 1;
			}
			else {
				result.m[line][column] = 0;
			}
		}
	}
	result.m[1][1] = std::cos(radian);
	result.m[1][2] = std::sin(radian);
	result.m[2][1] = -std::sin(radian);
	result.m[2][2] = std::cos(radian);
	return result;
}

// Y軸回転行列
Matrix4x4 MakeRotateYMatrix(float radian) {
	Matrix4x4 result;
	for (int line = 0; line < 4; line++) {
		for (int column = 0; column < 4; column++) {
			if (line == column) {
				result.m[line][column] = 1;
			}
			else {
				result.m[line][column] = 0;
			}
		}
	}
	result.m[0][0] = std::cos(radian);
	result.m[0][2] = -std::sin(radian);
	result.m[2][0] = std::sin(radian);
	result.m[2][2] = std::cos(radian);
	return result;
}

// Z軸回転行列
Matrix4x4 MakeRotateZMatrix(float radian) {
	Matrix4x4 result;
	for (int line = 0; line < 4; line++) {
		for (int column = 0; column < 4; column++) {
			if (line == column) {
				result.m[line][column] = 1;
			}
			else {
				result.m[line][column] = 0;
			}
		}
	}
	result.m[0][0] = std::cos(radian);
	result.m[0][1] = std::sin(radian);
	result.m[1][0] = -std::sin(radian);
	result.m[1][1] = std::cos(radian);
	return result;
}

Matrix4x4 MakeRotateXYZMatrix(const Vector3& rotation)
{
	Matrix4x4 result = MakeIdentity4x4();
	result = Multiply(result, MakeRotateXMatrix(rotation.x));
	result = Multiply(result, MakeRotateYMatrix(rotation.y));
	result = Multiply(result, MakeRotateZMatrix(rotation.z));
	return result;
}

// アフィン変換行列
Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rot, const Vector3& translate) {
	Matrix4x4 result;
	for (int line = 0; line < 4; line++) {
		for (int column = 0; column < 4; column++) {
			result.m[line][column] = 0;
		}
	}
	// スケーリング行列の作成
	Matrix4x4 scaleMatrix = MakeScaleMatrix(scale);

	// X軸周り回転行列の作成
	Matrix4x4 rotateX = MakeRotateXMatrix(rot.x);
	// Y軸周り回転行列の作成
	Matrix4x4 rotateY = MakeRotateYMatrix(rot.y);
	// Z軸周り回転行列の作成
	Matrix4x4 rotateZ = MakeRotateZMatrix(rot.z);
	// 回転行列の合成(Z回転 * X回転 * Y回転)
	Matrix4x4 rotateMatrix = Multiply(Multiply(rotateZ, rotateX), rotateY);

	// 平行移動行列の作成
	Matrix4x4 translateMatrix = MakeTranslateMatrix(translate);

	result = Multiply(Multiply(scaleMatrix, rotateMatrix), translateMatrix);
	return result;
}

Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Matrix4x4& rotateMatrix, const Vector3& translate)
{
	Matrix4x4 result;
	for (int line = 0; line < 4; line++) {
		for (int column = 0; column < 4; column++) {
			result.m[line][column] = 0;
		}
	}
	// スケーリング行列の作成
	Matrix4x4 scaleMatrix = MakeScaleMatrix(scale);

	// 平行移動行列の作成
	Matrix4x4 translateMatrix = MakeTranslateMatrix(translate);

	result = Multiply(Multiply(scaleMatrix, rotateMatrix), translateMatrix);
	return result;
}

// 単位行列の作成
Matrix4x4 MakeIdentity4x4() {
	Matrix4x4 result;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (i == j) {
				result.m[i][j] = 1;
			}
			else {
				result.m[i][j] = 0;
			}
		}
	}
	return result;
}

Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip) {
	Matrix4x4 result;
	for (int line = 0; line < 4; line++) {
		for (int column = 0; column < 4; column++) {
			result.m[line][column] = 0;
		}
	}

	result.m[0][0] = (1 / aspectRatio) * (1 / std::tan(fovY / 2.0f));
	result.m[1][1] = (1 / std::tan(fovY / 2.0f));
	result.m[2][2] = farClip / (farClip - nearClip);
	result.m[2][3] = 1;
	result.m[3][2] = (-nearClip * farClip) / (farClip - nearClip);
	return result;
}

Matrix4x4 MakeOrthographicMatrix(
	float left, float top, float right, float bottom, float nearClip, float farClip) {
	Matrix4x4 result;
	for (int line = 0; line < 4; line++) {
		for (int column = 0; column < 4; column++) {
			result.m[line][column] = 0;
		}
	}

	result.m[0][0] = 2 / (right - left);
	result.m[1][1] = 2 / (top - bottom);
	result.m[2][2] = 1 / (farClip - nearClip);
	result.m[3][3] = 1;
	result.m[3][0] = (left + right) / (left - right);
	result.m[3][1] = (top + bottom) / (bottom - top);
	result.m[3][2] = nearClip / (nearClip - farClip);

	return result;
}

Matrix4x4 MakeViewportMatrix(
	float left, float top, float width, float height, float minDepth, float maxDepth) {
	Matrix4x4 result;
	for (int line = 0; line < 4; line++) {
		for (int column = 0; column < 4; column++) {
			result.m[line][column] = 0;
		}
	}

	result.m[0][0] = width / 2.0f;
	result.m[1][1] = -height / 2.0f;
	result.m[2][2] = maxDepth - minDepth;
	result.m[3][3] = 1;
	result.m[3][0] = left + (width / 2.0f);
	result.m[3][1] = top + (height / 2.0f);
	result.m[3][2] = minDepth;

	return result;
}

Matrix4x4 MakeViewMatrix(const Vector3& rotate, const Vector3& translate)
{
	Matrix4x4 result;
	result = MakeAffineMatrix({ 1.0f, 1.0f, 1.0f }, rotate, translate);
	result = Inverse(result);
	return result;
}

Matrix4x4 DirectionToDirection(const Vector3& from, const Vector3& to)
{
	Matrix4x4 result = MakeIdentity4x4();
	Vector3 inverse = Inverse(from);
	Vector3 axis;
	if (to.x == inverse.x && to.y == inverse.y && to.z == inverse.z) {
		axis = { from.y, -from.x, 0.0f };
	}
	else {
		axis = Normalize(Cross(from, to));
	}

	// 回転角度を計算
	float cos = Dot(from, to);
	float sin = Length(Cross(from, to));
	float oneMinusCos = 1.0f - cos;

	result.m[0][0] = cos + std::powf(axis.x, 2) * oneMinusCos;
	result.m[1][0] = axis.x * axis.y * oneMinusCos - axis.z * sin;
	result.m[2][0] = axis.x * axis.z * oneMinusCos + axis.y * sin;

	result.m[0][1] = axis.y * axis.x * oneMinusCos + axis.z * sin;
	result.m[1][1] = cos + std::powf(axis.y, 2) * oneMinusCos;
	result.m[2][1] = axis.y * axis.z * oneMinusCos - axis.x * sin;

	result.m[0][2] = axis.z * axis.x * oneMinusCos - axis.y * sin;
	result.m[1][2] = axis.z * axis.y * oneMinusCos + axis.x * sin;
	result.m[2][2] = cos + std::powf(axis.z, 2) * oneMinusCos;

	return result;


}

Matrix4x4 MakeRotateAxisAngle(const Vector3& axis, float angle)
{
	Matrix4x4 result = MakeIdentity4x4();
	result.m[0][0] = (axis.x * axis.x) * (1 - std::cosf(angle)) + std::cosf(angle);
	result.m[0][1] = (axis.x * axis.y) * (1.0f - std::cosf(angle)) + axis.z * std::sinf(angle);
	result.m[0][2] = (axis.x * axis.z) * (1.0f - std::cosf(angle)) - axis.y * std::sinf(angle);
	result.m[1][0] = (axis.x * axis.y) * (1.0f - std::cosf(angle)) - axis.z * std::sinf(angle);
	result.m[1][1] = (axis.y * axis.y) * (1.0f - std::cosf(angle)) + std::cosf(angle);
	result.m[1][2] = (axis.y * axis.z) * (1.0f - std::cosf(angle)) + axis.x * std::sinf(angle);
	result.m[2][0] = (axis.x * axis.z) * (1.0f - std::cosf(angle)) + axis.y * std::sinf(angle);
	result.m[2][1] = (axis.y * axis.z) * (1.0f - std::cosf(angle)) - axis.x * std::sinf(angle);
	result.m[2][2] = (axis.z * axis.z) * (1.0f - std::cosf(angle)) + std::cosf(angle);
	return result;
}

// 正射影ベクトル
Vector3 Project(const Vector3& v1, const Vector3& v2) {
	Vector3 result;
	float t = Dot(v1, v2) / (Length(v2) * Length(v2));
	result = Multiply(t, v2);
	return result;
}

float ConvertToRadians(float degree)
{
	float result = degree * float(M_PI) / 180.0f;
	return result;
}

float LerpShortAngle(float a, float b, float t) {
	// 角度差分を求める
	float diff = b - a;

	diff = std::fmodf(diff, float(M_PI));

	if (diff > M_PI) {
		diff = diff - float(M_PI);
	}
	else if (diff < -M_PI) {
		diff = diff + float(M_PI);

	}

	return a + diff * t;
}

Vector3 Lerp(const Vector3& v1, const Vector3& v2, float t) {
	Vector3 result = Add(v1, Multiply(t, Subtract(v2, v1)));
	return result;
}

Vector3 Slerp(const Vector3& v1, const Vector3& v2, float t) {
	float s = ((1 - t) * Length(v1)) + (t * Length(v2));
	Vector3 e1 = Normalize(v1);
	Vector3 e2 = Normalize(v2);
	float an = std::acosf(Dot(v1, v2) * (1.0f / (Length(v1) * Length(v2))));
	if (an > 0.0f || an < 180.0f) {
		Vector3 v1e = Multiply(std::sinf((1 - t) * an) / std::sinf(an), e1);
		Vector3 v2e = Multiply(std::sinf(t * an) / std::sinf(an), e2);
		Vector3 result = Multiply(s, Add(v1e, v2e));
		return result;
	}
	return v1;
}

Quaternion IndentityQuaternion()
{
	Quaternion result = { 0.0f, 0.0f, 0.0f, 1.0f };

	return result;
}

Quaternion Conjugate(const Quaternion& q)
{
	Quaternion result = { -q.x, -q.y, -q.z, q.w };

	return result;
}

Quaternion Inverse(const Quaternion& q)
{
	Quaternion result;
	Quaternion conj = Conjugate(q);
	float norm = Norm(q);
	norm = std::powf(norm, 2);
	result = { conj.x / norm, conj.y / norm, conj.z / norm, conj.w / norm };

	return result;
}

Quaternion Normalize(const Quaternion& q)
{
	Quaternion result;
	float norm = Norm(q);
	result = { q.x / norm, q.y / norm, q.z / norm, q.w / norm };

	return result;
}

Quaternion Multiply(const Quaternion& q, const Quaternion& r)
{
	Quaternion result;
	Vector3 qxr = Cross({ q.x, q.y, q.z }, { r.x, r.y, r.z });
	Vector3 rq = Multiply(r.w, { q.x, q.y, q.z });
	Vector3 qr = Multiply(q.w, { r.x, r.y, r.z });
	result.w = (q.w * r.w) - Dot(Vector3{ q.x, q.y, q.z }, Vector3{ r.x, r.y, r.z });
	result.x = qxr.x + rq.x + qr.x;
	result.y = qxr.y + rq.y + qr.y;
	result.z = qxr.z + rq.z + qr.z;

	return result;
}

float Norm(const Quaternion& q)
{
	float result;
	float w2 = std::powf(q.w, 2);
	float x2 = std::powf(q.x, 2);
	float y2 = std::powf(q.y, 2);
	float z2 = std::powf(q.z, 2);
	result = sqrtf(w2 + x2 + y2 + z2);
	return result;
}

Quaternion MakeRotateAxisAngleQuaternion(const Vector3& axis, float angle)
{
	Quaternion result;
	result.w = std::cosf(angle / 2.0f);
	result.x = axis.x * std::sinf(angle / 2.0f);
	result.y = axis.y * std::sinf(angle / 2.0f);
	result.z = axis.z * std::sinf(angle / 2.0f);
	return result;
}

Vector3 RotateVector(const Vector3& vector, const Quaternion& q)
{

	Vector3 result;
	Quaternion r = { vector.x, vector.y, vector.z, 0.0f };
	Quaternion conj = Conjugate(q);
	r = Multiply(Multiply(q, r), conj);
	result.x = r.x;
	result.y = r.y;
	result.z = r.z;
	return result;
}

Matrix4x4 MakeRotateMatrix(const Quaternion& q)
{
	Matrix4x4 result = MakeIdentity4x4();
	
	result.m[0][0] = std::powf(q.w, 2) + std::powf(q.x, 2) - std::powf(q.y, 2) - std::powf(q.z, 2);
	result.m[0][1] = 2.0f * ((q.x * q.y) + (q.w * q.z));
	result.m[0][2] = 2.0f * ((q.x * q.z) - (q.w * q.y));
	result.m[1][0] = 2.0f * ((q.x * q.y) - (q.w * q.z));
	result.m[1][1] = std::powf(q.w, 2) - std::powf(q.x, 2) + std::powf(q.y, 2) - std::powf(q.z, 2);
	result.m[1][2] = 2.0f * ((q.y * q.z) + (q.w * q.x));
	result.m[2][0] = 2.0f * ((q.x * q.z) + (q.w * q.y));
	result.m[2][1] = 2.0f * ((q.y * q.z) - (q.w * q.x));
	result.m[2][2] = std::powf(q.w, 2) - std::powf(q.x, 2) - std::powf(q.y, 2) + std::powf(q.z, 2);

	return result;
}

Quaternion Slerp(const Quaternion& q0, const Quaternion& q1, float t)
{
	Quaternion result;
	float dot = Dot(q0, q1);
	float theta = 0.0f;
	if (dot < 0) {
		dot = -dot;
		theta = std::acosf(dot);
		result.w = (std::sinf((1.0f - t) * theta) / std::sinf(theta)) * -q0.w + (std::sinf(t * theta) / std::sinf(theta)) * q1.w;
		result.x = (std::sinf((1.0f - t) * theta) / std::sinf(theta)) * -q0.x + (std::sinf(t * theta) / std::sinf(theta)) * q1.x;
		result.y = (std::sinf((1.0f - t) * theta) / std::sinf(theta)) * -q0.y + (std::sinf(t * theta) / std::sinf(theta)) * q1.y;
		result.z = (std::sinf((1.0f - t) * theta) / std::sinf(theta)) * -q0.z + (std::sinf(t * theta) / std::sinf(theta)) * q1.z;
	}
	else {
		theta = std::acosf(dot);
		result.w = (std::sinf((1.0f - t) * theta) / std::sinf(theta)) * q0.w + (std::sinf(t * theta) / std::sinf(theta)) * q1.w;
		result.x = (std::sinf((1.0f - t) * theta) / std::sinf(theta)) * q0.x + (std::sinf(t * theta) / std::sinf(theta)) * q1.x;
		result.y = (std::sinf((1.0f - t) * theta) / std::sinf(theta)) * q0.y + (std::sinf(t * theta) / std::sinf(theta)) * q1.y;
		result.z = (std::sinf((1.0f - t) * theta) / std::sinf(theta)) * q0.z + (std::sinf(t * theta) / std::sinf(theta)) * q1.z;
	}
	return result;
}

float Dot(const Quaternion& q1, const Quaternion& q2)
{
	float result = (q1.x * q2.x) + (q1.y * q2.y) + (q1.z * q2.z) + (q1.w * q2.w);
	return result;
}

// 最近接点
// Vector3 ClosestPoint(const Vector3& point, const Segment& segment)
//{
//	Vector3 result;
//	result = Add(segment.origin, Project(Subtract(point, segment.origin), segment.diff));
//	ret