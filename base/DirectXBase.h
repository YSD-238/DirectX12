#pragma once

#include <Windows.h>
#include <d3d12.h>
#include <d3dx12.h>
#include <dxgi1_6.h>
#include <wrl.h>
#include <chrono>

#include "WindowsApplication.h"

/// <summary>
/// DirectX基盤
/// </summary>
class DirectXBase
{
private: // エイリアス
	// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

public: // メンバ関数
	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize(WindowsApplication* winApp);

	/// <summary>
	/// 描画前処理
	/// </summary>
	void PreDraw();

	/// <summary>
	/// 描画後処理
	/// </summary>
	void PostDraw();

	/// <summary>
	/// デバイスの取得
	/// </summary>
	/// <returns>デバイス</returns>
	ID3D12Device* GetDevice() { return dev.Get(); }

	/// <summary>
	/// コマンドリストの取得
	/// </summary>
	/// <returns>コマンドリスト</returns>
	ID3D12GraphicsCommandList* GetCommandList() { return cmdList.Get(); }

private: // メンバ変数
	// WindowsAPI
	WindowsApplication* winApp = nullptr;
	// 記録時間 (FPS固定用)
	std::chrono::steady_clock::time_point reference;
	// DirectX3D関連
	// デバイス
	ComPtr<ID3D12Device> dev;
	// DXGIファクトリ
	ComPtr<IDXGIFactory6> dxgiFactory;
	// コマンドアロケータ
	ComPtr<ID3D12CommandAllocator> cmdAllocator;
	// コマンドリスト
	ComPtr<ID3D12GraphicsCommandList> cmdList;
	// コマンドキュー
	ComPtr<ID3D12CommandQueue> cmdQueue;
	// スワップチェーン
	ComPtr<IDXGISwapChain4> swapchain;
	// レンダーターゲットビューヒープ
	ComPtr<ID3D12DescriptorHeap> rtvHeaps;
	// 
	ComPtr<ID3D12DescriptorHeap> dsvHeap;
	// バックバッファ
	std::vector<ComPtr<ID3D12Resource>> backBuffers;
	// 
	ComPtr<ID3D12Resource> depthBuffer;
	// フェンス
	ComPtr<ID3D12Fence> fence;
	// フェンスの数
	UINT64 fenceVal = 0;

private: // メンバ関数
	/// <summary>
	/// FPS固定初期化
	/// </summary>
	void InitializeFixFps();

	/// <summary>
	/// デバイスの初期化
	/// </summary>
	/// <returns>成否</returns>
	bool InitializeDevice();

	/// <summary>
	/// コマンド関連の初期化
	/// </summary>
	/// <returns>成否</returns>
	bool InitializeCommand();

	/// <summary>
	/// スワップチェーンの初期化
	/// </summary>
	/// <returns>成否</returns>
	bool InitializeSwapchain();

	/// <summary>
	/// レンダーターゲットビューの初期化
	/// </summary>
	/// <returns>成否</returns>
	bool InitializeRenderTargetView();

	/// <summary>
	/// 深度バッファの初期化
	/// </summary>
	/// <returns>成否</returns>
	bool InitializeDepthBuffer();

	/// <summary>
	/// フェンスの初期化
	/// </summary>
	/// <returns>成否</returns>
	bool InitializeFence();

	/// <summary>
	/// FPS固定更新
	/// </summary>
	void UpdateFixFPS();
};