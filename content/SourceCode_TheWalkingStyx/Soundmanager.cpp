#include "stdafx.h"
#include "SoundManager.h"


SoundManager* SoundManager::m_instance = nullptr;
SoundManager* SoundManager::GetInstance()
{
	if (m_instance == nullptr) {
		m_instance = new SoundManager();
	}

	return m_instance;
}
void SoundManager::Release()
{
	m_instance->shutdown();
	if (m_instance != nullptr)
		delete m_instance;
	m_instance = nullptr;
}

void SoundManager::Init() 
{
	//
	SoundManager::GetInstance()->AddSound("TitleMusic", "walking_styx_titel.wav");
	SoundManager::GetInstance()->AddSound("Level1Music", "levelloop1_1.ogg");
	SoundManager::GetInstance()->AddSound("Level2Music", "levelloop1_stufe2.ogg");
	SoundManager::GetInstance()->AddSound("SettingsMusic", "SoundOfTheSoulles.ogg");
	SoundManager::GetInstance()->AddSound("CreditsMusic", "SoundOfTheSoulles.ogg");
	SoundManager::GetInstance()->AddSound("ButtonClick", "ButtonClickSound.ogg");
	SoundManager::GetInstance()->AddSound("CassandraDeathSound", "cassandraDeathSound.ogg");
	SoundManager::GetInstance()->AddSound("IkarusDeathSound", "ikarusDeathSound.ogg");
	SoundManager::GetInstance()->AddSound("EnemyAttackSound", "EnemyAttackSound.ogg");
	SoundManager::GetInstance()->AddSound("VaseBreakingSound", "vasenklirren1.ogg");
	SoundManager::GetInstance()->AddSound("GameOverMusic", "game_over_new.ogg");
	SoundManager::GetInstance()->AddSound("SuccessSound", "level_up.ogg");
}
void SoundManager::AddSound(string ObjectType, string soundPath)
{
	m_sounds.emplace(ObjectType, soundPath);
}

void SoundManager::shutdown()
{
	m_sounds.clear();
}

void SoundManager::onEvent(PlayMusicEvent * e)
{
	if (m_sounds.size() > 0 && m_sounds.find(e->m_ObjectType) != m_sounds.end())
	{
		string Filename = m_sounds[e->m_ObjectType];
		if (!m_currentBackgroundMusic.openFromFile("..\\assets\\Sounds\\" + Filename))
		{
			cout << "Background Music couldn´t be loaded!" << endl;
		}
		else
		{
			m_currentBackgroundMusic.setVolume(50);
			m_currentBackgroundMusic.setLoop(true);
			m_currentBackgroundMusic.play();
		}
		
	}
	else
	{
		std::cout << "Name of requested MusicFile does not exist." << std::endl;
	}

}

void SoundManager::onEvent(StopMusicEvent * e)
{
	if(m_currentBackgroundMusic.getStatus() == Music::Playing) m_currentBackgroundMusic.stop();
}

void SoundManager::onEvent(PlaySoundEvent * e)
{
	/*if (m_sound.getStatus() != Sound::Playing)
	{*/
		if (m_sounds.size() > 0 && m_sounds.find(e->m_SoundType) != m_sounds.end())
		{
			string Filename = m_sounds[e->m_SoundType];
			if (!m_buffer.loadFromFile("..\\assets\\Sounds\\" + Filename))
			{
				cout << "Sound Effect couldn´t be loaded!" << endl;
			}
			else
			{
				m_sound.setBuffer(m_buffer);
				m_sound.setVolume(50);
				m_sound.play();
				/*sf::Time t1 = sf::seconds(0.4f);
				sf::sleep(t1);*/
			}
		
		}
		else
		{
			std::cout << "Name of requested SoundEffect does not exist." << std::endl;
		}
	/*}*/
}
