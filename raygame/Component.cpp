#include "Component.h"

Component::Component()
{
	m_owner = nullptr;
	m_started = false;
}

void Component::assignOwner(Actor* owner)
{
	if (getOwner())
		return;

	m_owner = owner;
}

void Component::setEnabled(bool value)
{
	if (m_enabled == value) return;

	m_enabled = value;

	if (m_enabled)
		onEnabled();
	else
		onDisabled();
}
