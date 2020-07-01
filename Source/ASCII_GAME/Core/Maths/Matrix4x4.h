#ifndef _MATRIX_H_
#define _MATRIX_H_

class Vector2;
class Vector3;

class Matrix4x4
{
public:

	Matrix4x4();
	~Matrix4x4();

	float m_MatrixData[4][4];

	void Translate(Vector2& translation);
	void SetTranslation(Vector2& translation);

	void Translate(Vector3& translation);
	void SetTranslation(Vector3& translation);

	void RotateX(float rotation);
	void SetRotationX(float rotation);

	void RotateY(float rotation);
	void SetRotationY(float rotation);

	void RotateZ(float rotation);
	void SetRotationZ(float rotation);

	void Scale(Vector2& scale);
	void SetScale(Vector2& scale);

	void Scale(Vector3& scale);
	void SetScale(Vector3& scale);

	Vector2 GetTranslation2D();
	Vector3 GetTranslation3D();

	void Identity();

	//Matrix4x4 operator+(const Matrix4x4& mat);
	Vector2 operator*(const Vector2& vec);
	Vector3 operator*(const Vector3& vec);

};

#endif
