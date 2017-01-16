/**
 * @file _Component\nkTransform.h
 *
 * トランスフォームクラスの定義.
 */
#pragma once

namespace nkEngine
{

	/**
	 * トランスフォームクラス.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	class Transform
	{
	public:

		/**
		 * コンストラクタ.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 */
		Transform();

		/**
		 * デストラクタ.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 */
		~Transform();

		/**
		 * ワールド行列などの更新.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 */
		void Update();

		/**
		 * ビルボードする更新.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/16
		 */
		void BillboardUpdate(const D3DXMATRIX& rot);
	
	public:

		/** 親子関係を持つ親のTransformクラスのポインタ. */
		Transform* Parent_;
		/** 親にする行列. */
		D3DXMATRIX* ParentMatrix_;

		/** 位置ベクトル. */
		D3DXVECTOR3 Position_;
		/** 拡大ベクトル. */
		D3DXVECTOR3 Scale_;
		/** 回転ベクトル. */
		D3DXQUATERNION Rotation_;

		/** ローカルのワールド行列. */
		D3DXMATRIX LocalMatrix_;
		/** ワールド行列. */
		D3DXMATRIX WorldMatrix_;
		/** ワールド行列の逆行列. */
		D3DXMATRIX WorldInvMatrix_;
		/** 回転行列. */
		D3DXMATRIX RotationMatrix_;

	};

}// namespace nkEngine