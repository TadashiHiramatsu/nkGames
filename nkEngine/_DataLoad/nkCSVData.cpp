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

		//�t�@�C�����J��
		fstream file(fileP);

		if (!file.is_open())
		{
			//�t�@�C�����J���Ȃ�
			NK_ASSERT(false, "�t�@�C�����J���Ă��܂���");
		}

		//�t�@�C����ǂݍ���
		while (!file.eof())
		{
			//��s�ǂݍ���
			string buffer;
			file >> buffer;

			//�t�@�C������ǂݍ��񂾈�s�̕������","�ŕ����ă��X�g�ɒǉ�����
			vector<string> record; //��s���̃��X�g
			istringstream streambuffer(buffer); //�����X�g���[��
			string token; //�P�Z�����̕�����

			while (getline(streambuffer, token, ','))
			{
				//1�Z�����̕���������X�g�ɒǉ�����
				record.push_back(token);
			}

			//1�s���̕�������o�͈����̃��X�g�ɒǉ�����
			_Table.push_back(record);
		}
	}
}
