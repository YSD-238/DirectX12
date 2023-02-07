#include "BaseScene.h"
#include "CollisionManager.h";
#include "SceneManager.h";

DirectXBase* BaseScene::dx = nullptr;

void BaseScene::Initialize()
{
	// NULL検出
	assert(dx);

	this->dx = dx;

	// インスタンス取得
	debugText = DebugText::GetInstance();
	input = Input::GetInstance();
	audio = Audio::GetInstance();
	spriteCommon = SpriteCommon::GetInstance();
	particleMan = ParticleManager::GetInstance();
	collisionMan = CollisionManager::GetInstance();
	sceneManager = SceneManager::GetInstance();

	// カメラ生成処理
	camera = new Camera(WindowsApplication::window_width, WindowsApplication::window_height);
	Object3d::SetCamera(camera);

	// ライトグループの生成処理
	lightGroup = LightGroup::Create();
	Object3d::SetLightGroup(lightGroup);

}

void BaseScene::Finalize()
{
	safe_delete(camera);
	safe_delete(lightGroup);
}
