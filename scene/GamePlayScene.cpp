#include "GamePlayScene.h"

void GamePlayScene::Initialize()
{
	// �V�[����Տ���������
	BaseScene::Initialize();

}

void GamePlayScene::Finalize()
{
	// �V�[����ՏI������
	BaseScene::Finalize();
}

void GamePlayScene::Update()
{
}

void GamePlayScene::Draw()
{
	// �R�}���h���X�g�̎擾
	ID3D12GraphicsCommandList* cmdList = dx->GetCommandList();

#pragma region �w�i�X�v���C�g�`��
	// �w�i�X�v���C�g�`��O����
	spriteCommon->PreDraw();
	// �w�i�X�v���C�g�`��
	

	/// <summary>
	/// �����ɔw�i�X�v���C�g�̕`�揈����ǉ��ł���
	/// </summary>

#pragma endregion

#pragma region 3D�I�u�W�F�N�g�`��
	// 3D�I�u�W�F�N�g�`��O����
	Object3d::PreDraw(cmdList);

	// 3D�I�u�N�W�F�N�g�̕`��


	/// <summary>
	/// ������3D�I�u�W�F�N�g�̕`�揈����ǉ��ł���
	/// </summary>

	// 3D�I�u�W�F�N�g�`��㏈��
	Object3d::PostDraw();
#pragma endregion

#pragma region �O�i�X�v���C�g�`��
	// �O�i�X�v���C�g�`��O����
	spriteCommon->PreDraw();

	/// <summary>
	/// �����ɑO�i�X�v���C�g�̕`�揈����ǉ��ł���
	/// </summary>

	//// �`��

	// �f�o�b�O�e�L�X�g�̕`��
	debugText->DrawAll(cmdList);

#pragma endregion
}
