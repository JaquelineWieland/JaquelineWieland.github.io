#pragma once
#include "stdafx.h"

enum Input
{
	MoveLeft, MoveRight, MoveUp, MoveDown, SpecialMove,
	SwitchToMenuState, SwitchToMainState, Shutdown
};

class InputManager //Singelton
{
public:
	std::map<std::pair<Input, int>, int> m_inputs;
	std::map<std::pair<Input, int>, bool> m_inputPreviousFrame;

	static InputManager* GetInstance();
	static void Release();

	void bind(Input action, int iKeyCode, int iID);
	void unbind(Input action, int iID);
	bool isKeyDown(Input action, int iID);
	bool isKeyPressed(Input action, int iID);


private:
	InputManager() = default;
	~InputManager() = default;
	InputManager(const InputManager& p) = delete;
	InputManager& operator= (InputManager const&) = delete;

	void shutdown();

	static InputManager* m_instance;
};
