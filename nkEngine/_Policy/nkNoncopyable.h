/**
* Noncopy�|���V�[.
*/
#pragma once

/**
* �m���R�s�[�A�u���N���X.
* �N���X�̃R�s�[���֎~����N���X.
*/
class Noncopyable
{
public: 

	/**
	* �f�t�H���g�R���X�g���N�^.
	*/
	Noncopyable() = default;

	/**
	* �R�s�[�R���X�g���N�^���폜.
	*/
	Noncopyable(const Noncopyable&) = delete;

	/**
	* ������Z�q���폜.
	*/
	Noncopyable& operator=(const Noncopyable&) = delete;

};