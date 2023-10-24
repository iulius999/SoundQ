#pragma once
#include <string>
#include "Duration.h"

class Song {
private:
	std::string title;
	std::string artist;
	Duration duration;
	int numberOfLikes;
	std::string link;

public:
	Song();
	Song(const std::string& title, const std::string& artist, const Duration& duration, const int& numberOfLikes,
		const std::string& link);

	bool operator==(const Song& s);

	std::string getTitle() const;
	std::string getArtist() const;
	Duration getDuration() const;
	int getNumberOfLikes() const;
	std::string getLink() const;

	void setTitle(const std::string& newTitle);
	void setArtist(const std::string& newArtist);
	void setDuration(const Duration& newDuration);
	void setNumberOfLikes(const int& newNumberOfLikes);
	void setLink(const std::string& newLink);

	std::string toString() const;

	void play();

	friend std::ifstream& operator>>(std::ifstream& fin, Song& song);
	friend std::ofstream& operator<<(std::ofstream& fout, const Song& song);
};
