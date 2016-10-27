class Demo : public CGameObject
{
public:
	Demo();
	~Demo();
	void Init()override;
	void Update()override;
	void Render()override;
	void Release()override;
private:

};