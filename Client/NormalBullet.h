
#include "Bullet.h"
class CNormalBullet :
	public CBullet
{
public:
	CNormalBullet();
	virtual ~CNormalBullet();

	// CBullet��(��) ���� ��ӵ�
	virtual HRESULT Initialize() override;
	virtual void LateInit() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;


};