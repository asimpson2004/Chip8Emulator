#include "Matrix4x4.h"
#include "Vector2.h"
#include "Vector3.h"
#include <math.h>
#include "MathHelpers.h"

Matrix4x4::Matrix4x4()
{
	Identity();
}

Matrix4x4::~Matrix4x4()
{

}

void Matrix4x4::Translate(Vector3& translation)
{
	m_MatrixData[0][3] += translation.x;
	m_MatrixData[1][3] += translation.y;
	m_MatrixData[2][3] += translation.z;
}

void Matrix4x4::SetTranslation(Vector3& translation)
{
	m_MatrixData[0][3] = translation.x;
	m_MatrixData[1][3] = translation.y;
	m_MatrixData[2][3] = translation.z;
}

void Matrix4x4::Translate(Vector2& translation)
{
	m_MatrixData[0][3] += translation.x;
	m_MatrixData[1][3] += translation.y;
}

void Matrix4x4::SetTranslation(Vector2& translation)
{
	m_MatrixData[0][3] = translation.x;
	m_MatrixData[1][3] = translation.y;
}

void Matrix4x4::RotateX(float rotation)
{
	float radians = rotation * DEGTORAD;
	m_MatrixData[1][1] += cosf(radians);
	m_MatrixData[1][2] += -sinf(radians);
	m_MatrixData[2][1] += sinf(radians);
	m_MatrixData[2][2] += cosf(radians);
}

void Matrix4x4::SetRotationX(float rotation)
{
	float radians = rotation * DEGTORAD;

	m_MatrixData[1][1] = cosf(radians);
	m_MatrixData[1][2] = -sinf(radians);
	m_MatrixData[2][1] = sinf(radians);
	m_MatrixData[2][2] = cosf(radians);
}

void Matrix4x4::RotateY(float rotation)
{
	float radians = rotation * DEGTORAD;

	m_MatrixData[0][0] += cosf(radians);
	m_MatrixData[0][2] += sinf(radians);
	m_MatrixData[2][0] += -sinf(radians);
	m_MatrixData[2][2] += cosf(radians);
}

void Matrix4x4::SetRotationY(float rotation)
{
	float radians = rotation * DEGTORAD;

	m_MatrixData[0][0] = cosf(radians);
	m_MatrixData[0][2] = sinf(radians);
	m_MatrixData[2][0] = -sinf(radians);
	m_MatrixData[2][2] = cosf(radians);
}


void Matrix4x4::RotateZ(float rotation)
{
	Matrix4x4 temp;
	temp.SetRotationZ(rotation);
	m_MatrixData[0][0] += temp.m_MatrixData[0][0]; m_MatrixData[0][1] += temp.m_MatrixData[0][1]; m_MatrixData[0][2] += temp.m_MatrixData[0][2]; m_MatrixData[0][3] += temp.m_MatrixData[0][3];
	m_MatrixData[1][0] += temp.m_MatrixData[1][0]; m_MatrixData[1][1] += temp.m_MatrixData[1][1]; m_MatrixData[1][2] += temp.m_MatrixData[1][2]; m_MatrixData[1][3] += temp.m_MatrixData[1][3];
	m_MatrixData[2][0] += temp.m_MatrixData[2][0]; m_MatrixData[2][1] += temp.m_MatrixData[2][1]; m_MatrixData[2][2] += temp.m_MatrixData[2][2]; m_MatrixData[2][3] += temp.m_MatrixData[2][3];
	m_MatrixData[3][0] += temp.m_MatrixData[3][0]; m_MatrixData[3][1] += temp.m_MatrixData[3][1]; m_MatrixData[3][2] += temp.m_MatrixData[3][2]; m_MatrixData[3][3] = 1.0f;
	
}

void Matrix4x4::SetRotationZ(float rotation)
{
	float radians = rotation * DEGTORAD;

	m_MatrixData[0][0] = cosf(radians);
	m_MatrixData[0][1] = -sinf(radians);
	m_MatrixData[1][0] = sinf(radians);
	m_MatrixData[1][1] = cosf(radians);
}

void Matrix4x4::Scale(Vector3& scale)
{
	m_MatrixData[0][0] *= scale.x;
	m_MatrixData[1][1] *= scale.y;
	m_MatrixData[2][2] *= scale.z;
}

void Matrix4x4::SetScale(Vector3& scale)
{
	m_MatrixData[0][0] = scale.x;
	m_MatrixData[1][1] = scale.y;
	m_MatrixData[2][2] = scale.z;
}

void Matrix4x4::Scale(Vector2& scale)
{
	m_MatrixData[0][0] += scale.x;
	m_MatrixData[1][1] += scale.y;
}

void Matrix4x4::SetScale(Vector2& scale)
{
	m_MatrixData[0][0] = scale.x;
	m_MatrixData[1][1] = scale.y;
}

void Matrix4x4::Identity()
{
	m_MatrixData[0][0] = 1.0f; m_MatrixData[0][1] = 0.0f; m_MatrixData[0][2] = 0.0f; m_MatrixData[0][3] = 0.0f;
	m_MatrixData[1][0] = 0.0f; m_MatrixData[1][1] = 1.0f; m_MatrixData[1][2] = 0.0f; m_MatrixData[1][3] = 0.0f;
	m_MatrixData[2][0] = 0.0f; m_MatrixData[2][1] = 0.0f; m_MatrixData[2][2] = 1.0f; m_MatrixData[2][3] = 0.0f;
	m_MatrixData[3][0] = 0.0f; m_MatrixData[3][1] = 0.0f; m_MatrixData[3][2] = 0.0f; m_MatrixData[3][3] = 1.0f;
}

Vector2 Matrix4x4::GetTranslation2D()
{
	return Vector2(m_MatrixData[0][3], m_MatrixData[1][3]);
}

Vector3 Matrix4x4::GetTranslation3D()
{ 
	return Vector3(m_MatrixData[0][3], m_MatrixData[1][3], m_MatrixData[2][3]);
}

/*
Matrix4x4 Matrix4x4::operator+(const Matrix4x4& mat)
{

	m_MatrixData[0][0] += mat.m_MatrixData[0][0]; m_MatrixData[0][1] += mat.m_MatrixData[0][1]; m_MatrixData[0][2] += mat.m_MatrixData[0][2]; m_MatrixData[0][3] += mat.m_MatrixData[0][3];
	m_MatrixData[1][0] += mat.m_MatrixData[1][0]; m_MatrixData[1][1] += mat.m_MatrixData[1][1]; m_MatrixData[1][2] += mat.m_MatrixData[1][2]; m_MatrixData[1][3] += mat.m_MatrixData[1][3];
	m_MatrixData[2][0] += mat.m_MatrixData[2][0]; m_MatrixData[2][1] += mat.m_MatrixData[2][1]; m_MatrixData[2][2] += mat.m_MatrixData[2][2]; m_MatrixData[2][3] += mat.m_MatrixData[2][3];
	m_MatrixData[3][0] += mat.m_MatrixData[3][0]; m_MatrixData[3][1] += mat.m_MatrixData[3][1]; m_MatrixData[3][2] += mat.m_MatrixData[3][2]; m_MatrixData[3][3] = 1.0f;
	return m_MatrixData;
}
*/
Vector2 Matrix4x4::operator*(const Vector2& vec)
{
	Vector2 retVal;

	retVal.x = m_MatrixData[0][0] * vec.x + m_MatrixData[0][1] * vec.y + m_MatrixData[0][3] * vec.w;
	retVal.y = m_MatrixData[1][0] * vec.x + m_MatrixData[1][1] * vec.y + m_MatrixData[1][3] * vec.w;
	retVal.w = m_MatrixData[3][0] * vec.x + m_MatrixData[3][1] * vec.y + m_MatrixData[3][3] * vec.w;

	return retVal;
}

Vector3 Matrix4x4::operator*(const Vector3& vec)
{
	Vector3 retVal;

	retVal.x = m_MatrixData[0][0] * vec.x + m_MatrixData[0][1] * vec.y + m_MatrixData[0][2] * vec.z + m_MatrixData[0][3] * vec.w;
	retVal.y = m_MatrixData[1][0] * vec.x + m_MatrixData[1][1] * vec.y + m_MatrixData[1][2] * vec.z + m_MatrixData[1][3] * vec.w;
	retVal.z = m_MatrixData[2][0] * vec.x + m_MatrixData[2][1] * vec.y + m_MatrixData[2][2] * vec.z + m_MatrixData[2][3] * vec.w;
	retVal.w = m_MatrixData[3][0] * vec.x + m_MatrixData[3][1] * vec.y + m_MatrixData[3][2] * vec.z + m_MatrixData[3][3] * vec.w;

	return retVal;
}
