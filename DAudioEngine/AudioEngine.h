#pragma once

#include "AudioUtility.h"
using namespace std;

CAkFilePackageLowLevelIODeferred g_lowLevelIO;

class AudioEvent
{
public:
	AudioEvent();

	bool IsEventPlaying() const
	{
		return playing_id != 0L;
	}

	AkPlayingID playing_id = 0L;						// When Event is played, is different from 0L
	AkCallbackFunc event_call_back = nullptr;			// Call back function
};

class AudioEngine
{
public:
	AudioEngine();
	~AudioEngine();

	bool WwiseInit();
	bool Start();
	bool Update();

	bool Clean();

	void SetListenerTransform(float posx, float posy, float posz, float ofx, float ofy, float ofz, float otx, float oty, float otz);
	void SetSpatial1Transform(float posx, float posy, float posz);
	void SetSpatial2Transform(float posx, float posy, float posz);

	//callback stuff
	static void EventCallBack(AkCallbackType in_eType, AkCallbackInfo* in_pCallbackInfo)
	{
		AudioEvent* a_event = (AudioEvent*)in_pCallbackInfo->pCookie;

		switch (in_eType)
		{
		case(AkCallbackType::AK_EndOfEvent):
		{
			a_event->playing_id = 0L;
			break;
		}
		}
	}

private:
	//Camera
	AkGameObjectID GAME_OBJECT_ID_BCGMUSIC;
	//dynamic
	AkGameObjectID GAME_OBJECT_ID_SFX_HORNYBONK;
	//static
	AkGameObjectID GAME_OBJECT_ID_SFX_WOLOLO;

	AudioEvent* wololo;
	AudioEvent* hornybonk;
	AudioEvent* lostArk_theme;
	AudioEvent* onePiece_theme;

	bool nextSong = false;

};

