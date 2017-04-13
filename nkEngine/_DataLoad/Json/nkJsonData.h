/**
* JsonDataを管理するクラスの定義.
*/
#pragma once

namespace nkEngine
{

	/**
	* JsonDataを管理するクラス.
	* シングルトンクラス.
	*/
	class CJsonData : Noncopyable
	{
	private:

		/**
		* コンストラクタ
		*/
		CJsonData()
		{
			FilePath_ = "Asset/Data/SaveData.json";
		}

		/**
		* デストラクタ.
		*/
		~CJsonData()
		{
		}

	public:

		/**
		* インスタンスの取得.
		*/
		static CJsonData& GetInstance()
		{
			static CJsonData instance;
			return instance;
		}

	public:

		/**
		* 読み込み.
		*
		* @return true or false.
		*/
		bool Load();

		/**
		* 書き込み.
		*/
		void Save();

		/**
		* データオブジェクトの取得.
		*
		* @param key	キー.
		*
		* @return オブジェクト.
		*/
		picojson::object& GetObject(string key)
		{
			if (DataObject_[key].is<picojson::object>())
			{
				return DataObject_[key].get<picojson::object>();
			}
			NK_ASSERT(false, "データが存在していません");
		}

		/**
		* オブジェクトを登録する.
		*
		* @param key	キー.
		* @param obj	オブジェクト.
		*/
		void SetObject(string key, picojson::object& obj)
		{
			DataObject_[key] = picojson::value(obj);
		}

		/**
		* オブジェクトを登録する.
		*
		* @param key	キー.
		* @param arr	配列.
		*/
		void SetObject(string key, picojson::array& arr)
		{
			DataObject_[key] = picojson::value(arr);
		}
		

	private:

		/** データオブジェクト. */
		picojson::object DataObject_;

		/** セーブファイルパス. */
		string FilePath_;

	};

	/**
	* JsonData管理クラス.
	*/
	static CJsonData& JsonData()
	{
		return CJsonData::GetInstance();
	}

}