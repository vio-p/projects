#pragma once

class DbShowActor
{
	int m_ShowId;
	int m_ActorId;

public:
	DbShowActor() = default;
	DbShowActor(int showId, int actorId);
	~DbShowActor() = default;

	// getters
	int GetShowId() const;
	int GetActorId() const;

	// setters
	void SetShowId(int showId);
	void SetActorId(int actorId);
};


