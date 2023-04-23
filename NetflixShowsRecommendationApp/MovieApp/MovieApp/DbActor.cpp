#include "DbActor.h"

DbActor::DbActor(int actorId, const std::string& actorName)
	: m_ActorId{ actorId }, m_ActorName{ actorName }
{
}

std::string DbActor::GetActorName() const
{
	return m_ActorName;
}

int DbActor::GetActorId() const
{
	return m_ActorId;
}

void DbActor::SetActorName(const std::string& actorName)
{
	m_ActorName = actorName;
}

void DbActor::SetActorId(int actorId)
{
	m_ActorId = actorId;
}
