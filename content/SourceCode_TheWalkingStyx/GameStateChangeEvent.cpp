#include "stdafx.h"
#include "EventHeader.h"

GameStateChangeEvent::GameStateChangeEvent(Object* const sender, std::string newGameState, bool reinizialize) : CustomEvent(sender)
{
	m_newGameState = newGameState;
	m_reinit = reinizialize;

	StopMusicEvent s(sender);
	EventBus::FireEvent(s);

	if (newGameState == "MainGameState")
	{
		PlayMusicEvent e(this, "Level1Music");
		EventBus::FireEvent(e);
	}
	else if (newGameState == "MenuGameState")
	{
		PlayMusicEvent e(this, "TitleMusic");
		EventBus::FireEvent(e);
	}
	else if (newGameState == "GameOverGameState")
	{
		PlayMusicEvent GameOverMusic(this, "GameOverMusic");
		EventBus::FireEvent(GameOverMusic);
	}
	else if (newGameState == "SettingsGameState")
	{
		PlayMusicEvent b(this, "SettingsMusic");
		EventBus::FireEvent(b);
	}
	else if (newGameState == "CreditGameState")
	{
		PlayMusicEvent b(this, "CreditsMusic");
		EventBus::FireEvent(b);
	}
	else if (newGameState == "SuccessGameState")
	{
		PlaySoundEvent success(this, "SuccessSound");
		EventBus::FireEvent(success);

		/*PlayMusicEvent e(this, "Level1Music");
		EventBus::FireEvent(e);*/
	}
}