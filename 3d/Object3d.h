#pragma once

#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <DirectXMath.h>
#include <d3dx12.h>
#include <string>
#include "PipelineSet.h"
#include "Model.h"
#include "Camera.h"
#include "LightGroup.h"
#include "CollisionInfo.h"


#include <map>

class CollisionManager;
class BaseCollider;

/// <summary>
/// 3Dオブジェクト
/// </summary>
class Object3d
{
protected: // エイリアス
	// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public: // サブクラス
	// 定数バッファ用データ構造体B0
	struct ConstBufferDataB0
	{
		XMMATRIX viewproj;    // ビュープロジェクション行列
		XMMATRIX world; // ワールド行列
		XMFLOAT3 cameraPos; // カメラ座標（ワールド座標）
	};

public: // 静的メンバ関数
	/// <summary>
	/// 静的初期化
	/// </summary>
	/// <param name="device">デバイス</param>
	static void StaticInitialize(ID3D12Device* device, Camera* camera = nullptr);

	/// <summary>
	/// グラフィックパイプラインの生成
	/// </summary>
	/// <param name="vsName">頂点シェーダー</param>
	/// <param name="psName">ピクセルシェーダー</param>
	/// <param name="piplineName">パイプラインセットの連想配列用名</param>
	static void CreateGraphicsPipeline(const wchar_t* vsName, const wchar_t* psName, const char* piplineName);

	/// <summary>
	/// カメラのセット
	/// </summary>
	/// <param name="camera">カメラ</param>
	static void SetCamera(Camera* camera) {
		Object3d::camera = camera;
	}

	/// <summary>
	/// ライトグループのセット
	/// </summary>
	/// <param name="lightGroup">ライトグループ</param>
	static void SetLightGroup(LightGroup* lightGroup) {
		Object3d::lightGroup = lightGroup;
	}

	/// <summary>
	/// 描画前処理
	/// </summary>
	/// <param name="cmdList">描画コマンドリスト</param>
	static void PreDraw(ID3D12GraphicsCommandList* cmdList);

	/// <summary>
	/// 描画後処理
	/// </summary>
	static void PostDraw();

	/// <summary>
	/// 3Dオブジェクト生成
	/// </summary>
	/// <returns>3Dオブジェクト</returns>
	static Object3d* Create(Model* model = nullptr, Object3d* object3d = new Object3d);

protected: // 静的メンバ変数
	// デバイス
	static ID3D12Device* dev;
	// コマンドリスト
	static ID3D12GraphicsCommandList* cmdList;
	// パイプライン
	static std::map<std::string, PipelineSet> pipelineSet;
	// カメラ
	static Camera* camera;
	// ライト
	static LightGroup* lightGroup;
	// コリジョンマネージャー
	static CollisionManager* collisionMan;

public: // メンバ関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Object3d() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~Object3d();

	/// <summary>
	/// 初期化処理
	/// </summary>
	/// <returns>成否</returns>
	virtual bool Initialize();

	/// <summary>
	/// 更新処理
	/// </summary>
	virtual void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	virtual void Draw();

	/// <summary>
	/// 行列の更新
	/// </summary>
	void UpdateWorldMatrix();

	/// <summary>
	/// 座標の取得
	/// </summary>
	/// <returns>座標</returns>
	const XMFLOAT3& GetPosition() { return position; }

	/// <summary>
	/// 回転の取得
	/// </summary>
	/// <returns>回転</returns>
	const XMFLOAT3& GetRotation() { return rotation; }

	/// <summary>
	/// コライダーを取得
	/// </summary>
	/// <returns>コライダー</returns>
	BaseCollider* GetCollider() { return collider; }

	/// <summary>
	/// ワールド行列の取得
	/// </summary>
	/// <returns>ワールド行列</returns>
	const XMMATRIX& GetMatWorld() { return matWorld; }

	/// <summary>
	/// パイプラインセットの連想配列用名を取得
	/// </summary>
	/// <returns>パイプラインセットの連想配列用名</returns>
	const std::string& GetPipelineName() { return piplineName; }

	/// <summary>
	/// ワールド座標を取得
	/// </summary>
	/// <returns>ワールド座標</returns>
	XMFLOAT3 GetWorldPosition();

	/// <summary>
	/// モデルを取得
	/// </summary>
	/// <returns>モデル</returns>
	inline Model* GetModel() { return model; }

	/// <summary>
	/// 座標の設定
	/// </summary>
	/// <param name="position">座標</param>
	void SetPosition(XMFLOAT3 position) { this->position = position; }

	/// <summary>
	/// 回転の設定
	/// </summary>
	/// <param name="rotation">回転</param>
	void SetRotation(XMFLOAT3 rotation) { this->rotation = rotation; }

	/// <summary>
	/// スケールの設定
	/// </summary>
	/// <param name="position">スケール</param>
	void SetScale(XMFLOAT3 scale) { this->scale = scale; }

	/// <summary>
	/// モデルのセット
	/// </summary>
	/// <param name="model">モデル</param>
	void SetModel(Model* model) { this->model = model; }

	/// <summary>
	/// ビルボードフラグのセット
	/// </summary>
	/// <param name="isBillboard">ビルボードか</param>
	void SetBillboard(bool isBillboard) { this->isBillboard = isBillboard; }

	/// <summary>
	/// コライダーのセット
	/// </summary>
	/// <param name="collider">コライダー</param>
	void SetCollider(BaseCollider* collider);

	/// <summary>
	/// 衝突時コールバック関数
	/// </summary>
	/// <param name="info">衝突情報</param>
	virtual void OnCollision(const CollisionInfo& info) {}

	/// <summary>
	/// パイプラインセットの連想配列用名を設定
	/// </summary>
	/// <param name="piplineName">パイプラインセットの連想配列用名</param>
	void SetPipelineName(const char* piplineName);

protected: // メンバ関数
	/// <summary>
	/// コライダーの削除
	/// </summary>
	void ColliderDestroy();

protected: // メンバ変数
	const char* name = nullptr;
	// 定数バッファ
	ComPtr<ID3D12Resource> constBuffB0;
	// パイプラインセットの連想配列用名
	std::string piplineName = "BaseShader";
	// 色
	XMFLOAT4 color = { 1,1,1,1 };
	// ローカルスケール
	XMFLOAT3 scale = { 1,1,1 };
	// X,Y,Z軸回りのローカル回転角
	XMFLOAT3 rotation = { 0,0,0 };
	// ローカル座標
	XMFLOAT3 position = { 0,0,0 };
	// ローカルワールド変換行列
	XMMATRIX matWorld;
	// 親オブジェクト
	Object3d* parent = nullptr;
	// モデル
	Model* model = nullptr;
	// ビルボード
	bool isBillboard = false;
	// コライダー
	BaseCollider* collider = nullptr;
};

