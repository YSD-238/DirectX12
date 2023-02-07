#pragma once

#include <Windows.h>
#include <wrl.h>
#include <DirectXMath.h>
#include <d3dx12.h>

#include "SpriteCommon.h"

/// <summary>
/// スプライト1枚分のクラス
/// </summary>
class Sprite
{
private: // エイリアス
	// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

private: // 静的メンバ変数
	// スプライトの基盤
	static SpriteCommon* spriteCommon;
	// デバイス
	static ID3D12Device* dev;
	// コマンドリスト
	static ID3D12GraphicsCommandList* cmdList;

public: // 静的メンバ関数
	/// <summary>
	/// 静的初期化処理
	/// </summary>
	static void StaticInitialize(ID3D12Device* dev, ID3D12GraphicsCommandList* cmdList);

	/// <summary>
	/// スプライト生成
	/// </summary>
	/// <param name="texNumber">テクスチャ番号</param>
	/// <param name="position">座標</param>
	/// <param name="color">色</param>
	/// <param name="anchorpoint">アンカーポイント</param>
	/// <param name="isFlipX">左右反転</param>
	/// <param name="isFlipY">上下反転</param>
	/// <returns>生成されたスプライト</returns>
	static Sprite* Create(UINT texNumber, XMFLOAT2 position = { 0,0 }, XMFLOAT4 color = { 1, 1, 1, 1 }, XMFLOAT2 anchorpoint = { 0.0f, 0.0f }, bool isFlipX = false, bool isFlipY = false);

public:  // サブクラス
	/// <summary>
	/// 頂点データ
	/// </summary>
	struct VertexPosUv
	{
		XMFLOAT3 pos; // xyz座標
		XMFLOAT2 uv;  // uv座標
	};

	/// <summary>
	/// 定数バッファ用データ構造体
	/// </summary>
	struct ConstBufferData
	{
		XMFLOAT4 color; // 色 (RGBA)
		XMMATRIX mat;   // ３Ｄ変換行列
	};

public: // メンバ関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Sprite(UINT texNumber, XMFLOAT2 position, XMFLOAT2 size, XMFLOAT4 color, XMFLOAT2 anchorpoint, bool isFlipX, bool isFlipY);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Sprite();

	/// <summary>
	///  初期化処理
	/// </summary>
	void Initialize();

	/// <summary>
	/// 頂点バッファの転送
	/// </summary>
	void TransferVertexBuffer();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();

	/// <summary>
	/// 座標の取得
	/// </summary>
	/// <returns>座標</returns>
	const XMFLOAT2& GetPosition() { return position; }

	/// <summary>
	/// サイズの取得
	/// </summary>
	/// <returns>サイズ</returns>
	const XMFLOAT2& GetSize() { return size; }

	/// <summary>
	/// 色を取得
	/// </summary>
	/// <returns>色</returns>
	const XMFLOAT4& GetColor() { return color; }

	/// <summary>
	/// アンカーポイントの取得
	/// </summary>
	/// <returns>アンカーポイント</returns>
	const XMFLOAT2& GetAnchorpoint() { return anchorpoint; }

	/// <summary>
	/// テクスチャ左上座標の取得
	/// </summary>
	/// <returns>テクスチャ左上座標</returns>
	const XMFLOAT2& GetTexLeftTop() { return texLeftTop; };

	/// <summary>
	/// テクスチャ切り出しサイズの取得
	/// </summary>
	/// <returns>テクスチャ切り出しサイズ</returns>
	const XMFLOAT2& GetTexSize() { return texSize; }

	/// <summary>
	/// 座標の設定
	/// </summary>
	/// <param name="position">座標</param>
	void SetPosition(const XMFLOAT2& position) { this->position = position; }

	/// <summary>
	/// 大きさの設定
	/// </summary>
	/// <param name="size">大きさ</param>
	void SetSize(const XMFLOAT2& size) { this->size = size; TransferVertexBuffer(); }

	/// <summary>
	/// 色の設定
	/// </summary>
	/// <param name="color">色</param>
	void SetColor(const XMFLOAT4& color) { this->color = color; }

	/// <summary>
	/// アンカーポイントの設定
	/// </summary>
	/// <param name="anchorpoint">アンカーポイント</param>
	void SetAnchorpoin(const XMFLOAT2& anchorpoint) { this->anchorpoint = anchorpoint; }

	/// <summary>
	/// テクスチャ左上座標の設定
	/// </summary>
	/// <param name="texLeftTop">テクスチャ左上座標</param>
	void SetTexLeftTop(const XMFLOAT2& texLeftTop) { this->texLeftTop = texLeftTop; };

	/// <summary>
	/// テクスチャ切り出しサイズの設定
	/// </summary>
	/// <returns>テクスチャ切り出しサイズ</returns>
	void SetTexSize(const XMFLOAT2& texSize) { this->texSize = texSize; }

private: // メンバ変数
	//頂点バッファ;
	ComPtr<ID3D12Resource> vertBuff;
	//頂点バッファビュー;
	D3D12_VERTEX_BUFFER_VIEW vbView{};
	//定数バッファ;
	ComPtr<ID3D12Resource> constBuff;
	// Z軸回りの回転角
	float rotation = 0.0f;
	// 座標
	XMFLOAT2 position = { 0,0 };
	// ワールド行列
	XMMATRIX matWorld;
	// 色(RGBA)
	XMFLOAT4 color = { 1, 1, 1, 1 };
	// テクスチャ番号
	UINT texNumber = 0;
	// 大きさ
	XMFLOAT2 size = { 100, 100 };
	// アンカーポイント
	XMFLOAT2 anchorpoint = { 0.5f, 0.5f };
	// 左右反転
	bool isFlipX = false;
	// 上下反転
	bool isFlipY = false;
	// テクスチャ左上座標
	XMFLOAT2 texLeftTop = { 0, 0 };
	// テクスチャ切り出しサイズ
	XMFLOAT2 texSize = { 100, 100 };
	// 非表示
	bool isInvisible = false;
};