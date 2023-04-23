#include "DbShowActor.h"

DbShowActor::DbShowActor(int showId, int actorId) : m_ShowId{ showId }, m_ActorId{ actorId }
{
	//empty
}

int DbShowActor::GetShowId() const
{
	return m_ShowId;
}

int DbShowActor::GetActorId() const
{
	return m_ActorId;
}

void DbShowActor::SetShowId(int showId)
{
	m_ShowId = showId;
}

void DbShowActor::SetActorId(int actorId)
{
	m_ActorId = actorId;
}
