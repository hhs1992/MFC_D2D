#include "stdafx.h"
#include "TimeMgr.h"

IMPLEMENT_SINGLETON(CTimeMgr)

CTimeMgr::CTimeMgr()
	: m_fTime(0.f)
{
	ZeroMemory(&m_CurTime, sizeof(LARGE_INTEGER));
	ZeroMemory(&m_OldTime1, sizeof(LARGE_INTEGER));
	ZeroMemory(&m_OldTime2, sizeof(LARGE_INTEGER));
	ZeroMemory(&m_CpuTick, sizeof(LARGE_INTEGER));
}


CTimeMgr::~CTimeMgr()
{
}

// ���� �ѹ� �ʱ�ȭ.
void CTimeMgr::InitTime()
{
	// QueryPerformanceCounter: 
	// ���κ��尡 ������ �ִ� ���ػ� Ÿ�̸��� ���� ���� �ð��� ���´�.
	// 1 / 10000 �� ������ ���´�.
	QueryPerformanceCounter(&m_CurTime);
	QueryPerformanceCounter(&m_OldTime1);
	QueryPerformanceCounter(&m_OldTime2);

	// QueryPerformanceFrequency: CPU�� ���� �ֱ⸦ ������ �Լ�. 1�ʿ� ��� �����ϴ°�!
	QueryPerformanceFrequency(&m_CpuTick);
}

// �� �����Ӹ��� �ð� ����.
void CTimeMgr::UpdateTime()
{
	// �� �����Ӹ��� ���� �ð��� ����.
	QueryPerformanceCounter(&m_CurTime);

	// ���� �ð��� ���� �ð��� ���� m_CpuTick�� ���� ��� ����.
	if (m_CurTime.QuadPart - m_OldTime2.QuadPart > m_CpuTick.QuadPart)
	{
		// ���� CPU �������� ���� ���´�.
		QueryPerformanceFrequency(&m_CpuTick);
		m_OldTime2 = m_CurTime;
	}

	m_fTime = float(m_CurTime.QuadPart - m_OldTime1.QuadPart) / m_CpuTick.QuadPart;
	m_OldTime1 = m_CurTime;
}
