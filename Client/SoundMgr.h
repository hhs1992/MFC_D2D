#pragma once
class CSoundMgr
{
	DECLARE_SINGLETON(CSoundMgr)

public:
	enum CHANNEL { BGM, PLAYER, MONSTER, EFFECT, END };

private:
	CSoundMgr();
	~CSoundMgr();

public:
	void Initialize();
	void UpdateSound();
	void PlaySound(const TCHAR* pSoundKey, CHANNEL eID);
	void PlayBGM(const TCHAR* pSoundKey);
	void StopSound(CHANNEL eID);
	void StopAll();
	void Release();

private:
	void LoadSoundFile();


private:
	FMOD_SYSTEM*					m_pSystem;	// FMOD_SYSTEM: ���� ����� �Ѱ��ϴ� ��ġ.
	FMOD_CHANNEL*					m_pChannel[END]; // FMOD_CHANNEL: ���� ����� �����ϴ� ��ü.
	map<const TCHAR*, FMOD_SOUND*>	m_MapSound; // FMOD_SOUND: ���� ���ҽ� ������ ���� ��ü.
};

