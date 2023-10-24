#pragma once

class Duration {
private:
	int minutes;
	int seconds;

public:
	Duration();
	Duration(const int& minutes, const int& seconds);

	int getMinutes() const;
	int getSeconds() const;

	void setMinutes(const int& newMinutes);
	void setSeconds(const int& newSeconds);
};
