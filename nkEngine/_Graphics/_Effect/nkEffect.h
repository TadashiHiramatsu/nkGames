/**
 * @file _Graphics\_Effect\nkEffect.h
 *
 * シェーダエフェクトクラスの定義.
 */
#pragma once

namespace nkEngine
{

	/**
	 * シェーダエフェクトクラス.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/18
	 */
	class Effect
	{
	public:

		/**
		 * コンストラクタ.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/18
		 */
		Effect()
		{
		}

		/**
		 * コンストラクタ.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/18
		 *
		 * @param [in,out] effect If non-null, the effect.
		 */
		Effect(ID3DXEffect* effect) :
			D3DEffect_(effect)
		{
		}

		/**
		 * デストラクタ.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/18
		 */
		~Effect()
		{
		}

		/**
		 * テクニックを設定.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/18
		 *
		 * @param technique テクニック名.
		 */
		void SetTechnique(const char* technique)
		{
			D3DEffect_->SetTechnique(technique);
		}

		/**
		 * テクニックの適応開始.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/18
		 */
		void Begin()
		{
			D3DEffect_->Begin(nullptr, D3DXFX_DONOTSAVESHADERSTATE);
		}
		/**
		 * テクニックの適応開始.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/18
		 *
		 * @param [in,out] pass パス.
		 * @param 		   flag フラグ.
		 */
		void Begin(UINT* pass,DWORD flag)
		{
			D3DEffect_->Begin(pass, flag);
		}

		/**
		 * 使用するテクニックのパスを設定して描画開始.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/18
		 *
		 * @param pass パス.
		 */
		void BeginPass(int pass)
		{
			D3DEffect_->BeginPass(pass);
		}

		/**
		 * 設定した値をGPUに送る.
		 * だったはず.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/18
		 */
		void CommitChanges()
		{
			D3DEffect_->CommitChanges();
		}

		/**
		 * テクニックの適応を終了.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/18
		 */
		void EndPass()
		{
			D3DEffect_->EndPass();
		}

		/**
		 * 描画の終了.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/18
		 */
		void End()
		{
			D3DEffect_->End();
		}


		/**
		 * 値を設定.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/18
		 *
		 * @param name パラメータの名前.
		 * @param data 設定する値.
		 * @param size サイズ（単位:バイト）.
		 */
		void SetValue(const char* name, const void* data, int size)
		{
			D3DEffect_->SetValue(name, data, size);
		}

		/**
		 * 行列を設定.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/18
		 *
		 * @param name   パラメータの名前.
		 * @param matrix 行列のポインタ.
		 */
		void SetMatrix(const char* name, const D3DXMATRIX* matrix)
		{
			D3DEffect_->SetMatrix(name, matrix);
		}

		/**
		 * 行列の配列を設定.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/19
		 *
		 * @param name		  パラメータの名前.
		 * @param matrixarrey 配列の先頭アドレス.
		 * @param size		  サイズ.
		 */
		void SetMatrixArray(const char* name, const D3DXMATRIX* matrixarrey,UINT size)
		{
			D3DEffect_->SetMatrixArray(name, matrixarrey, size);
		}

		/**
		 * テクスチャを設定.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/19
		 *
		 * @param name    パラメータの名前.
		 * @param texture テクスチャクラスのポインタ.
		 */
		void SetTexture(const char* name, const Texture* texture)
		{
			D3DEffect_->SetTexture(name, texture->GetTexture());
		}

		/**
		 * 整数の設定.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/19
		 *
		 * @param name パラメータの名前.
		 * @param idx  整数値.
		 */
		void SetInt(const char* name, const int idx)
		{
			D3DEffect_->SetInt(name, idx);
		}

		/**
		 * ブール型の設定.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/19
		 *
		 * @param name パラメータの名前.
		 * @param flag true or false.
		 */
		void SetBool(const char* name, const bool flag)
		{
			D3DEffect_->SetBool(name, flag);
		}

		/**
		 * ベクトルを設定.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/19
		 * 
		 * @param name パラメータの名前.
		 * @param vec  ベクトルのポインタ.
		 */
		void SetVector(const char* name, const D3DXVECTOR4* vec)
		{
			D3DEffect_->SetVector(name, vec);
		}

	private:

		/** D3Dシェーダエフェクト. */
		ID3DXEffect* D3DEffect_;

	};

}// namespace nkEngine