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
	// ����������
	Initialize();
	// �Q�[�����[�v
	Loop();
	// �I������
	Finalize();
}

void Framework::Initialize()
{
	// WindowsAPI�̏���������
	win = new WindowsApplication();
	win->Initialize();

	// DirectX�̏���������
	dx = new DirectXBase();
	dx->Initialize(win);

	// Input�N���X����������
	// �C���X�^���X�擾
	input = Input::GetInstance();
	if (!input->Initialize(win)) {
		assert(0);
		return;
	}

	// Audio����������
	// �C���X�^���X�擾
	audio = Audio::GetInstance();
	if (!audio->Initialize()) {
		assert(0);
		return;
	}

	// SpriteCommon���ʏ�����
	SpriteCommon::GetInstance()->Initialize(dx->GetDevice(), dx->GetCommandList(), 
		WindowsApplication::window_width, WindowsApplication::window_height);

	// Sprite�ÓI����������
	Sprite::StaticInitialize(dx->GetDevice(), dx->GetCommandList());

	// DebugText����������
	// �C���X�^���X�̎擾
	debugText = DebugText::GetInstance();
	debugText->Initialize();

	// ���C�g�O���[�v����������
	LightGroup::StaticInitialize(dx->GetDevice());

	// Object3D�ÓI����������
	Object3d::StaticInitialize(dx->GetDevice());

	// �p�[�e�B�N�����ʏ���������
	ParticleManager::GetInstance()->Initialize(dx->GetDevice());

	// �V�[���̐ÓI������
	BaseScene::SetDirectXBase(dx);

	// �V�[���}�l�[�W���[�̃C���X�^���X���擾
	sceneManager = SceneManager::GetInstance();
	sceneManager->Initialize(new GamePlayScene());
}

void Framework::Finalize()
{
	// Audio�̏I������
	audio->Finalize();
	// �f�o�b�O�e�L�X�g�̏I������
	debugText->Finalize();
	// �V�[���}�l�[�W���[�I������
	sceneManager->Finalize();
	// DirectX��Չ��
	safe_delete(dx);
	// WindowsAPI�̏I������
	win->Finalize();
	// WindowsAPI���
	safe_delete(win);
}

void Framework::Loop()
{
	// �Q�[�����[�v
	while (true)
	{
		// ���b�Z�[�W����
		if (win->ProcessMessage() || input->PushKey(DIK_ESCAPE)) { break; }
		// �X�V����
		Update();
		// �`�揈��
		Draw();
	}
}

void Framework::Update()
{
	// Input�X�V����
	input->Update();
	// Scene�X�V����
	sceneManager->Update();

}

void Framework::Draw()
{
	// �R�}���h���X�g���擾
	ID3D12GraphicsCommandList* cmdList = dx->GetCommandList();

	// �`��O����
	dx->PreDraw();
	// �`��㏈��
	//// Scene�`�揈��
	sceneManager->Draw();
	// �f�o�b�O�e�L�X�g�̑S�`��
	debugText->DrawAll(cmdList);
	dx->PostDraw();
}