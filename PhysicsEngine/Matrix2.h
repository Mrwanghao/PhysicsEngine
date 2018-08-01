#pragma once


class Matrix2
{
public:
	union
	{
		struct
		{
			float m00, m01,
				m10, m11;
		};
		float data[4];
	};

public:
	Matrix2();
	Matrix2(float _m00, float _m01, float _m10, float _m11);

public:
	inline float* operator[](int index) { return &(data[index * 2]); }
	Matrix2& operator*(float scale);

public:
	Matrix2 Transpose() const;
	float Determinant() const;
	Matrix2 Minor() const;
	Matrix2 Cofactor() const;
	Matrix2 Adjugate() const;
	Matrix2 Invert() const;
};
