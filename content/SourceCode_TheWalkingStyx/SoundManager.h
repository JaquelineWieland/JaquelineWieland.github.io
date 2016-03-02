#pragma once
#include "stdafx.h"
#include "EventHeader.h"

class SoundManager : public EventHandler<PlayMusicEvent>, public EventHandler<StopMusicEvent>, public EventHandler<PlaySoundEvent>
{
public:

	static SoundManager* GetInstance();
	static void Release();
	void Init();
	void AddSound(string ObjectType, string soundPath);

private:
	SoundManager() = default;
	~SoundManager() = default;
	SoundManager(const SoundManager& p) = delete;
	SoundManager& operator= (SoundManager const&) = delete;

	void shutdown();
	void onEvent(PlayMusicEvent* e) override;
	void onEvent(StopMusicEvent* e) override;
	void onEvent(PlaySoundEvent* e) override;

	static SoundManager* m_instance;
	std::map<std::string, std::string> m_sounds;  //Type and SoundfilePath --> to check with Event || Kepp all Sounds AND Music
	Music m_currentBackgroundMusic;
	Sound m_sound;
	SoundBuffer m_buffer;
};
