#pragma once
#include <string>

class User {
private:
	std::string name;
	bool isAdmin;

public:
	User();
	User(const std::string& name, const bool& isAdmin = false);

	std::string getName() const;
	bool getIsAdmin() const;

	friend std::ifstream& operator>>(std::ifstream& fin, User& user);
};
