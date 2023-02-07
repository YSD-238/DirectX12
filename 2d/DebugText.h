#pragma once

#include "Sprite.h"

// デバッグ文字列クラスの定義
class DebugText
{
private: // エイリアス
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;

public: // 静的メンバ関数
	/// <summary>
	/// インスタンスの取得
	/// </summary>
	/// <returns>インスタンス</returns>
	static DebugText* GetInstance();

private: // 静的メンバ変数    
	static const int maxCharCount = 256;    // 最大文字数
	static const int fontWidth = 9;         // フォント画像内1文字分の横幅
	static const int fontHeight = 18;       // フォント画像内1文字分の縦幅
	static const int fontLineCount = 14;    // フォント画像内1行分の文字数

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
	/// 文字列の描画
	/// </summary>
	/// <param name="text">文字列</param>
	/// <param name="position">座標</param>
	/// <param name="scale">大きさ</param>
	void Print(const std::string& text, XMFLOAT2 position = { 0.0f,0.0f }, float scale = 1.0f);

	/// <summary>
	/// 全描画
	/// </summary>
	/// <param name="cmdList">コマンドリスト</param>
	void DrawAll(ID3D12GraphicsCommandList* cmdList);

private: // メンバ変数
	// スプライトの共通部分
	SpriteCommon* spriteCommon;
	// スプライトデータの配列
	Sprite* spriteDatas[maxCharCount];
	// スプライトデータ配列の添え字番号
	int spriteIndex = 0;
};