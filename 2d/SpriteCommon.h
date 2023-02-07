#pragma once

#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <d3dx12.h>
#include <DirectXMath.h>

#include "PipelineSet.h"

/// <summary>
/// スプライトの共通部分
/// </summary>
class SpriteCommon
{
private: // エイリアス
	// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMMATRIX = DirectX::XMMATRIX;

public: // 静的メンバ関数
	/// <summary>
	/// インスタンスの取得
	/// </summary>
	/// <returns>インスタンス</returns>
	static SpriteCommon* GetInstance();

public: // 静的メンバ変数
	// テクスチャの最大枚数
	static const int spriteSRVCount = 512;

public: // メンバ関数
	/// <summary>
	/// 初期化処理
	/// </summary>
	/// <param name="dev">デバイス</param>
	/// <param name="cmdList">コマンドリスト</param>
	/// <param name="window_width">ウィンドウ横幅</param>
	/// <param name="window_height">ウィンドウ縦幅</param>
	void Initialize(ID3D12Device* dev, ID3D12GraphicsCommandList* cmdList, int window_width, int window_height);

	/// <summary>
	/// テクスチャ読み込み
	/// </summary>
	/// <param name="texNumber">テクスチャ番号</param>
	/// <param name="filename">テクスチャの名前</param>
	bool LoadTexture(UINT texNumber, const wchar_t* filename);

	/// <summary>
	/// 描画前処理
	/// </summary>
	void PreDraw();

	/// <summary>
	/// デスクリプタヒープのセット
	/// </summary>
	void SetDescriptorHeaps();

	/// <summary>
	/// ルートデスクリプタテーブルの設定
	/// </summary>
	/// <param name="rootParameterIndex">ルートパラメーター番号</param>
	/// <param name="texNumber">テクスチャ番号</param>
	void SetGraphicsRootDescriptorTable(UINT rootParameterIndex, UINT texNumber);

	/// <summary>
	/// テクスチャの取得
	/// </summary>
	/// <param name="texNumber">テクスチャ番号</param>
	/// <returns>テクスチャ</returns>
	ID3D12Resource* GetTexBuff(int texNumber);

	/// <summary>
	/// 射影行列の取得
	/// </summary>
	/// <returns>射影行列</returns>
	const XMMATRIX& GetMatProjection() { return matProjection; }

private: // メンバ関数
	/// <summary>
	/// グラフィックスパイプラインの生成
	/// </summary>
	void CreateGraphicsPipeline();

	SpriteCommon() = default;
	SpriteCommon(const SpriteCommon&) = delete;
	~SpriteCommon() = default;
	SpriteCommon& operator=(const SpriteCommon&) = delete;
private: // メンバ変数
	// デバイス
	ID3D12Device* dev = nullptr;
	// DXコマンドリスト
	ID3D12GraphicsCommandList* cmdList = nullptr;
	// パイプラインセット
	PipelineSet pipelineSet;
	// 射影行列
	XMMATRIX matProjection{};
	// デスクリプタヒープ
	ComPtr<ID3D12DescriptorHeap> descHeap;
	// テクスチャバッファの配列
	ComPtr<ID3D12Resource> texBuff[spriteSRVCount];
};