#include"nkEngine/nkstdafx.h"
#include"nkParticleEmitter.h"

namespace nkEngine
{
	CParticleEmitter::CParticleEmitter():
		isCreate(false)
	{
	}
	CParticleEmitter::~CParticleEmitter()
	{
	}

	void CParticleEmitter::Init(CCamera* _Camera, const SParicleEmitParameter& _Param, D3DXVECTOR3* _EmitPosition)
	{
		camera = _Camera;
		param = _Param;
		EmitPosition = _EmitPosition;
		timer = 0.0f;

		m_pTextures.Load(_Param.texturePath);
	}

	void CParticleEmitter::Update()
	{
		if (timer >= param.intervalTime && isCreate) {
			//パーティクルを生成。
			CParticle* p = new CParticle();
			p->Init(camera, param, EmitPosition);
			timer = 0.0f;
			particleList.push_back(p);
		}
		timer += Time().DeltaTime();
		std::list<CParticle*>::iterator p = particleList.begin();
		while (p != particleList.end()) {
			if ((*p)->GetDead()) {
				p = particleList.erase(p);
			}
			else {
				p++;
			}
		}
		p = particleList.begin();
		while (p != particleList.end()) {
			(*p++)->Update();
		}
	}

	void CParticleEmitter::AddForce(const D3DXVECTOR3& _AddForce)
	{
		for (auto p : particleList) {
			p->AddForce(_AddForce);
		}
	}

	void CParticleEmitter::Render()
	{
		std::list<CParticle*>::iterator p = particleList.begin();
		while (p != particleList.end()) {
			(*p++)->Render(m_pTextures.GetTextureDX());
		}
	}
}