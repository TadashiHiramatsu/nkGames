/**
* JsonData���Ǘ�����N���X�̒�`.
*/
#pragma once

namespace nkEngine
{

	/**
	* JsonData���Ǘ�����N���X.
	* �V���O���g���N���X.
	*/
	class CJsonData : Noncopyable
	{
	private:

		/**
		* �R���X�g���N�^
		*/
		CJsonData()
		{
			FilePath_ = "Asset/Data/SaveData.json";
		}

		/**
		* �f�X�g���N�^.
		*/
		~CJsonData()
		{
		}

	public:

		/**
		* �C���X�^���X�̎擾.
		*/
		static CJsonData& GetInstance()
		{
			static CJsonData instance;
			return instance;
		}

	public:

		/**
		* �ǂݍ���.
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
		* @param key	�L�[.
		*
		* @return �I�u�W�F�N�g.
		*/
		picojson::object& GetObject(string key)
		{
			if (DataObject_[key].is<picojson::object>())
			{
				return DataObject_[key].get<picojson::object>();
			}
			NK_ASSERT(false, "�f�[�^�����݂��Ă��܂���");
		}

		/**
		* �I�u�W�F�N�g��o�^����.
		*
		* @param key	�L�[.
		* @param obj	�I�u�W�F�N�g.
		*/
		void SetObject(string key, picojson::object& obj)
		{
			DataObject_[key] = picojson::value(obj);
		}

		/**
		* �I�u�W�F�N�g��o�^����.
		*
		* @param key	�L�[.
		* @param arr	�z��.
		*/
		void SetObject(string key, picojson::array& arr)
		{
			DataObject_[key] = picojson::value(arr);
		}
		

	private:

		/** �f�[�^�I�u�W�F�N�g. */
		picojson::object DataObject_;

		/** �Z�[�u�t�@�C���p�X. */
		string FilePath_;

	};

	/**
	* JsonData�Ǘ��N���X.
	*/
	static CJsonData& JsonData()
	{
		return CJsonData::GetInstance();
	}

}