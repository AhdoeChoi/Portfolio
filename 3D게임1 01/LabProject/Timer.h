#pragma once

const ULONG MAX_SAMPLE_COUNT = 50; // 50ȸ�� ������ ó���ð��� �����Ͽ� ����Ѵ�.

class CGameTimer
{
private: 
	bool m_bHardwareHasPerformanceCounter;
	float m_fTimeScale; float m_fTimeElapsed;
	__int64 m_nCurrentTime;
	__int64 m_nLastTime;
	__int64 m_nPerformanceFrequency;

	float m_fFrameTime[MAX_SAMPLE_COUNT];
	ULONG m_nSampleCount;
	unsigned long m_nCurrentFrameRate; unsigned long m_nFramesPerSecond; float m_fFPSTimeElapsed;
public:
	CGameTimer();
	virtual ~CGameTimer();
public:
	void Tick(float fLockFPS);  //Ÿ�̸� �ð� ����
	unsigned long GetFrameRate(LPTSTR lpszString, int nCharacters); //������ ����Ʈ ��ȯ
	float GetTimeElapsed(); //������ ��հ�� �ð� ��ȯ
};

