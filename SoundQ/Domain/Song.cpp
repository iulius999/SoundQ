#include "Song.h"
#include <fstream>
#include <Windows.h>

Song::Song()
{
	this->numberOfLikes = 0;
}

Song::Song(const std::string& title, const std::string& artist, const Duration& duration, const int& numberOfLikes, const std::string& link)
{
	this->title = title;
	this->artist = artist;
	this->duration = duration;
	this->numberOfLikes = numberOfLikes;
	this->link = link;
}

bool Song::operator==(const Song& s)
{
	if (this->title == s.getTitle() && this->artist == s.getArtist()) {
		return true;
	}
	return false;
}

std::string Song::getTitle() const
{
	return this->title;
}

std::string Song::getArtist() const
{
	return this->artist;
}

Duration Song::getDuration() const
{
	return this->duration;
}

int Song::getNumberOfLikes() const
{
	return this->numberOfLikes;
}

std::string Song::getLink() const
{
	return this->link;
}

void Song::setTitle(const std::string& newTitle)
{
	this->title = newTitle;
}

void Song::setArtist(const std::string& newArtist)
{
	this->artist = newArtist;
}

void Song::setDuration(const Duration& newDuration)
{
	this->duration = newDuration;
}

void Song::setNumberOfLikes(const int& newNumberOfLikes)
{
	this->numberOfLikes = newNumberOfLikes;
}

void Song::setLink(const std::string& newLink)
{
	this->link = newLink;
}

std::string Song::toString() const
{
	std::string s = this->getTitle() + " | " + this->getArtist() + " | ";
	s += std::to_string(this->getDuration().getMinutes()) + ":";
	if (this->getDuration().getSeconds() < 10) {
		s += "0";
	}
	s += std::to_string(this->getDuration().getSeconds()) + " | ";
	s += std::to_string(this->getNumberOfLikes()) + " | " + this->getLink();

	return s;
}

void Song::play()
{
	ShellExecuteA(NULL, NULL, "chrome.exe", this->getLink().c_str(), NULL, SW_SHOWMAXIMIZED);
}

std::ifstream& operator>>(std::ifstream& fin, Song& song)
{
	char line[1000];
	fin.getline(line, 1000);

	char* p = strtok(line, "|");
	char s[1000];
	int k = 0;
	std::string title, artist, link;
	int numberOfLikes = 0, minutes = 0, seconds = 0;
	while (p != NULL) {
		strcpy(s, p);

		if (k == 0) {
			title = std::string(s);
		}
		else if (k == 1) {
			artist = std::string(s);
		}
		else if (k == 2) {
			if (strlen(s) == 4) {
				minutes = s[0] - '0';
				seconds = 10 * (s[2] - '0') + s[3] - '0';
			}
			else if (strlen(s) == 5) {
				minutes = 10 * (s[0] - '0') + s[1] - '0';
				seconds = 10 * (s[3] - '0') + s[4] - '0';
			}
		}
		else if (k == 3) {
			numberOfLikes = atoi(s);
		}
		else {
			link = std::string(s);
		}

		p = strtok(NULL, "|");
		k++;
	}

	song = Song(title, artist, Duration(minutes, seconds), numberOfLikes, link);
	return fin;
}

std::ofstream& operator<<(std::ofstream& fout, const Song& song)
{
	std::string s = song.getTitle() + "|" + song.getArtist() + "|";
	s += std::to_string(song.getDuration().getMinutes()) + ":";
	if (song.getDuration().getSeconds() < 10) {
		s += "0";
	}
	s += std::to_string(song.getDuration().getSeconds()) + "|";
	s += std::to_string(song.getNumberOfLikes()) + "|" + song.getLink();

	fout << s << "\n";
	return fout;
}
