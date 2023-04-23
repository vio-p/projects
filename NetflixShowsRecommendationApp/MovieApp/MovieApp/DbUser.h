#pragma once
#include <string>

class DbUser
{
	int m_UserId;
	std::string m_Username;
	std::string m_Password;
	char m_Gender;
	std::string m_DateOfBirth;

public:
	DbUser() = default;
	DbUser(int userId, const std::string& username, const std::string& password, char gender, const std::string& dateOfBirth);
	DbUser(const DbUser& other) = default;
	DbUser& operator=(const DbUser& other) = default;
	~DbUser() = default;

	DbUser(DbUser&& other);
	DbUser& operator=(DbUser&& other);

	int GetUserId() const;
	std::string GetUsername() const;
	std::string GetPassword() const;
	char GetGender() const;
	std::string GetDateOfBirth() const;

	void SetUserId(int userId);
	void SetUsername(const std::string& username);
	void SetPassword(const std::string& password);
	void SetGender(char gender);
	void SetDateOfBirth(const std::string& dateOfBirth);
};

