/**
* Noncopyポリシー.
*/
#pragma once

/**
* ノンコピーアブルクラス.
* クラスのコピーを禁止するクラス.
*/
class Noncopyable
{
public: 

	/**
	* デフォルトコンストラクタ.
	*/
	Noncopyable() = default;

	/**
	* コピーコンストラクタを削除.
	*/
	Noncopyable(const Noncopyable&) = delete;

	/**
	* 代入演算子を削除.
	*/
	Noncopyable& operator=(const Noncopyable&) = delete;

};