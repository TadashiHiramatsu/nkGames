/**
* JsonData���Ǘ�����N���X�̎���.
*/
#include"nkEngine/nkstdafx.h"
#include"nkJsonData.h"

namespace nkEngine
{

	/**
	* �ǂݍ���.
	*/
	bool CJsonData::Load()
	{
		ifstream file_in;
		file_in.open(FilePath_);

		if (file_in.fail())
		{
			return false;
		}

		picojson::value DataValue;

		file_in >> DataValue;

		DataObject_ = DataValue.get<picojson::object>();

		return true;
	}

	/**
	* ��������.
	*/
	void CJsonData::Save()
	{
		picojson::value DataValue(DataObject_);

		ofstream file_out;
		file_out.open(FilePath_);

		file_out << DataValue.serialize(true);

	}

}