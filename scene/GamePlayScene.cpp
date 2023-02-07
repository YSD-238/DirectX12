#include "GamePlayScene.h"

void GamePlayScene::Initialize()
{
	// シーン基盤初期化処理
	BaseScene::Initialize();

}

void GamePlayScene::Finalize()
{
	// シーン基盤終了処理
	BaseScene::Finalize();
}

void GamePlayScene::Update()
{
}

void GamePlayScene::Draw()
{
	// コマンドリストの取得
	ID3D12GraphicsCommandList* cmdList = dx->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	spriteCommon->PreDraw();
	// 背景スプライト描画
	

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Object3d::PreDraw(cmdList);

	// 3Dオブクジェクトの描画


	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	// 3Dオブジェクト描画後処理
	Object3d::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	spriteCommon->PreDraw();

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	//// 描画

	// デバッグテキストの描画
	debugText->DrawAll(cmdList);

#pragma endregion
}
