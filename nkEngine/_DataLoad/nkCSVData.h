/**
 * @file	_DataLoad\CSVData.h
 *
 * CSV�t�@�C�����[�h�N���X�̒�`.
 */
#pragma once

 //�t�@�C���֘A
#include<fstream>
 //�����X�g���[��
#include<sstream>
#include<string>

namespace nkEngine
{

	typedef vector<vector<string>> CSVDataTableT;

	/**
	 * CSV�t�@�C���ǂݍ��݃N���X.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/04
	 */
	class CSVData
	{
	public:

		/**
		 * �ǂݍ���.
		 * "Asset/Data/"�t�H���_����CSV�t�@�C����ǂݍ���.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/04
		 *
		 * @param [in]	  	filePath	"Asset/Data/"���Ȃ����t�@�C���p�X.
		 * @param [in,out]	table   	���̈����Ƀf�[�^���Ԃ��Ă���.
		 */
		static void Load(const char* filePath, CSVDataTableT& table)
		{
			//�t�@�C���p�X�̍쐬
			char fileP[1024];
			sprintf(fileP, "Asset/Data/%s.csv", filePath);

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
				table.push_back(record);
			}

		}

	};

}// namespace nkEngine