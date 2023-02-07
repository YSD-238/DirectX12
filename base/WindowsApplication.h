#pragma once

#include <Windows.h>

/// <summary>
/// WindoswAPI
/// </summary>
class WindowsApplication
{
public: // 静的メンバ変数
	// ウィンドウサイズ
	static const int window_width = 1280;	// 横幅
	static const int window_height = 720;	// 縦幅
	static const wchar_t windowClassName[];

public: // 静的メンバ関数
	/// <summary>
	/// ウィンドウプロシージャ
	/// </summary>
	/// <param name="hwnd">ウィンドウハンドル</param>
	/// <param name="msg">メッセージ番号</param>
	/// <param name="wparam">メッセージ情報1</param>
	/// <param name="lparam">メッセージ情報2</param>
	/// <returns>成否</returns>
	static LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

public: // メンバ関数
	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize();

	/// <summary>
	/// 終了処理
	/// </summary>
	void Finalize();

	/// <summary>
	/// メッセージの処理
	/// </summary>
	/// <returns>終了かどうか</returns>
	bool ProcessMessage();

	/// <summary>
	/// ハンドルウィンドウの取得
	/// </summary>
	/// <returns>ハンドルウィンドウ</returns>
	HWND GetHwnd() { return hwnd; }

	/// <summary>
	/// インスタンスの取得
	/// </summary>
	/// <returns>インスタンス</returns>
	HINSTANCE GetHInstance() { return w.hInstance; }

private: // メンバ関数
	// ウィンドウズクラス
	WNDCLASSEX w{};
	// ハンドルウィンドウ
	HWND hwnd;
};