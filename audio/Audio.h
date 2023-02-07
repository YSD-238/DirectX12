#pragma once

#include <Windows.h>
#include <xaudio2.h>
#include <wrl.h>
#include <unordered_map>
#include <string>

/// <summary>
/// オーディオ
/// </summary>
class Audio
{
private: // エイリアス
	// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

public: // 静的メンバ関数
	/// <summary>
	/// インスタンスの取得
	/// </summary>
	/// <returns>インスタンス</returns>
	static Audio* GetInstance();

public: // サブクラス
	/// <summary>
	/// チャンクヘッダ
	/// </summary>
	struct ChunkHeader
	{
		char id[4]; // チャンク毎のID
		int32_t size;  // チャンクサイズ
	};

	/// <summary>
	/// RIFFヘッダチャンク
	/// </summary>
	struct RiffHeader
	{
		ChunkHeader chunk;   // "RIFF"
		char type[4]; // "WAVE"
	};

	/// <summary>
	/// FMTチャンク
	/// </summary>
	struct FormatChunk
	{
		ChunkHeader chunk; // "fmt "
		WAVEFORMATEX fmt; // 波形フォーマット
	};

	/// <summary>
	/// 音声データ
	/// </summary>
	struct SoundData
	{
		// 波形フォーマット
		WAVEFORMATEX wfex;
		// バッファの先頭アドレス
		BYTE* pBuffer;

		// バッファのサイズ
		unsigned int bufferSize;
	};

public: // メンバ関数
	/// <summary>
	/// 初期化処理
	/// </summary>
	/// <returns>成否</returns>
	bool Initialize();

	/// <summary>
	/// 終了処理
	/// </summary>
	void Finalize();

	/// <summary>
	/// WAVE音声読み込み
	/// </summary>
	/// <param name="filename">ファイル名</param>
	void LoadWave(const char* filename);

	/// <summary>
	/// 音声再生
	/// </summary>
	/// <param name="filename">ファイル名</param>
	/// <param name="loopFlag">ループフラグ</param>
	void PlayWave(const char* filename, bool loopFlag);

	/// <summary>
	/// 音声を止める
	/// </summary>
	/// <param name="filename">ファイル名</param>
	void Stop(const char* filename);

	/// <summary>
	/// 音量の取得
	/// </summary>
	/// <param name="filename">ファイル名</param>
	/// <returns>音量</returns>
	float GetVolume(const char* filename);

	/// <summary>
	/// 音量の設定
	/// </summary>
	/// <param name="filename">ファイル名</param>
	/// <param name="volume">音量</param>
	void SetVolume(const char* filename, float& volume);

private: // メンバ関数
	/// <summary>
	/// サウンドデータの解放
	/// </summary>
	void Unload(SoundData* saundoData);

	Audio() = default;
	Audio(const Audio&) = delete;
	~Audio() = default;
	Audio& operator=(const Audio&) = delete;
private: // メンバ変数
	// ディレクトリーパス
	const std::string directoryPath = "Resources/Audio/";
	// xAudioのインスタンス
	ComPtr<IXAudio2> xAudio2;
	// サウンドデータ配列
	std::unordered_map<std::string, SoundData> soundDatas;
	// サウンドボイス配列
	std::unordered_map<std::string, IXAudio2SourceVoice*> pSourceVoices;
};
