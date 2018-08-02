#pragma once


class Vec4
{
public:
	union 
	{
		struct
		{
			float x;
			float y;
			float z;
			float w;
		};
		float data[4];
	};

public:
	inline float& operator[](int index) { return data[index]; }
	Vec4 operator+(const Vec4& right) const;
	Vec4 operator-(const Vec4& right) const;
	Vec4 operator*(const Vec4& right) const;
	Vec4 operator*(float scale) const;
	bool operator==(const Vec4& right);
	bool operator!=(const Vec4& right);

public:
	Vec4();
	Vec4(float _x, float _y, float _z, float _w);

public:
	float Dot(const Vec4& right) const;
	float Magnitude() const;
	float MagnitudeSq() const;
	void Normalize();
	Vec4 GetNormalized() const;
};