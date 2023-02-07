#pragma once

#include <wrl.h>

#include <dinput.h>
#define DIRECTINPUT_VERSION     0x0800          // DirectInputのバージョン指定

#include "WindowsApplication.h"

/// <summary>
/// 入力
/// </summary>
class Input
{
private: // エイリアス
	// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

public: // サブクラス
	struct MouseMove
	{
		LONG    lX;
		LONG    lY;
		LONG    lZ;
	};

public: // 静的メンバ関数
	/// <summary>
	/// インスタンスの取得
	/// </summary>
	/// <returns>インスタンス</returns>
	static Input* GetInstance();

public: // メンバ関数
	/// <summary>
	/// 初期化処理
	/// </summary>
	bool Initialize(WindowsApplication* win);

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// キーの押下をチェック
	/// </summary>
	/// <param name="keyNumber">キー番号( DIK_0 等)</param>
	/// <returns>押されているか</returns>
	bool PushKey(BYTE keyNumber);

	/// <summary>
	/// キーのトリガーをチェック
	/// </summary>
	/// <param name="keyNumber">キー番号( DIK_0 等)</param>
	/// <returns>トリガーか</returns>
	bool TriggerKey(BYTE keyNumber);

	/// <summary>
	/// マウスの左ボタン押下をチェック
	/// </summary>
	/// <returns>押されているか</returns>
	bool PushMouseLeft();

	/// <summary>
	/// マウスの右ボタン押下をチェック
	/// </summary>
	/// <returns>押されているか</returns>
	bool PushMouseRight();

	/// <summary>
	/// マウスの中央ボタン押下をチェック
	/// </summary>
	/// <returns>押されているか</returns>
	bool PushMouseMiddle();

	/// <summary>
	/// マウスの左ボタントリガーをチェック
	/// </summary>
	/// <returns>トリガーか</returns>
	bool TriggerMouseLeft();

	/// <summary>
	/// マウスの右ボタントリガーをチェック
	/// </summary>
	/// <returns>トリガーか</returns>
	bool TriggerMouseRight();

	/// <summary>
	/// マウスの中央ボタントリガーをチェック
	/// </summary>
	/// <returns>トリガーか</returns>
	bool TriggerMouseMiddle();

	/// <summary>
	/// マウスの移動量を取得
	/// </summary>
	/// <returns>マウスの移動量</returns>
	const MouseMove& GetMouseMove();

private: // メンバ関数
	Input() = default;
	Input(const Input&) = delete;
	~Input() = default;
	Input& operator=(const Input&) = delete;

private: // メンバ変数
	// DirectInputインスタンス
	ComPtr<IDirectInput8> dinput = nullptr;
	// キーボードデバイス
	ComPtr<IDirectInputDevice8> devKeyboard = nullptr;
	// マウスデバイス
	ComPtr<IDirectInputDevice8> devMouse = nullptr;
	// キーボード情報
	BYTE key[256] = {};
	// 前回フレームキーボード情報
	BYTE keyPre[256] = {};
	// マウス情報
	DIMOUSESTATE2 mouseState = {};
	// 前回フレームのマウス情報
	DIMOUSESTATE2 mouseStatePre = {};
};