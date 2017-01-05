/**
 * @file	_DataLoad\CSVData.h
 *
 * Declares the CSV data class.
 */
#pragma once

 //ファイル関連
#include<fstream>
 //文字ストリーム
#include<sstream>
#include<string>

namespace nkEngine
{

	/**
	 * A CSV data.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/04
	 */
	class CSVData
	{
	public:

		/**
		 * Default constructor.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/04
		 */
		CSVData();

		/**
		 * Destructor.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/04
		 */
		~CSVData();

		/**
		 * Loads.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/04
		 *
		 * @param [in]	  	_FilePath	Full pathname of the file.
		 * @param [in,out]	_Table   	The table.
		 */
		void Load(const char* _FilePath, vector<vector<string>>& _Table);
	private:
	};
}