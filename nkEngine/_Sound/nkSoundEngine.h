/**
* サウンドエンジンクラスの定義.
*/
#pragma once

#include"nkWaveFileBank.h"
#include"../_Math/nkVector.h"

#define INPUTCHANNELS 2		//!< number of source channels
#define OUTPUTCHANNELS 8	//!< 最大出力チャンネル数.

namespace nkEngine
{
	class WaveFile;
	class SoundSource;

	/**
	* サウンドエンジンクラス.
	*/
	class CSoundEngine : Noncopyable
	{
	public:

		/**
		* コンストラクタ.
		*/
		CSoundEngine()
		{
			memset(X3DAudioHandle_, 0, sizeof(X3DAudioHandle_));
		}

		/**
		* デストラクタ.
		*/
		~CSoundEngine()
		{
			Release();
		}

		/**
		* 初期化.
		*/
		void Init();

		/**
		* 更新.
		*/
		void Update();

		/**
		* 解放.
		*/
		void Release();

		/**
		* 3Dサウンドソースを追加.
		*
		* @param s	サウンドソース.
		*/
		void Add3DSoundSource(SoundSource* s)
		{
			SoundSource3DList_.push_back(s);
		}

		/**
		* 3Dサウンドソースの削除.
		*/
		void Remove3DSoundSource(SoundSource* s)
		{
			auto& it = find(SoundSource3DList_.begin(), SoundSource3DList_.end(), s);
			if (it != SoundSource3DList_.end())
			{
				SoundSource3DList_.erase(it);
			}
		}

		/**
		* サウンドリスナーの座標を設定.
		*
		* @param pos	位置ベクトル.
		*/
		void SetListenerPosition(const Vector3& pos)
		{
			ListenerPosition_ = pos;
		}

		/**
		* サウンドリスナーの前方向を設定.
		*
		* @param front	前方向ベクトル.
		*/
		void SetListenerFront(const Vector3& front)
		{
			front.CopyTo(Listener_.OrientFront);
		}

		/**
		* サウンドリスナーの上方向を設定.
		*
		* @param up		上方向ベクトル.
		*/
		void SetListenerUp(const Vector3& up)
		{
			up.CopyTo(Listener_.OrientTop);
		}

		/**
		* XAudio2のソースボイスを作成.
		*
		* @param wavefile	波形データ.
		* @param is3Dsound	3Dサウンドフラグ.
		*/
		IXAudio2SourceVoice* CreateSourceVoice(WaveFile* wavefile, bool is3Dsound);

		/**
		* マスターボイスを取得.
		*/
		IXAudio2MasteringVoice* GetMasteringVoice()
		{
			return MasteringVoice_;
		}

		/**
		* サブミックスボイスの取得.
		*/
		IXAudio2SubmixVoice* GetSubmixVoice()
		{
			return SubmixVoice_;
		}

		/**
		* 出力チャンネル数を取得.
		*/
		int GetChannelNum() const
		{
			return ChannelNum_;
		}

		/**
		* 波形データバンクを取得.
		*/
		WaveFileBank& GetWaveFileBank()
		{
			return WaveFileBank_;
		}


	private:

		/** 初期化フラグ. */
		bool isInit = false;

		/** XAudio2のインターフェイス. */
		IXAudio2* XAudio2_ = nullptr;
		/** マスターボイス. */
		IXAudio2MasteringVoice* MasteringVoice_ = nullptr;
		/** 3Dオーディオのハンドル. */
		X3DAUDIO_HANDLE X3DAudioHandle_;
		/** リバーブエフェクト. */
		IUnknown* ReverbEffect_ = nullptr;
		/** サブミックスボイス. */
		IXAudio2SubmixVoice* SubmixVoice_ = nullptr;
		/** オーディオチャンネルマスク. */
		DWORD ChannnelMask_;
		/** チャンネル数. */
		DWORD ChannelNum_;
		
		/** サウンドリスナー. */
		X3DAUDIO_LISTENER Listener_;
		/** リスナーの位置. */
		Vector3 ListenerPosition_ = Vector3::Zero;
		/** リスナーの角度. */
		float ListenerAngle_ = 0;
		/** リスナーコーンフラグ. */
		bool isListenerCone_ = false;
		/** 円半径フラグ. */
		bool isInnerRadius_ = false;
		
		/** 低音増強フラグ?. */
		bool isRedirectToLFE_ = false;
		
		/** 3Dサウンドソースリスト. */
		list<SoundSource*> SoundSource3DList_;
		
		/** エミッターコーン. */
		X3DAUDIO_CONE EmitterCone_;

		/** 波形データバンク. */
		WaveFileBank WaveFileBank_;
	
	};

}