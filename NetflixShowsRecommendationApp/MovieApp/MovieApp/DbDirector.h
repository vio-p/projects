#pragma once
#include <string>

class DbDirector
{
    int m_DirectorId;
    std::string m_DirectorName;

public:
    DbDirector() = default;
    DbDirector(int directorId, const std::string& directorName);
    ~DbDirector() = default;

    int GetDirectorId() const;
    std::string GetDirectorName() const;

    void SetDirectorId(int directorId);
    void SetDirectorName(const std::string& directorName);
};

