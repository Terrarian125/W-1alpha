#pragma once
#include <DirectXMath.h>

namespace DirectX
{
	// XMFLOAT3同士の加算
	inline XMFLOAT3 operator+(const XMFLOAT3& lhs, const XMFLOAT3& rhs)
	{
		return XMFLOAT3(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
	}
	// XMFLOAT3同士の減算
	inline XMFLOAT3 operator-(const XMFLOAT3& lhs, const XMFLOAT3& rhs)
	{
		return XMFLOAT3(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
	}
	// XMFLOAT3とスカラー値の乗算
	inline XMFLOAT3 operator*(const XMFLOAT3& vec, float scalar)
	{
		return XMFLOAT3(vec.x * scalar, vec.y * scalar, vec.z * scalar);
	}
	// スカラー値とXMFLOAT3の乗算
	inline XMFLOAT3 operator*(float scalar, const XMFLOAT3& vec)
	{
		return vec * scalar;
	}
}