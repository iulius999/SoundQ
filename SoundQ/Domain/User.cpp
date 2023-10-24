#include "User.h"
#include <fstream>

User::User()
{
	this->isAdmin = false;
}

User::User(const std::string& name, const bool& isAdmin)
{
	this->name = name;
	this->isAdmin = isAdmin;
}

std::string User::getName() const
{
	return this->name;
}

bool User::getIsAdmin() const
{
	return this->isAdmin;
}

std::ifstream& operator>>(std::ifstream& fin, User& user)
{
	char line[1000];
	fin.getline(line, 1000);

	char* p = strtok(line, "|");
	int k = 0;
	std::string name;
	bool isAdmin = false;
	char s[1000];

	while (p != NULL) {
		strcpy(s, p);

		if (k == 0) {
			name = std::string(s);
		}
		else {
			if (strcmp(s, "admin") == 0) {
				isAdmin = true;
			}
		}

		p = strtok(NULL, "|");
		k++;
	}

	user = User(name, isAdmin);
	return fin;
}
