#include "Sprite.h"
#include <cassert>

SpriteCommon* Sprite::spriteCommon = nullptr;
ID3D12Device* Sprite::dev = nullptr;
ID3D12GraphicsCommandList* Sprite::cmdList = nullptr;

using namespace DirectX;

void Sprite::StaticInitialize(ID3D12Device* dev, ID3D12GraphicsCommandList* cmdList)
{
	// NULL検出
	assert(dev);
	assert(cmdList);

	Sprite::dev = dev;
	Sprite::cmdList = cmdList;
	Sprite::spriteCommon = SpriteCommon::GetInstance();
}

Sprite::Sprite(UINT texNumber, XMFLOAT2 position, XMFLOAT2 size, XMFLOAT4 color, XMFLOAT2 anchorpoint, bool isFlipX, bool isFlipY)
{
	this->texNumber = texNumber;
	this->position = position;
	this->size = size;
	this->color = color;
	this->anchorpoint = anchorpoint;
	this->isFlipX = isFlipX;
	this->isFlipY = isFlipY;
}

Sprite::~Sprite()
{
}

void Sprite::Initialize()
{
	HRESULT result = S_FALSE;

	this->texNumber = texNumber;
	this->anchorpoint = anchorpoint;
	this->isFlipX = isFlipX;
	this->isFlipY = isFlipY;

	// 頂点データ
	VertexPosUv vertices[4];

	// 指定番号の画像が読み込み済みなら
	if (spriteCommon->GetTexBuff(texNumber)) {
		// テクスチャ情報取得
		D3D12_RESOURCE_DESC resDesc = spriteCommon->GetTexBuff(texNumber)->GetDesc();

		// スプライトの大きさを画像の解像度に合わせる
		size = { (float)resDesc.Width, (float)resDesc.Height };
		texSize = { (float)resDesc.Width, (float)resDesc.Height };
	}

	// 頂点バッファ生成
	result = dev->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer(sizeof(vertices)),
		D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&vertBuff));

	// 頂点バッファデータ転送
	TransferVertexBuffer();

	// 頂点バッファビューの作成
	vbView.BufferLocation = vertBuff->GetGPUVirtualAddress();
	vbView.SizeInBytes = sizeof(vertices);
	vbView.StrideInBytes = sizeof(vertices[0]);

	// 定数バッファの生成
	result = dev->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer((sizeof(ConstBufferData) + 0xff) & ~0xff),
		D3D12_RESOURCE_STATE_GENERIC_READ, nullptr,
		IID_PPV_ARGS(&constBuff));

	// 定数バッファにデータ転送
	ConstBufferData* constMap = nullptr;
	result = constBuff->Map(0, nullptr, (void**)&constMap);
	constMap->color = XMFLOAT4(1, 1, 1, 1); // 色指定（RGBA）
	constMap->mat = spriteCommon->GetMatProjection();
	constBuff->Unmap(0, nullptr);
}

void Sprite::TransferVertexBuffer()
{
	HRESULT result = S_FALSE;

	// 頂点データ
	VertexPosUv vertices[] = {
		//     u     v
		{{}, {0.0f, 1.0f}}, // 左下
		{{}, {0.0f, 0.0f}}, // 左上
		{{}, {1.0f, 1.0f}}, // 右下
		{{}, {1.0f, 0.0f}}, // 右上
	};

	// 左下、左上、右下、右上
	enum { LB, LT, RB, RT };

	float left = (0.0f - anchorpoint.x) * size.x;
	float right = (1.0f - anchorpoint.x) * size.x;
	float top = (0.0f - anchorpoint.y) * size.y;
	float bottom = (1.0f - anchorpoint.y) * size.y;

	if (isFlipX)
	{// 左右入れ替え
		left = -left;
		right = -right;
	}

	if (isFlipY)
	{// 左右入れ替え
		top = -top;
		bottom = -bottom;
	}

	vertices[LB].pos = { left, bottom,  0.0f }; // 左下
	vertices[LT].pos = { left, top,     0.0f }; // 左上
	vertices[RB].pos = { right, bottom, 0.0f }; // 右下
	vertices[RT].pos = { right, top,    0.0f }; // 右上

	// 指定番号の画像が読み込み済みなら
	if (spriteCommon->GetTexBuff(texNumber)) {
		// テクスチャ情報取得
		D3D12_RESOURCE_DESC resDesc = spriteCommon->GetTexBuff(texNumber)->GetDesc();

		float tex_left = texLeftTop.x / resDesc.Width;
		float tex_right = (texLeftTop.x + texSize.x) / resDesc.Width;
		float tex_top = texLeftTop.y / resDesc.Height;
		float tex_bottom = (texLeftTop.y + texSize.y) / resDesc.Height;

		vertices[LB].uv = { tex_left,   tex_bottom }; // 左下
		vertices[LT].uv = { tex_left,   tex_top }; // 左上
		vertices[RB].uv = { tex_right,  tex_bottom }; // 右下
		vertices[RT].uv = { tex_right,  tex_top }; // 右上
	}

	// 頂点バッファへのデータ転送
	VertexPosUv* vertMap = nullptr;
	result = vertBuff->Map(0, nullptr, (void**)&vertMap);
	memcpy(vertMap, vertices, sizeof(vertices));
	vertBuff->Unmap(0, nullptr);
}

Sprite* Sprite::Create(UINT texNumber, XMFLOAT2 position, XMFLOAT4 color, XMFLOAT2 anchorpoint, bool isFlipX, bool isFlipY)
{
	// 仮サイズ
	XMFLOAT2 size = { 100.0f, 100.0f };

	if (spriteCommon->GetTexBuff(texNumber))
	{
		// テクスチャ情報取得
		D3D12_RESOURCE_DESC resDesc = spriteCommon->GetTexBuff(texNumber)->GetDesc();
		// スプライトのサイズをテクスチャのサイズに設定
		size = { (float)resDesc.Width, (float)resDesc.Height };
	}

	// インスタンスの生成
	Sprite* instance = new Sprite(texNumber, position, size, color, anchorpoint, isFlipX, isFlipY);

	instance->Initialize();

	return instance;
}

void Sprite::Update()
{
	//// ワールド行列の更新
	//matWorld = XMMatrixIdentity();
	//// Z軸回転
	//matWorld *= XMMatrixRotationZ(XMConvertToRadians(rotation));
	//// 平行移動
	//matWorld *= XMMatrixTranslation(position.x, position.y, 0.0f);

	//// 定数バッファの転送
	//ConstBufferData* constMap = nullptr;
	//HRESULT result = constBuff->Map(0, nullptr, (void**)&constMap);
	//constMap->mat = matWorld * spriteCommon->GetMatProjection();
	//constMap->color = color;
	//constBuff->Unmap(0, nullptr);
}

void Sprite::Draw()
{
	// ワールド行列の更新
	matWorld = XMMatrixIdentity();
	// Z軸回転
	matWorld *= XMMatrixRotationZ(XMConvertToRadians(rotation));
	// 平行移動
	matWorld *= XMMatrixTranslation(position.x, position.y, 0.0f);

	// 定数バッファの転送
	ConstBufferData* constMap = nullptr;
	HRESULT result = constBuff->Map(0, nullptr, (void**)&constMap);
	constMap->mat = matWorld * spriteCommon->GetMatProjection();
	constMap->color = color;
	constBuff->Unmap(0, nullptr);

	if (isInvisible) {
		return;
	}

	// 頂点バッファをセット
	cmdList->IASetVertexBuffers(0, 1, &vbView);
	// デスクリプタヒープをセット
	spriteCommon->SetDescriptorHeaps();
	// ルートパラメーター0番に定数バッファをセット
	cmdList->SetGraphicsRootConstantBufferView(0, constBuff->GetGPUVirtualAddress());
	// ルートパラメーター1番にシェーダリソースビューをセット
	spriteCommon->SetGraphicsRootDescriptorTable(1, texNumber);
	// ポリゴンの描画（4頂点で四角形）
	cmdList->DrawInstanced(4, 1, 0, 0);
}