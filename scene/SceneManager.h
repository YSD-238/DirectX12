#pragma once
#include "BaseScene.h"

/// <summary>
/// シーン管理
/// </summary>
class SceneManager
{

public: // 静的メンバ関数
	/// <summary>
	/// インスタンスの取得
	/// </summary>
	/// <returns>インスタンス</returns>
	static SceneManager* GetInstance();

private: // メンバ関数
	SceneManager() = default;
	SceneManager(const SceneManager&) = delete;	
	~SceneManager() = default;
	SceneManager& operator=(const SceneManager&) = delete;

public: // メンバ関数
	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize(BaseScene* fastScene);

	/// <summary>
	/// 終了処理
	/// </summary>
	void Finalize();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();

	/// <summary>
	/// 次のシーンの予約設定
	/// </summary>
	/// <param name="baseScene">次のシーン</param>
	void SetNextScene(BaseScene* nextScene) { this->nextScene = nextScene; }

private: // メンバ変数
	// 現在のシーン
	BaseScene* scene = nullptr;
	// 次のシーン
	BaseScene* nextScene = nullptr;
};