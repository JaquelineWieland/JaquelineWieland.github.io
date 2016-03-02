#include "stdafx.h"
#include "InputManager.h"

InputManager* InputManager::m_instance = nullptr;
InputManager* InputManager::GetInstance()
{
	if (m_instance == nullptr)
		m_instance = new InputManager();

	return m_instance;
}
void InputManager::Release()
{
	m_instance->shutdown();
	if (m_instance != nullptr)
		delete m_instance;
	m_instance = nullptr;
}

void InputManager::bind(Input action, int iKeyCode, int iID)
{
	m_inputs.emplace(std::pair<Input, int>(action, iID), iKeyCode);
	m_inputPreviousFrame.emplace(std::pair<Input, int>(action, iID), true);
}

void InputManager::unbind(Input action, int iID)
{
	m_inputs.erase(std::pair<Input, int>(action, iID));
	m_inputPreviousFrame.erase(std::pair<Input, int>(action, iID));
}

bool InputManager::isKeyDown(Input action, int iID)
{
	std::pair<Input, int> currentAction = std::pair<Input, int>(action, iID);

	return Keyboard::isKeyPressed(Keyboard::Key(m_inputs[currentAction]));
}

bool InputManager::isKeyPressed(Input action, int iID)
{
	std::pair<Input, int> currentAction = std::pair<Input, int>(action, iID);

	if (Keyboard::isKeyPressed(Keyboard::Key(m_inputs[currentAction])))
	{
		if (!m_inputPreviousFrame[currentAction])
		{
			m_inputPreviousFrame[currentAction] = true;
			return true;
		}
	}
	else
		m_inputPreviousFrame[currentAction] = false;

	return false;
}

void InputManager::shutdown()
{
	m_inputs.clear();
	m_inputPreviousFrame.clear();
}
