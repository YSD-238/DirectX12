#include "Framework.h"
#include "SceneManager.h"
#include "GamePlayScene.h"

#include "BaseScene.h"
#include <cassert>

Framework::Framework()
{
}

Framework::~Framework()
{
}

void Framework::Run()
{
	// 初期化処理
	Initialize();
	// ゲームループ
	Loop();
	// 終了処理
	Finalize();
}

void Framework::Initialize()
{
	// WindowsAPIの初期化処理
	win = new WindowsApplication();
	win->Initialize();

	// DirectXの初期化処理
	dx = new DirectXBase();
	dx->Initialize(win);

	// Inputクラス初期化処理
	// インスタンス取得
	input = Input::GetInstance();
	if (!input->Initialize(win)) {
		assert(0);
		return;
	}

	// Audio初期化処理
	// インスタンス取得
	audio = Audio::GetInstance();
	if (!audio->Initialize()) {
		assert(0);
		return;
	}

	// SpriteCommon共通初期化
	SpriteCommon::GetInstance()->Initialize(dx->GetDevice(), dx->GetCommandList(), 
		WindowsApplication::window_width, WindowsApplication::window_height);

	// Sprite静的初期化処理
	Sprite::StaticInitialize(dx->GetDevice(), dx->GetCommandList());

	// DebugText初期化処理
	// インスタンスの取得
	debugText = DebugText::GetInstance();
	debugText->Initialize();

	// ライトグループ初期化処理
	LightGroup::StaticInitialize(dx->GetDevice());

	// Object3D静的初期化処理
	Object3d::StaticInitialize(dx->GetDevice());

	// パーティクル共通初期化処理
	ParticleManager::GetInstance()->Initialize(dx->GetDevice());

	// シーンの静的初期化
	BaseScene::SetDirectXBase(dx);

	// シーンマネージャーのインスタンスを取得
	sceneManager = SceneManager::GetInstance();
	sceneManager->Initialize(new GamePlayScene());
}

void Framework::Finalize()
{
	// Audioの終了処理
	audio->Finalize();
	// デバッグテキストの終了処理
	debugText->Finalize();
	// シーンマネージャー終了処理
	sceneManager->Finalize();
	// DirectX基盤解放
	safe_delete(dx);
	// WindowsAPIの終了処理
	win->Finalize();
	// WindowsAPI解放
	safe_delete(win);
}

void Framework::Loop()
{
	// ゲームループ
	while (true)
	{
		// メッセージ処理
		if (win->ProcessMessage() || input->PushKey(DIK_ESCAPE)) { break; }
		// 更新処理
		Update();
		// 描画処理
		Draw();
	}
}

void Framework::Update()
{
	// Input更新処理
	input->Update();
	// Scene更新処理
	sceneManager->Update();

}

void Framework::Draw()
{
	// コマンドリストを取得
	ID3D12GraphicsCommandList* cmdList = dx->GetCommandList();

	// 描画前処理
	dx->PreDraw();
	// 描画後処理
	//// Scene描画処理
	sceneManager->Draw();
	// デバッグテキストの全描画
	debugText->DrawAll(cmdList);
	dx->PostDraw();
}