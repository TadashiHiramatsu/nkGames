/**
 * @file	_DataLoad\CSVData.h
 *
 * CSVファイルロードクラスの定義.
 */
#pragma once

 //ファイル関連
#include<fstream>
 //文字ストリーム
#include<sstream>
#include<string>

namespace nkEngine
{

	typedef vector<vector<string>> CSVDataTableT;

	/**
	 * CSVファイル読み込みクラス.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/04
	 */
	class CSVData
	{
	public:

		/**
		 * 読み込み.
		 * "Asset/Data/"フォルダ内のCSVファイルを読み込む.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/04
		 *
		 * @param [in]	  	filePath	"Asset/Data/"を省いたファイルパス.
		 * @param [in,out]	table   	この引数にデータが返ってくる.
		 */
		static void Load(const char* filePath, CSVDataTableT& table)
		{
			//ファイルパスの作成
			char fileP[1024];
			sprintf(fileP, "Asset/Data/%s.csv", filePath);

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
				table.push_back(record);
			}

		}

	};

}// namespace nkEngine