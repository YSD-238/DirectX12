#include "Framework.h"

/// <summary>
///  WindowsAPIのポインタ
/// </summary>
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	// ゲームの宣言
	Framework* myGame = new Framework;
	// 実行処理
	myGame->Run();
	// ゲームの解放
	safe_delete(myGame);
	return 0;
}