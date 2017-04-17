/**
* �Z�[�u�f�[�^�֌W���Ǘ�����N���X�̒�`.
*/
#pragma once

/**
* �Z�[�u�f�[�^�֌W���Ǘ�����N���X.
*/
class CSaveData : Noncopyable
{
private:

	/**
	* �R���X�g���N�^.
	*/
	CSaveData()
	{
	}
	
	/**
	* �f�X�g���N�^.
	*/
	~CSaveData()
	{
	}

public:

	/**
	* �C���X�^���X�̎擾.
	*/
	static CSaveData& GetInstance()
	{
		static CSaveData instance;
		return instance;
	}

	/**
	* �ǂݎ��.
	*
	* @return true or false.
	*/
	bool Load();

	/**
	* ��������.
	*/
	void Save();

	/**
	* �f�[�^�I�u�W�F�N�g�̎擾.
	*
	* @return �I�u�W�F�N�g.
	*/
	picojson::object& GetDataObject()
	{
		return Data_.GetDataObject();
	}

	/**
	* �f�[�^�I�u�W�F�N�g�̎擾.
	*
	* @param key	�L�[.
	*
	* @return �I�u�W�F�N�g.
	*/
	picojson::object& GetDataObject(string key)
	{
		return Data_.GetDataObject(key);
	}

	/**
	* �I�u�W�F�N�g��o�^����.
	*
	* @param key	�L�[.
	* @param obj	�I�u�W�F�N�g.
	*/
	void SetDataObject(string key, picojson::object& obj)
	{
		Data_.SetDataObject(key, obj);
	}

	/**
	* �I�u�W�F�N�g��o�^����.
	*
	* @param key	�L�[.
	* @param arr	�z��.
	*/
	void SetDataObject(string key, picojson::array& arr)
	{
		Data_.SetDataObject(key, arr);
	}

	/**
	* �R���e�B�j���[��Ԃ�����.
	*/
	bool IsContinue()
	{
		return isContinue_;
	}

	/**
	* �Z�[�u���s���I�u�W�F�N�g�͓o�^����.
	*/
	void SetSaveObject(IGameObject* obj)
	{
		SaveObject_.push_back(obj);
	}

private:

	/** �t�@�C����. */
	string FileName_ = "Save_01";
	/** Json�̃f�[�^. */
	JsonData Data_;

	/** ��������s���t���O. */
	bool isContinue_ = false;
	
	vector<IGameObject*> SaveObject_;

};

/**
* �Z�[�u�f�[�^�֘A�̊Ǘ����s��.
*/
static CSaveData& SaveData()
{
	return CSaveData::GetInstance();
}