#pragma once

#include <DirectXMath.h>

/// <summary>
/// カメラ基本機能
/// </summary>
class Camera
{
protected: // エイリアス
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

public: // メンバ関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="window_width">画面幅</param>
	/// <param name="window_height">画面高さ</param>
	Camera(const int& window_width, const int& window_height);

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~Camera() = default;

	/// <summary>
	/// 毎フレーム更新
	/// </summary>
	virtual void Update();

	/// <summary>
	/// ビュー行列を更新
	/// </summary>
	void UpdateViewMatrix();

	/// <summary>
	/// 射影行列を更新
	/// </summary>
	void UpdateProjectionMatrix();

	/// <summary>
	/// ビュー行列の取得
	/// </summary>
	/// <returns>ビュー行列</returns>
	const XMMATRIX& GetViewMatrix() { return matView; }

	/// <summary>
	/// 射影行列の取得
	/// </summary>
	/// <returns>射影行列</returns>
	const XMMATRIX& GetProjectionMatrix() { return matProjection; }

	/// <summary>
	/// ビュー射影行列の取得
	/// </summary>
	/// <returns>ビュー射影行列</returns>
	const XMMATRIX& GetViewProjectionMatrix() { return matViewProjection; }

	/// <summary>
	/// ビルボード行列の取得
	/// </summary>
	/// <returns>ビルボード行列</returns>
	const XMMATRIX& GetBillboardMatrix() { return matBillboard; }

	/// <summary>
	/// 視点座標の取得
	/// </summary>
	/// <returns>座標</returns>
	const XMFLOAT3& GetEye() { return eye; }

	/// <summary>
	/// 視点座標の設定
	/// </summary>
	/// <param name="eye">座標</param>
	void SetEye(const XMFLOAT3& eye) { this->eye = eye; viewDirty = true; }

	/// <summary>
	/// 注視点座標の取得
	/// </summary>
	/// <returns>座標</returns>
	const XMFLOAT3& GetTarget() { return target; }

	/// <summary>
	/// 注視点座標の設定
	/// </summary>
	/// <param name="target">座標</param>
	void SetTarget(const XMFLOAT3& target) { this->target = target; viewDirty = true; }

	/// <summary>
	/// 上方向ベクトルの取得
	/// </summary>
	/// <returns>上方向ベクトル</returns>
	const XMFLOAT3& GetUp() { return up; }

	/// <summary>
	/// 上方向ベクトルの設定
	/// </summary>
	/// <param name="up">上方向ベクトル</param>
	void SetUp(const XMFLOAT3& up) { this->up = up; viewDirty = true; }

	/// <summary>
	/// 角度を取得
	/// </summary>
	/// <returns>角度</returns>
	const XMFLOAT3 GetRotation() { return rotation; }

	/// <summary>
	/// 角度を設定
	/// </summary>
	/// <param name="rotation">角度</param>
	void SetRotation(const XMFLOAT3& rotation);

	/// <summary>
	/// ベクトルによる視点移動
	/// </summary>
	/// <param name="move">移動量</param>
	void MoveEyeVector(const XMFLOAT3& move);
	void MoveEyeVector(const XMVECTOR& move);

	/// <summary>
	/// ベクトルによる移動
	/// </summary>
	/// <param name="move">移動量</param>
	void MoveVector(const XMFLOAT3& move);
	void MoveVector(const XMVECTOR& move);

	/// <summary>
	/// ベクトルとローテーションによる移動
	/// </summary>
	/// <param name="move">移動量</param>
	void MoveRotationVector(const XMFLOAT3& move);
	void MoveRotationVector(const XMVECTOR& move);

	/// <summary>
	/// アングルによる回転
	/// </summary>
	/// <param name="angle">アングル</param>
	void RotateXAngle(const int& angle);
	void RotateYAngle(const int& angle);
	void RotateZAngle(const int& angle);

	/// <summary>
	/// ラジアンによる回転
	/// </summary>
	/// <param name="radian">ラジアン</param>
	void RotateXRadian(const float& radian);
	void RotateYRadian(const float& radian);
	void RotateZRadian(const float& radian);

protected: // メンバ変数
	// ビュー行列
	XMMATRIX matView = DirectX::XMMatrixIdentity();
	// ビルボード行列
	XMMATRIX matBillboard = DirectX::XMMatrixIdentity();
	// Y軸回りビルボード行列
	XMMATRIX matBillboardY = DirectX::XMMatrixIdentity();
	// 射影行列
	XMMATRIX matProjection = DirectX::XMMatrixIdentity();
	// ビュー射影行列
	XMMATRIX matViewProjection = DirectX::XMMatrixIdentity();
	// ビュー行列ダーティフラグ
	bool viewDirty = false;
	// 射影行列ダーティフラグ
	bool projectionDirty = false;
	// 視点座標
	XMFLOAT3 eye = { 0, 0, -20 };
	// 注視点座標
	XMFLOAT3 target = { 0, 0, 0 };
	// 上方向ベクトル
	XMFLOAT3 up = { 0, 1, 0 };
	// ローテーション
	XMFLOAT3 rotation = { 0, 0, 0 };
	// 距離
	float distance = 30.0f;
	// アスペクト比
	float aspectRatio = 1.0f;
};

