#pragma once

class IMenuWindow
{
public:

	//������
	virtual void Start(RectTransform* rt, float namepos) = 0;

	//�X�V
	virtual void Update() = 0;

	//�`��
	virtual void Render() = 0;

	void NameStart(RectTransform* parent, const char* filepath, float pos);

	//�\�����̍X�V
	void NameUpdate()
	{
		NameTransform_.Update();
	}

	//�\�����̕`��
	void NameRender()
	{
		NameImage_.Render();
	}

	RectTransform& GetNameTransform()
	{
		return NameTransform_;
	}

	virtual void Close() 
	{
	}

protected:

	Image NameImage_;
	RectTransform NameTransform_;

};