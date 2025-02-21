#pragma once

class VMatrix
{
public:
	Vector3 m[4][4];

	const matrix3x4_t& As3x4() const {
		return *((const matrix3x4_t*)this);
	}
};
