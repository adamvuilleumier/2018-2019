#include <iostream>
#include <string>
#include <cctype>
#include "grid.h"
using namespace std;

bool isCourseWellFormed(string course);
int driveSegment(int r, int c, char dir, int maxSteps);
int driveCourse(int sr, int sc, int er, int ec, string course, int& nsteps);
string segmentor(string course, int position);
int magnitude(string segment);
int numberOfCommands(string course);
bool isDirection(char c);

int main()
{
	setSize(2, 5);
	setWall(2, 2);
	int ns = -999;
	cout << driveCourse(2, 2, 1, 3, "studd", ns) << endl;
	cout << ns;
}

bool isCourseWellFormed(string course) {
	for (int k = 0; k != course.size(); k++) {   //checks to see if all digits are valid and returns false if not
		if (!isDirection(course[k])) {
			if (!isdigit(course[k]) || isdigit(course[0]))    //checks to make sure that characters are either above letters or any digit (but the first character cannot be digit)
				return false;
		}
	}
	for (int i = 1; i <= numberOfCommands(course); i++) {     //i is the command position number that is being scanned
		string segment = segmentor(course, i);
		if (magnitude(segment) == 100 || magnitude(segment) < 0)  //checks if commands have valid magnitudes
			return false;
	}
	return true;
}

int driveSegment(int r, int c, char dir, int maxSteps) {
	if (!isDirection(dir) || maxSteps < 0 || r > getRows() || r < 1 || c > getCols() || c < 1)    //makes sure all arguments are valid
		return -1;
	if (isWall(r, c))     //makes sure starting position is not a wall
		return -1;

	if (toupper(dir) == 'E') {
		int totalSteps = 0;
		for (int k = 0; k < maxSteps; k++) {       //counts total steps before hitting wall in any given dir
			if (c + k + 1 > getCols())    //makes sure each step is not off the grid
				return totalSteps;
			else if (isWall(r, c + k + 1))
				return totalSteps;
			else if (!isWall(r, c + k + 1))
				totalSteps++;
		}
	}
	else if (toupper(dir) == 'W') {
		int totalSteps = 0;
		for (int k = 0; k < maxSteps; k++) {
			if (c - (k + 1) < 1)
				return totalSteps;
			else if (isWall(r, c - (k + 1)))
				return totalSteps;
			else if (!isWall(r, c - (k + 1)))
				totalSteps++;
		}
	}
	else if (toupper(dir) == 'N') {
		int totalSteps = 0;
		for (int k = 0; k < maxSteps; k++) {
			if (r - (k + 1) < 1)
				return totalSteps;
			else if (isWall(r - (k + 1), c))
				return totalSteps;
			else if (!isWall(r - (k + 1), c))
				totalSteps++;
		}
	}
	else if (toupper(dir) == 'S') {
		int totalSteps = 0;
		for (int k = 0; k < maxSteps; k++) {
			if (r + k + 1 > getRows())
				return totalSteps;
			else if (isWall(r + k + 1, c))
				return totalSteps;
			else if (!isWall(r + k + 1, c))
				totalSteps++;
		}
	}
	return maxSteps;
}

int driveCourse(int sr, int sc, int er, int ec, string course, int& nsteps) {
	if (isWall(sr, sc) || isWall(er, ec) || !isCourseWellFormed(course))  //checks for invalid input (return 2 case)
		return 2;
	if (sr > getRows() || sr < 1 || er > getRows() || er < 1)
		return 2;
	if (sc > getCols() || sc < 1 || ec > getCols() || ec < 1)
		return 2;

	int totalStepsTaken = 0;
	int crashTest = 0;    //crashTest is nonzero if the course caused the car to hit a wall or go off grid and 0 if all went well
	int r = sr;
	int c = sc;

	for (int k = 1; k <= numberOfCommands(course); k++) {
		string seg = segmentor(course, k);
		int stepsTaken = driveSegment(r, c, seg[0], magnitude(seg));
		int proposedStepsTaken = magnitude(seg);

		if (toupper(seg[0]) == 'N')  //moves the car in the direction/magnitude of the command
			r -= stepsTaken;
		if (toupper(seg[0]) == 'S')
			r += stepsTaken;
		if (toupper(seg[0]) == 'E')
			c += stepsTaken;
		if (toupper(seg[0]) == 'W')
			c -= stepsTaken;

		totalStepsTaken += stepsTaken;

		if (stepsTaken != proposedStepsTaken) { //compares what the course called for to what actually happened
			crashTest++;
			break;
		}
	}

	nsteps = totalStepsTaken;

	if (crashTest != 0)
		return 3;
	if (r == er && c == ec)
		return 0;
	if (r != er || c != ec)
		return 1;
	return -1;
}

int magnitude(string segment) { //segment starts with direction ends with the string end (only measures first command's magnitude)
	if (!isDirection(segment[0]))
		return 0;

	int numberOfFollowingDigits = 0;
	for (int k = 1; k != segment.size(); k++) {
		if (isdigit(segment[k]))
			numberOfFollowingDigits++;
		else                  // breaks when the number following a direction ends
			break;
	}
	if (numberOfFollowingDigits == 0)
		return 1;
	else if (numberOfFollowingDigits == 1)
		return segment[1] - '0';            // converts character to int and returns that int
	else if (numberOfFollowingDigits == 2)
		return ((segment[1] - '0') * 10) + (segment[2] - '0');
	else
		return 100;            //magnitude function will return 100 if magnitude is 3 digits or more
}

string segmentor(string course, int desiredPosition) {  //returns commands including and after command number given by argument "desiredPosition" (works only for valid syntax)
	int scannedPositions = 0;                           //the command positions start with 1 (not 0)
	for (int k = 0; k != course.size(); k++) {
		if (isalpha(course[k])) {
			if (scannedPositions < desiredPosition)
				scannedPositions++;
			if (scannedPositions == desiredPosition)
				return course.substr(k, (course.size() - k));
		}
	}
	return "";                                         //if desiredPosition argument is too high, returns empty string
}

int numberOfCommands(string course) {      //finds total number of commands in the course in order to prevent for loop errors
	int maxPositions = 0;
	for (int k = 0; k != course.size(); k++) {
		if (isalpha(course[k]))
			maxPositions++;
	}
	return maxPositions;
}

bool isDirection(char c) {
	if (toupper(c) != 'N' && toupper(c) != 'S' && toupper(c) != 'E' && toupper(c) != 'W')
		return false;
	else
		return true;
}