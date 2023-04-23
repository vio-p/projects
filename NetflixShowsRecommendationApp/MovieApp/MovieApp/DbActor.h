#pragma once
#include <string>

class DbActor
{
	int m_ActorId;
	std::string m_ActorName;

public:
	DbActor() = default;
	DbActor(int actorId, const std::string& actorName);
	~DbActor() = default;

	// getters
	std::string GetActorName() const;
	int GetActorId() const;

	// setters
	void SetActorName(const std::string& actorName);
	void SetActorId(int actorId);
};

