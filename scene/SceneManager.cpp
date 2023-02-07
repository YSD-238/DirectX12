#include "SceneManager.h"

SceneManager* SceneManager::GetInstance()
{
	// インスタンスの生成
	static SceneManager instance;

	return &instance;
}

void SceneManager::Initialize(BaseScene* startScene)
{
	// シーンの取得
	scene = startScene;
	// シーンの初期化
	scene->Initialize();
}

void SceneManager::Finalize()
{
	// シーンの終了処理
	scene->Finalize();
	// シーンの解放
	safe_delete(scene);
}

void SceneManager::Update()
{
	// 次のシーンが入っていたら
	if (nextScene) {
		// 現在のシーン終了処理
		scene->Finalize();
		// 現在のシーン解放
		safe_delete(scene);
		// 次のシーンに移動
		scene = nextScene;
		// 次のシーンの初期化
		scene->Initialize();
		nextScene = nullptr;
	}

	// シーン更新処理
	scene->Update();
}

void SceneManager::Draw()
{
	// シーン描画処理
	scene->Draw();
}
