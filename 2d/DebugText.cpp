#include "DebugText.h"
#include "SafeDelete.h"

#include <cassert>

DebugText* DebugText::GetInstance()
{
	static DebugText instance;

	return &instance;
}

void DebugText::Initialize()
{
	// SpriteCommonのインスタンスを取得
	spriteCommon = SpriteCommon::GetInstance();

	// デバックテキストをロード
	if (!spriteCommon->LoadTexture(0, L"Resources/debugfont.png")) {
		assert(0);
		return;
	}

	// 全てのスプライトデータについて
	for (int i = 0; i < _countof(spriteDatas); i++)
	{
		// スプライトを生成する
		spriteDatas[i] = Sprite::Create(0);
	}
}

void DebugText::Finalize()
{
	for (auto s : spriteDatas) {
		safe_delete(s);
	}
}

void DebugText::Print(const std::string& text, XMFLOAT2 position, float scale)
{
	// 全ての文字について
	for (int i = 0; i < text.size(); i++)
	{
		// 最大文字数超過
		if (spriteIndex >= maxCharCount) {
			break;
		}

		// 1文字取り出す(※ASCIIコードでしか成り立たない)
		const unsigned char& character = text[i];

		// ASCIIコードの2段分飛ばした番号を計算
		int fontIndex = character - 32;
		if (character >= 0x7f) {
			fontIndex = 0;
		}

		int fontIndexY = fontIndex / fontLineCount;
		int fontIndexX = fontIndex % fontLineCount;

		// 座標計算
		spriteDatas[spriteIndex]->SetPosition({ position.x + fontWidth * scale * i, position.y });
		spriteDatas[spriteIndex]->SetTexLeftTop({ (float)fontIndexX * fontWidth, (float)fontIndexY * fontHeight });
		spriteDatas[spriteIndex]->SetTexSize({ fontWidth, fontHeight });
		spriteDatas[spriteIndex]->SetSize({ fontWidth * scale, fontHeight * scale });
		// 頂点バッファ転送
		spriteDatas[spriteIndex]->TransferVertexBuffer();
		// 更新
		spriteDatas[spriteIndex]->Update();

		// 文字を１つ進める
		spriteIndex++;
	}
}

// まとめて描画
void DebugText::DrawAll(ID3D12GraphicsCommandList* cmdList)
{
	// 全ての文字のスプライトについて
	for (int i = 0; i < spriteIndex; i++)
	{
		// スプライト描画
		spriteDatas[i]->Draw();
	}

	spriteIndex = 0;
}