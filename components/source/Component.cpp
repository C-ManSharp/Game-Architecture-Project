#include "../header/Component.h"
#include "../../header/mydrawengine.h"

Component::Component() : componentName{ L"" }, message{ std::make_shared<Message>() }
{
}

void Component::recieveMessage(std::shared_ptr<Message> message)
{
	this->message = message;
}

void Component::setComponentName(std::wstring componentName)
{
	std::wstring componentNameLower;
	for (wchar_t c : componentName)
		componentNameLower += std::tolower(c);

	this->componentName = componentNameLower;
}

std::wstring Component::getComponentName() const
{
	return componentName;
}

Component::~Component()
{
}
