#include "BaseScene.h"
#include "CollisionManager.h";
#include "SceneManager.h";

DirectXBase* BaseScene::dx = nullptr;

void BaseScene::Initialize()
{
	// NULL���o
	assert(dx);

	this->dx = dx;

	// �C���X�^���X�擾
	debugText = DebugText::GetInstance();
	input = Input::GetInstance();
	audio = Audio::GetInstance();
	spriteCommon = SpriteCommon::GetInstance();
	particleMan = ParticleManager::GetInstance();
	collisionMan = CollisionManager::GetInstance();
	sceneManager = SceneManager::GetInstance();

	// �J������������
	camera = new Camera(WindowsApplication::window_width, WindowsApplication::window_height);
	Object3d::SetCamera(camera);

	// ���C�g�O���[�v�̐�������
	lightGroup = LightGroup::Create();
	Object3d::SetLightGroup(lightGroup);

}

void BaseScene::Finalize()
{
	safe_delete(camera);
	safe_delete(lightGroup);
}
