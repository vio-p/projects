#include "DbUser.h"

DbUser::DbUser(int userId, const std::string& username, const std::string& password, char gender, const std::string& dateOfBirth)
	: m_UserId{ userId }, m_Username{ username }, m_Password{ password }, m_Gender{ gender }, m_DateOfBirth{ dateOfBirth }
{
}

DbUser::DbUser(DbUser&& other)
{
	*this = std::move(other);
}

DbUser& DbUser::operator=(DbUser&& other)
{
	m_UserId = other.m_UserId;
	m_Username = other.m_Username;
	m_Password = other.m_Password;
	m_Gender = other.m_Gender;
	m_DateOfBirth = other.m_DateOfBirth;
	new(&other) DbUser();
	return *this;
}

int DbUser::GetUserId() const
{
	return m_UserId;
}

std::string DbUser::GetUsername() const
{
	return m_Username;
}

std::string DbUser::GetPassword() const
{
	return m_Password;
}

char DbUser::GetGender() const
{
	return m_Gender;
}

std::string DbUser::GetDateOfBirth() const
{
	return m_DateOfBirth;
}

void DbUser::SetUserId(int userId)
{
	m_UserId = userId;
}

void DbUser::SetUsername(const std::string& username)
{
	m_Username = username;
}

void DbUser::SetPassword(const std::string& password)
{
	m_Password = password;
}

void DbUser::SetGender(char gender)
{
	m_Gender = gender;
}

void DbUser::SetDateOfBirth(const std::string& dateOfBirth)
{
	m_DateOfBirth = dateOfBirth;
}