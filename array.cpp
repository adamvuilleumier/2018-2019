#include<iostream>
#include<string>
#include<cassert>
using namespace std;

int countMatches(const string a[], int n, string target);
int detectMatch(const string a[], int n, string target);
bool detectSequence(const string a[], int n, string target, int& begin, int& end);
int detectMin(const string a[], int n);
int moveToBack(string a[], int n, int pos);
int moveToFront(string a[], int n, int pos);
int detectDifference(const string a1[], int n1, const string a2[], int n2l);
int deleteDups(string a[], int n);
bool contains(const string a1[], int n1, const string a2[], int n2);
int meld(const string a1[], int n1, const string a2[], int n2, string result[], int max);
int split(string a[], int n, string splitter);
void moveEnd(string a[], int n, int pos);
void moveFront(string a[], int pos);
int checkSize(string a[], int n);
bool isNondecrease(const string a[], int n);

int main() {
	string h[7] = { "romanoff", "thor", "rogers", "banner", "", "danvers", "rogers" };
	assert(countMatches(h, 7, "rogers") == 2);
	assert(countMatches(h, 7, "") == 1);
	assert(countMatches(h, 7, "rhodes") == 0);
	assert(countMatches(h, 0, "rogers") == 0);
	assert(detectMatch(h, 7, "rogers") == 2);
	assert(detectMatch(h, 2, "rogers") == -1);
	int bg;
	int en;
	assert(detectSequence(h, 7, "banner", bg, en) && bg == 3 && en == 3);

	string g[4] = { "romanoff", "thor", "banner", "danvers" };
	assert(detectMin(g, 4) == 2);
	assert(detectDifference(h, 4, g, 4) == 2);
	assert(contains(h, 7, g, 4));
	assert(moveToBack(g, 4, 1) == 1 && g[1] == "banner" && g[3] == "thor");

	string f[4] = { "danvers", "banner", "thor", "rogers" };
	assert(moveToFront(f, 4, 2) == 2 && f[0] == "thor" && f[2] == "banner");

	string e[5] = { "danvers", "danvers", "danvers", "thor", "thor" };
	assert(deleteDups(e, 5) == 2 && e[1] == "thor");

	string x[4] = { "rhodes", "rhodes", "tchalla", "thor" };
	string y[4] = { "banner", "danvers", "rhodes", "rogers" };
	string z[10];
	assert(meld(x, 4, y, 4, z, 10) == 8 && z[5] == "rogers");

	assert(split(h, 7, "rogers") == 3);

	cout << "All tests succeeded" << endl;
}

int countMatches(const string a[], int n, string target) { 
	if (n < 0)
		return -1;
	int nMatches = 0;
	for (int k = 0; k < n; k++) {
		if (a[k] == target)
			nMatches++;
	}
	return nMatches;
}

int detectMatch(const string a[], int n, string target) {
	for (int k = 0; k < n; k++) {
		if (a[k] == target)
			return k;
	}
	return -1;
}

bool detectSequence(const string a[], int n, string target, int& begin, int& end) {
	for (int k = 0; k < n; k++) {
		if (a[k] == target) {
			begin = k;
			int repeats = 0;
			for (int i = k; i < n; i++) {
				if (a[i] == target)
					repeats++;
			}
			end = k + (repeats - 1);  //need the -1 here because the first string in the sequence is technically a repeat
			return true;
		}
	}
	return false;
}

int detectMin(const string a[], int n) {
	if (n <= 0)
		return -1;
	string smallest = a[0];
	int smallPosition = 0;
	for (int k = 0; k < n; k++) {
		if (a[k] < smallest) {
			smallest = a[k];
			smallPosition = k;
		}
	}
	return smallPosition;
}

int moveToBack(string a[], int n, int pos) {
	if (pos >= n || pos < 0)
		return -1;
	if (n < 0)
		return -1;
	string startPos = a[pos];
	for (int k = 0; (pos + k) < (n - 1); k++) {
		a[pos + k] = a[(pos + k) + 1];
	}
	a[n - 1] = startPos;
	return pos;
}

int moveToFront(string a[], int n, int pos) {
	if (pos >= n || pos < 0)
		return -1;
	if (n < 0)
		return -1;
	string startPos = a[pos];
	for (int k = pos; k > 0; k--) { //need to start from end position so previous actions in the for loop don't affect the later positions in the array
		a[k] = a[k - 1];
	}
	a[0] = startPos;
	return pos;
}

int detectDifference(const string a1[], int n1, const string a2[], int n2) {
	if (n1 < 0 || n2 < 0)
		return -1;
	if (n1 <= n2) {
		for (int i = 0; i < n1; i++) {
			if (a1[i] != a2[i])
				return i;
		}
		return n1;  //if the entire sequence is the same, return total number of strings in smaller array
	}
	else if (n2 < n1) {
		for (int k = 0; k < n2; k++) {
			if (a1[k] != a2[k])
				return k;
		}
		return n2;
	}
	return -1;
}

int deleteDups(string a[], int n) {
	if (n < 0)
		return -1;
	int returnVal = checkSize(a, n); //checkSize() function needs to be given the original array
	for (int k = 0; k < n; k++) {
		int i = k + 1;
		while (i < n - 1) {       //since the moveEnd function shifts everything down a position when there is a dup, no need for i++
			if (a[i] == a[k]) {
				moveEnd(a, n, i);
			} else
				break;
		}
	}
	return returnVal;
}

bool contains(const string a1[], int n1, const string a2[], int n2) {
	if (n1 < 0 || n2 < 0)
		return false;
	int count = 0;
	int matchPos = -1;
	for (int l = 0; l < n2; l++) {
		for (int b = matchPos + 1; b < n1; b++) {
			if (a2[l] == a1[b]) {
				matchPos = b;
				count++;
				break;
			}
		}
	}
	if (count == n2)
		return true;
	return false;
}

int meld(const string a1[], int n1, const string a2[], int n2, string result[], int max) {
	int sizeR = n1 + n2;
	if (n1 < 0 || n2 < 0 || max < 0)
		return -1;
	if (!isNondecrease(a1, n1) || !isNondecrease(a2, n2))
		return -1;
	if (sizeR > max)
		return -1;
	int i = 0;
	int ii = 0;
	int k = 0;
	while (i < n1 && ii < n2) {
		if (a1[i] < a2[ii]) {
			result[k] = a1[i];
			i++;
			k++;
		}
		else if (a1[i] >= a2[ii]) {
			result[k] = a2[ii];
			ii++;
			k++;
		}
	}
	while (i < n1 - 1) {
		result[k] = a1[i];
		i++;
		k++;
	}
	while (ii < n2 - 1) {
		result[k] = a2[ii];
		i++;
		k++;
	}
	if (ii < n2)
		result[sizeR - 1] = a2[ii];
	if (i < n1)
		result[sizeR - 1] = a1[i];
	return sizeR;
}

int split(string a[], int n, string splitter) {
	if (n < 0)
		return -1;
	for (int k = 0; k < n; k++) {
		if (a[k] > splitter)
			moveEnd(a, n, k);
		if (a[k] < splitter)
			moveFront(a, k);
	}
	for (int k = 0; k < n; k++) {
		if (a[k] >= splitter)
			return k;
	}
	return n;
}

void moveEnd(string a[], int n, int pos) { //helper function that moves a string to the end of an array w/o returning anything
	string startPos = a[pos];
	for (int k = 0; (pos + k) < (n - 1); k++) {
		a[pos + k] = a[(pos + k) + 1];
	}
	a[n - 1] = startPos;
}

void moveFront(string a[], int pos) {
	string startPos = a[pos];
	for (int k = pos; k > 0; k--) {
		a[k] = a[k - 1];
	}
	a[0] = startPos;
}

int checkSize(string a[], int n) {  //helper function that counts the amount of series of duplicate strings in an array
	int nUnique = 0;
	for (int k = 0; k < n; k++) {
		if (a[k] != a[k + 1])
			nUnique++;
	}
	return nUnique;
}

bool isNondecrease(const string a[], int n) { //returns true if array is in nondecreasing order
	for (int k = 1; k < n; k++) {
		if (a[k] < a[k - 1])
			return false;
	}
	return true;
}