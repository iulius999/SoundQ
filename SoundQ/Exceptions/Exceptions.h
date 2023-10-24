#pragma once
#include <stdexcept>

class DuplicateSong : public std::exception {
private:
	std::string message;

public:
	DuplicateSong(const std::string& msg) : message(msg) {}

	const char* what() const noexcept override {
		return message.c_str();
	}
};

class InexistentSong : public std::exception {
private:
	std::string message;

public:
	InexistentSong(const std::string& msg) : message(msg) {}

	const char* what() const noexcept override {
		return message.c_str();
	}
};

class InvalidSong : public std::exception {
private:
	std::string message;

public:
	InvalidSong(const std::string& msg) : message(msg) {}

	const char* what() const noexcept override {
		return message.c_str();
	}
};
