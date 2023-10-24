#pragma once
#include "../Repository/Playlist.h"
#include <algorithm>
#include "../Domain/User.h"
#include "../Observer/Subject.h"
#include <ctype.h>

class Service : public Subject {
private:
	Playlist& playlist;
	Playlist& waitingList;

public:
	Service(Playlist& pl, Playlist& wl);

	std::vector<Song> getAllSongs();

	std::vector<User> getAllUsers(const std::string& fileName);

	void addSong(const std::string& title, const std::string& artist, const int& minutes, const int& seconds, 
		const int& numberOfLikes, const std::string& link);
	
	void removeSong(const std::string& title, const std::string& artist);

	std::vector<Song> searchSongs(std::string what);

	void proposeSong(const std::string& title, const std::string& artist, const int& minutes, const int& seconds,
		const int& numberOfLikes, const std::string& link);

	std::vector<Song> getAllProposedSongs();

	Song getProposedSongByIndex(const int& index);

	void acceptProposedSong(const Song& song);

	void rejectProposedSong(const Song& song);

private:
	static bool compareTitle(const Song& s1, const Song& s2);

	void validateSong(const Song& s);

	void checkIfSongExists(const Song& s);

	std::string toLower(const std::string& s);
};
