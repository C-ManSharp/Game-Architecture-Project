/*
Author: Connor Tall
Abstract base class that all components inherit.
*/

#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>
#include "../../header/Message.h"

class GameObject;

class Component
{
private:
	std::wstring componentName;
protected:
	std::shared_ptr<Message>message;
public:
	Component();
	virtual void update(GameObject& gameObject, float frameTime) = 0;
	virtual void recieveMessage(std::shared_ptr<Message>message);
	void setComponentName(std::wstring componentName);
	std::wstring getComponentName() const;
	virtual ~Component();
};

#endif