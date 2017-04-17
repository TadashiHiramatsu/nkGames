/**
* セーブデータ関係を管理するクラスの定義.
*/
#pragma once

/**
* セーブデータ関係を管理するクラス.
*/
class CSaveData : Noncopyable
{
private:

	/**
	* コンストラクタ.
	*/
	CSaveData()
	{
	}
	
	/**
	* デストラクタ.
	*/
	~CSaveData()
	{
	}

public:

	/**
	* インスタンスの取得.
	*/
	static CSaveData& GetInstance()
	{
		static CSaveData instance;
		return instance;
	}

	/**
	* 読み取り.
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
	* @return オブジェクト.
	*/
	picojson::object& GetDataObject()
	{
		return Data_.GetDataObject();
	}

	/**
	* データオブジェクトの取得.
	*
	* @param key	キー.
	*
	* @return オブジェクト.
	*/
	picojson::object& GetDataObject(string key)
	{
		return Data_.GetDataObject(key);
	}

	/**
	* オブジェクトを登録する.
	*
	* @param key	キー.
	* @param obj	オブジェクト.
	*/
	void SetDataObject(string key, picojson::object& obj)
	{
		Data_.SetDataObject(key, obj);
	}

	/**
	* オブジェクトを登録する.
	*
	* @param key	キー.
	* @param arr	配列.
	*/
	void SetDataObject(string key, picojson::array& arr)
	{
		Data_.SetDataObject(key, arr);
	}

	/**
	* コンティニュー状態か判定.
	*/
	bool IsContinue()
	{
		return isContinue_;
	}

	/**
	* セーブを行うオブジェクトは登録する.
	*/
	void SetSaveObject(IGameObject* obj)
	{
		SaveObject_.push_back(obj);
	}

private:

	/** ファイル名. */
	string FileName_ = "Save_01";
	/** Jsonのデータ. */
	JsonData Data_;

	/** 続きから行うフラグ. */
	bool isContinue_ = false;
	
	vector<IGameObject*> SaveObject_;

};

/**
* セーブデータ関連の管理を行う.
*/
static CSaveData& SaveData()
{
	return CSaveData::GetInstance();
}