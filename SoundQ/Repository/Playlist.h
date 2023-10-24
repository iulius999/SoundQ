#pragma once
#include "../Domain/Song.h"
#include <vector>

class Playlist {
private:
	std::vector<Song> songs;
	std::string fileName;

public:
	Playlist(const std::string& fileName);

	std::vector<Song> getAll();
	int getSize() const;

	void add(const Song& s);
	void remove(const Song& s);
	Song findByTitleAndArtist(const std::string& title, const std::string& artist);

private:
	void loadFile();
	void saveFile();
};
