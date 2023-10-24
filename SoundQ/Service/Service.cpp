#include "Service.h"
#include <fstream>
#include "../Exceptions/Exceptions.h"

Service::Service(Playlist& pl, Playlist& wl) : playlist(pl), waitingList(wl) {}

std::vector<Song> Service::getAllSongs()
{
	std::vector<Song> all = this->playlist.getAll();
	std::sort(all.begin(), all.end(), this->compareTitle);
	return all;
}

std::vector<User> Service::getAllUsers(const std::string& fileName)
{
	std::vector<User> users;
	std::ifstream fin(fileName);

	User u;
	while (fin >> u) {
		users.push_back(u);
	}

	fin.close();
	return users;
}

void Service::addSong(const std::string& title, const std::string& artist, const int& minutes, const int& seconds, const int& numberOfLikes, const std::string& link)
{
	Song song(title, artist, Duration(minutes, seconds), numberOfLikes, link);
	validateSong(song);
	playlist.add(song);

	notify();
}

void Service::removeSong(const std::string& title, const std::string& artist)
{
	Song s = playlist.findByTitleAndArtist(title, artist);
	playlist.remove(s);

	notify();
}

std::vector<Song> Service::searchSongs(std::string what)
{
	std::vector<Song> songs, all = this->getAllSongs();
	what = toLower(what);

	for (const Song& s : all) {
		std::string title = toLower(s.getTitle());
		std::string artist = toLower(s.getArtist());
		if (what.empty() || title.find(what) != std::string::npos || artist.find(what) != std::string::npos) {
			songs.push_back(s);
		}
	}

	return songs;
}

void Service::proposeSong(const std::string& title, const std::string& artist, const int& minutes, const int& seconds, const int& numberOfLikes, const std::string& link)
{
	Song song(title, artist, Duration(minutes, seconds), numberOfLikes, link);
	validateSong(song);
	checkIfSongExists(song);
	waitingList.add(song);

	notify();
}

std::vector<Song> Service::getAllProposedSongs()
{
	return waitingList.getAll();
}

Song Service::getProposedSongByIndex(const int& index)
{
	return waitingList.getAll()[index];
}

void Service::acceptProposedSong(const Song& song)
{
	waitingList.remove(song);
	playlist.add(song);

	notify();
}

void Service::rejectProposedSong(const Song& song)
{
	waitingList.remove(song);

	notify();
}

bool Service::compareTitle(const Song& s1, const Song& s2)
{
	if (s1.getTitle() < s2.getTitle()) {
		return true;
	}
	return false;
}

void Service::validateSong(const Song& s)
{
	std::string err;

	if (s.getTitle().empty()) {
		err += "Invalid title!\n";
	}
	if (s.getArtist().empty()) {
		err += "Invalid artist!\n";
	}
	
	int min = s.getDuration().getMinutes(), sec = s.getDuration().getSeconds();
	if (min < 0 || min > 59 || sec < 0 || sec > 59) {
		err += "Invalid duration!\n";
	}
	else if (min == 0 && sec == 0) {
		err += "Invalid duration!\n";
	}

	if (s.getNumberOfLikes() < 0 || s.getNumberOfLikes() > 1e9) {
		err += "Invalid number of likes!\n";
	}

	std::string link = s.getLink();
	if (link.size() < 13) {
		err += "Invalid link!\n";
	}
	else {
		std::string str = link.substr(0, 12);
		if (str != "https://www.") {
			err += "Invalid link!\n";
		}
	}

	if (!err.empty()) {
		throw InvalidSong(err);
	}
}

void Service::checkIfSongExists(const Song& s)
{
	if (!playlist.findByTitleAndArtist(s.getTitle(), s.getArtist()).getTitle().empty()) {
		throw DuplicateSong("The song is already available in the playlist!");
	}
}

std::string Service::toLower(const std::string& s)
{
	std::string t;
	for (int i = 0; i < s.size(); i++) {
		t += tolower(s[i]);
	}
	return t;
}
