#include "camera.h"
#include "Direct3D.h"

XMVECTOR _position;
XMVECTOR _target;
XMMATRIX _view;
XMMATRIX _proj;

//初期化（プロジェクション行列作成）
void Camera::Initialize()
{
	_position = XMVectorSet(0, 3, -10, 0);	//カメラの位置
	_target = XMVectorSet(0, 0, 0, 0);	//カメラの焦点

	//プロジェクション行列
	_proj = XMMatrixPerspectiveFovLH(XM_PIDIV4, (FLOAT)Direct3D::screenWidth_ / (FLOAT)Direct3D::screenHeight_, 0.1f, 1000.0f);
}

//更新（ビュー行列作成）
void Camera::Update()
{
	//ビュー行列
	_view = XMMatrixLookAtLH(XMVectorSet(_position.vecX, _position.vecY, _position.vecZ, 0),
		XMVectorSet(_target.vecX, _target.vecY, _target.vecZ, 0), XMVectorSet(0, 1, 0, 0));
}

//焦点を設定
void Camera::SetTarget(XMVECTOR target) { _target = target; }

//位置を設定
void Camera::SetPosition(XMVECTOR position) { _position = position; }

//焦点を取得
XMVECTOR Camera::GetTarget() { return _target; }

//位置を取得
XMVECTOR Camera::GetPosition() { return _position; }

//ビュー行列を取得
XMMATRIX Camera::GetViewMatrix() { return _view; }

//プロジェクション行列を取得
XMMATRIX Camera::GetProjectionMatrix() { return _proj; }