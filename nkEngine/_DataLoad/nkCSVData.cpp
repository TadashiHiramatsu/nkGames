/**
 * @file	_DataLoad\CSVData.cpp
 *
 * Implements the CSV data class.
 */
#include"nkEngine/nkstdafx.h"
#include"nkCSVData.h"

namespace nkEngine
{

	/**
	 * Default constructor.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/04
	 */
	CSVData::CSVData()
	{
	}

	/**
	 * Destructor.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/04
	 */
	CSVData::~CSVData()
	{
	}

	/**
	 * Loads.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/04
	 *
	 * @param 		  	_FilePath	Full pathname of the file.
	 * @param [in,out]	_Table   	The table.
	 */
	void CSVData::Load(const char * _FilePath, vector<vector<string>>& _Table)
	{
		char* baseDir = "Asset/Data/";
		char fileP[64];
		strcpy(fileP, baseDir);
		strcat(fileP, _FilePath);

		//ファイルを開く
		fstream file(fileP);

		if (!file.is_open())
		{
			//ファイルが開けない
			NK_ASSERT(false, "ファイルが開けていません");
		}

		//ファイルを読み込む
		while (!file.eof())
		{
			//一行読み込む
			string buffer;
			file >> buffer;

			//ファイルから読み込んだ一行の文字列を","で分けてリストに追加する
			vector<string> record; //一行分のリスト
			istringstream streambuffer(buffer); //文字ストリーム
			string token; //１セル分の文字列

			while (getline(streambuffer, token, ','))
			{
				//1セル分の文字列をリストに追加する
				record.push_back(token);
			}

			//1行分の文字列を出力引数のリストに追加する
			_Table.push_back(record);
		}
	}
}
