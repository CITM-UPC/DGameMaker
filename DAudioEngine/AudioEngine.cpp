#include "AudioEngine.h"

AudioEngine::AudioEngine() {

}

AudioEngine::~AudioEngine() {

}

bool AudioEngine::WwiseInit() {

	// MEMORY MANAGER
	AkMemSettings memSettings;
	AK::MemoryMgr::GetDefaultSettings(memSettings);

	if (AK::MemoryMgr::Init(&memSettings) == AK_Success)
	{
		cout << "Created Memory manager" << endl;
	}
	else
	{
		cout << "Could not create memory manager" << endl;
		return false;
	}

	// STREAM MANAGER
	AkStreamMgrSettings stmSettings;
	AK::StreamMgr::GetDefaultSettings(stmSettings);

	if (AK::StreamMgr::Create(stmSettings))
	{
		cout << "Streaming Manager created" << endl;
	}
	else
	{
		cout << "Could not create the Streaming Manager" << endl;
		return false;
	}

	// STREAM DEVICE
	AkDeviceSettings deviceSettings;
	AK::StreamMgr::GetDefaultDeviceSettings(deviceSettings);

	if (g_lowLevelIO.Init(deviceSettings) == AK_Success)
	{
		cout << "Created stream device and Low-Level I/O System" << endl;
	}
	else
	{
		cout << "Could not create the streaming device and Low-Level I/O system" << endl;
		return false;
	}

	//sound engine
	AkInitSettings initSettings;
	AkPlatformInitSettings platformInitSettings;
	AK::SoundEngine::GetDefaultInitSettings(initSettings);
	AK::SoundEngine::GetDefaultPlatformInitSettings(platformInitSettings);

	if (AK::SoundEngine::Init(&initSettings, &platformInitSettings) == AK_Success)
	{
		cout << "Sound Engine Initialized" << endl;
	}
	else
	{
		cout << "Could not initialize Sound Engine" << endl;
		return false;
	}


	//music engine
	AkMusicSettings musicInit;
	AK::MusicEngine::GetDefaultInitSettings(musicInit);

	if (AK::MusicEngine::Init(&musicInit) == AK_Success)
	{
		cout << "Succes on initialize the Music Engine." << endl;
	}
	else
	{
		cout << "Could not initialize the Music Engine" << endl;
		return false;
	}

	g_lowLevelIO.SetBasePath(AKTEXT("Assets\\Wwise\\DWwiseProject\\GeneratedSoundBanks\\Windows"));
	AK::StreamMgr::SetCurrentLanguage(AKTEXT("English(us)"));

	//bank init
	AkBankID bankID;
	if (AK::SoundEngine::LoadBank(BANKNAME_INIT, bankID) == AK_Success)
	{
		cout << "Init bank loaded" << endl;
	}
	else
	{
		cout << "Could not load init bank" << endl;
		return false;
	}

	if (AK::SoundEngine::LoadBank(BANKNAME_DENGINE, bankID) == AK_Success)
	{
		cout << "DEngine bank loaded" << endl;
	}
	else
	{
		cout << "Could not load DEngine bank" << endl;
		return false;
	}

	//communications
#ifndef AK_OPTIMIZED
	// Initialize communications (not in release build!)

	AkCommSettings commSettings;
	AK::Comm::GetDefaultInitSettings(commSettings);
	if (AK::Comm::Init(commSettings) == AK_Success)
	{
		cout << "Succes on initialize communication." << endl;
	}
	else
	{
		cout << "Could not initialize communication" << endl;
		return false;
	}
#endif // AK_OPTIMIZED


	//spatial audio
	AkSpatialAudioInitSettings settings; // The constructor fills AkSpatialAudioInitSettings with the recommended default settings. 

	if (AK::SpatialAudio::Init(settings) == AK_Success)
	{
		cout << "Succes on initialize the Spatial Audio" << endl;
	}
	else
	{
		cout << "Could not initialize the Spatial Audio." << endl;
		return false;
	}

	return true;
}

bool AudioEngine::Start() {
	if (WwiseInit())
	{
		cout << "Audio System initialization completed" << endl;
	}
	else
	{
		cout << "Audio System initialization ERROR" << endl;
		return false;
	}

	//registering music to game object
	if (AK::SoundEngine::RegisterGameObj(GAME_OBJECT_ID_BCGMUSIC, "BCG_Music") == AK_Success)
	{
		cout << "Game Object BackgroundMusic Succesfully Registered" << endl;
	}
	else
	{
		cout << "Game Object BackgroundMusic ERROR on Register" << endl;
	}
	//registering spatialsound1 to game object
	if (AK::SoundEngine::RegisterGameObj(GAME_OBJECT_ID_SFX_WOLOLO, "SpatialSound1") == AK_Success)
	{
		cout << "Game Object Spatial Sound 1 Succesfully Registered" << endl;
	}
	else
	{
		cout << "Game Object Spatial Sound 1 ERROR on Register" << endl;
	}
	//registering spatialsound2 to game object
	if (AK::SoundEngine::RegisterGameObj(GAME_OBJECT_ID_SFX_HORNYBONK, "SpatialSound2") == AK_Success)
	{
		cout << "Game Object Spatial Sound 2 Succesfully Registered" << endl;
	}
	else
	{
		cout << "Game Object Spatial Sound 2 ERROR on Register" << endl;
	}
	//set default listener
	AK::SoundEngine::SetDefaultListeners(&GAME_OBJECT_ID_BCGMUSIC, 1);

	//creating audio events
	wololo = new AudioEvent();
	hornybonk = new AudioEvent();
	lostArk_theme = new AudioEvent();
	onePiece_theme = new AudioEvent();

	return true;
}

bool AudioEngine::Update() {

	//always call this function on update to make things work
	AK::SoundEngine::RenderAudio();
	//if (isGameOn)
	//{
		//music 1
		//if its turn of the music1 (nextSong == true) and neither of both songs are playing
		if (nextSong && !lostArk_theme->IsEventPlaying() && !onePiece_theme->IsEventPlaying())
		{
			AK::SoundEngine::PostEvent(AK::EVENTS::BCG_MUSIC_LA, GAME_OBJECT_ID_BCGMUSIC, AkCallbackType::AK_EndOfEvent, lostArk_theme->event_call_back, (void*)lostArk_theme);
			lostArk_theme->playing_id = 1L;
			nextSong = false;
		}
		//music 2
		//if its turn of the music2 (nextSong == false) and neither of both songs are playing
		else if (!nextSong && !lostArk_theme->IsEventPlaying() && !onePiece_theme->IsEventPlaying())
		{
			AK::SoundEngine::PostEvent(AK::EVENTS::BCG_MUSIC_OP, GAME_OBJECT_ID_BCGMUSIC, AkCallbackType::AK_EndOfEvent, onePiece_theme->event_call_back, (void*)onePiece_theme);
			onePiece_theme->playing_id = 1L;
			nextSong = true;
		}

		//spatial sound 1
		if (!wololo->IsEventPlaying())
		{
			AK::SoundEngine::PostEvent(AK::EVENTS::SFX_WOLOLO_AOE, GAME_OBJECT_ID_SFX_WOLOLO, AkCallbackType::AK_EndOfEvent, wololo->event_call_back, (void*)wololo);
			wololo->playing_id = 1L;
		}

		//spatial sound 2
		if (!hornybonk->IsEventPlaying())
		{
			AK::SoundEngine::PostEvent(AK::EVENTS::SFX_HORNYBONK, GAME_OBJECT_ID_SFX_HORNYBONK, AkCallbackType::AK_EndOfEvent, hornybonk->event_call_back, (void*)hornybonk);
			hornybonk->playing_id = 1L;
		}
	//}

	return true;
}

// SETTERS
void AudioEngine::SetListenerTransform(float posx, float posy, float posz, float ofx, float ofy, float ofz, float otx, float oty, float otz)
{
	//SINCE OPENGL AND WWISE USE DIFFERENT POSITIVE X AND Z POSITIONS HERE WILL BE CHANGED HERE
	AkSoundPosition tTransform;
	tTransform.SetPosition({ -posx, posy, -posz });
	tTransform.SetOrientation({ ofx, ofy, ofz }, { otx, oty, otz });
	if (AK::SoundEngine::SetPosition(GAME_OBJECT_ID_BCGMUSIC, tTransform) != AK_Success)
	{
		cout << "ERROR setting position to backgroundmusic(default listener)" << endl;
	}

}
void AudioEngine::SetSpatial1Transform(float posx, float posy, float posz)
{
	//SINCE OPENGL AND WWISE USE DIFFERENT POSITIVE X AND Z POSITIONS HERE WILL BE CHANGED HERE
	AkSoundPosition tTransform;
	tTransform.SetPosition({ -posx, posy, -posz });
	tTransform.SetOrientation({ 0.0f, 0.0f, -1.0f }, { 0.0f, 1.0f, 0.0f });
	if (AK::SoundEngine::SetPosition(GAME_OBJECT_ID_SFX_WOLOLO, tTransform) != AK_Success)
	{
		cout << "ERROR setting position to spatialsound1 (emiter 1)" << endl;
	}
}
void AudioEngine::SetSpatial2Transform(float posx, float posy, float posz)
{
	//SINCE OPENGL AND WWISE USE DIFFERENT POSITIVE X AND Z POSITIONS HERE WILL BE CHANGED HERE
	AkSoundPosition tTransform;
	tTransform.SetPosition({ -posx, posy, -posz });
	tTransform.SetOrientation({ 0.0f, 0.0f, -1.0f }, { 0.0f, 1.0f, 0.0f });
	if (AK::SoundEngine::SetPosition(GAME_OBJECT_ID_SFX_HORNYBONK, tTransform) != AK_Success)
	{
		cout << "ERROR setting position to spatialsound2 (emiter 2)" << endl;
	}
}

bool AudioEngine::Clean() {
	delete(wololo);
	wololo = nullptr;
	delete(hornybonk);
	hornybonk = nullptr;
	delete(lostArk_theme);
	lostArk_theme = nullptr;
	delete(onePiece_theme);
	onePiece_theme = nullptr;

#ifndef AK_OPTIMIZED 
	AK::Comm::Term(); 
#endif // AK_OPTIMIZED

	AK::MusicEngine::Term(); 
	AK::SoundEngine::Term();

	g_lowLevelIO.Term();

	if (AK::IAkStreamMgr::Get())
	{
		AK::IAkStreamMgr::Get()->Destroy();
	}

	AK::MemoryMgr::Term();

	return true;
}