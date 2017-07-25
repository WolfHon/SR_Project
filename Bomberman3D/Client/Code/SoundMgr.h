#pragma once
#include "Include.h"
#include "Engine_Include.h"

class CSoundMgr
{
	DECLARE_SINGLETON(CSoundMgr);

public:
	enum CHANNEL_ID { CHANNEL_PLAYER, CHANNEL_MONSTER, CHANNEL_EFFECT, CHANNEL_EFFECT1, CHANNEL_EFFECT2,CHANNEL_EFFECT3,CHANNEL_EFFECT4, CHANNEL_EFFECT5,CHANNEL_EFFECT6,CHANNEL_BGM, CHANNEL_END };

private:
	CSoundMgr(void);
	~CSoundMgr(void);

public:
	void Initialize();
	void LoadSoundFile();
	void PlaySound(TCHAR* pSoundKey, CHANNEL_ID eChannel);
	void PlayBGM(TCHAR* pSoundKey);
	void UpdateSound();
	void StopSound(CHANNEL_ID eChannel);
	void StopSoundAll();
	void Release();

private:
	FMOD_SYSTEM*	m_pSystem; // ���带 ������ �ý��� ������.
	FMOD_CHANNEL*	m_pChannelArr[CHANNEL_END];	// ���带 ����� ä���� ����.

	map<TCHAR*, FMOD_SOUND*> m_MapSound;
};
