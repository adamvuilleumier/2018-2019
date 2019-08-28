#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cctype>
#include<cstring>
using namespace std;

const int KEY_SIZE = 26;
const int MAX_CIPHER = 4941;

bool decrypt(const char ciphertext[], const char crib[]);
int bindCrib(const char ciphertext[], const char crib[], int start);
int numberOfWords(const char cstring[]);
int lengthBetweenSpaces(const char cstring[], int pos);
int lengthIncludingSpaces(const char cstring[], int pos);
bool ensureNoDoubleValues(char a[][KEY_SIZE], int keyLength);

int main()
{
	cout.setf(ios::boolalpha); // output bools as "true"/"false"

	cout << decrypt("bz zqxjqk", "secret") << endl;
	cout << decrypt("Hirdd ejsy zu drvtry od.\nO'z fodvtrry.\n", "my secret") << endl;
}

bool decrypt(const char ciphertext[], const char crib[]) {
	char key[2][KEY_SIZE];  //two rows (corresponding and coded) with 26 columns (1 for each letter)
	int start = 0;
	int letters = 0;
	int keyPos = 0;
	int lettersInCrib = 0;
	int cribPos = 0;

	if (strlen(crib) == 0)
		return false;

	for (int words = 0; words < numberOfWords(crib); words++) {  //finds amount of letters in crib to use in while loop below
		lettersInCrib += lengthBetweenSpaces(crib, cribPos);
		if (words == numberOfWords(crib) - 1)  //to prevent undefined behavior by going off the end of crib string in command below
			break;
		cribPos += (lengthIncludingSpaces(crib, cribPos) + 1);
	}

	for (;;) {
		int pos = bindCrib(ciphertext, crib, start);

		if (pos == -1)
			return false;

		while (letters < lettersInCrib) { //gets rid of spaces in cipher starting from bind site and adds them to bottom row of array
			if (isalpha(ciphertext[pos])) {
				key[1][letters] = ciphertext[pos];
				letters++;
			}
			pos++;
		}
		for (int cribPos = 0; cribPos < strlen(crib); cribPos++) { //gets rid of spaces in crib and adds letters in order to top row
			if (isalpha(crib[cribPos])) {
				key[0][keyPos] = crib[cribPos];
				keyPos++;
			}
		}
		if (!ensureNoDoubleValues(key, lettersInCrib)) {  //if different values assigned to the same cipher letter or different cipher values assigned to same crib letter
			start = pos + 1;     //if wrong bind site, start process over starting from one position past wrong site
		}
		else
			break;
	}
	char newCipher[MAX_CIPHER];   //constructs copy of ciphertext that is not constant
	strcpy(newCipher, ciphertext);
	int newCiphLength = strlen(newCipher);
	for (int b = 0; b < newCiphLength; b++) { //makes the coded cipher completely lowercase
		newCipher[b] = tolower(newCipher[b]);
	}

	for (int i = 0; i < strlen(newCipher); i++) {   //for all letters in the cipher c-string
		for (int k = 0; k < lettersInCrib; k++) {
			if (newCipher[i] == key[1][k])
				newCipher[i] = toupper(key[0][k]);  //replaces all known letter pairs with uppercase decoded letters
		}
	}
	for (int ciphPos = 0; ciphPos < newCiphLength; ciphPos++) { //prints out the new decoded cipher
		cout << newCipher[ciphPos];
	}
	return true;
}

int bindCrib(const char ciphertext[], const char crib[], int start) {  //returns position where crib binds to ciphertext
	int letterCount = 0;
	int posInCrib = 0;
	int posInCipher = 0;
	int firstMatch = 0;
	int nCribWords = 0;
	for (int i = start; i <= strlen(ciphertext); i++) {
		if (isalpha(ciphertext[i]))
			letterCount++;
		else if (letterCount == lengthBetweenSpaces(crib, posInCrib)) {
			posInCipher = i;
			firstMatch = i - letterCount;
			posInCrib += lengthIncludingSpaces(crib, posInCrib);
			nCribWords++;
			while (nCribWords < numberOfWords(crib)) { //goes here to check for later words when first word matches
				if (lengthBetweenSpaces(crib, posInCrib) == lengthBetweenSpaces(ciphertext, posInCipher)) {
					nCribWords++;
					posInCipher += lengthIncludingSpaces(ciphertext, posInCipher + 1);
					posInCrib += lengthIncludingSpaces(crib, posInCrib + 1);
				}
				else {
					posInCrib = 0;
					posInCipher = 0;
					nCribWords = 0;
					letterCount = 0;
					start = firstMatch + 1; //restarts binding process at one position later if second/third words in crib don't match
					break;
				}
			}
			if (nCribWords == numberOfWords(crib))
				return firstMatch;
		}
		else
			letterCount = 0;
	}
	return -1;
}

int numberOfWords(const char cstring[]) {
	int wordCount = 0;
	int pos = 0;
	int endPos = 0;
	while (pos < strlen(cstring)) {
		wordCount++;
		pos += lengthIncludingSpaces(cstring, pos);
		endPos = pos - 1;
	}
	if (!isalpha(cstring[endPos])) //corrects word count if last letter in cstring is a space
		wordCount--;
	return wordCount;
}

int lengthBetweenSpaces(const char cstring[], int pos) {  //position of start of word to be analyzed (can be a space)
	int preWordSpaceCount = 0;
	for (int k = pos; k < strlen(cstring); k++) {  //makes sure that spaces before the actual word are not counted
		if (!isalpha(cstring[k]))
			preWordSpaceCount++;
		else
			break;
	}
	for (int i = pos + preWordSpaceCount; i < strlen(cstring); i++) { //starts at the beginning of first word following spaces
		if (!isalpha(cstring[i]))
			return (i - pos) - preWordSpaceCount;
	}
	return (strlen(cstring) - pos) - preWordSpaceCount;
}

int lengthIncludingSpaces(const char cstring[], int pos) {
	int preWordSpaceCount = 0;
	for (int k = pos; k < strlen(cstring); k++) {  //makes sure that spaces before the actual word are not counted
		if (!isalpha(cstring[k]))
			preWordSpaceCount++;
		else
			break;
	}
	for (int i = pos + preWordSpaceCount; i < strlen(cstring); i++) { //starts at the beginning of first word following spaces
		if (!isalpha(cstring[i]))
			return i - pos;
	}
	return strlen(cstring) - pos;
}

bool ensureNoDoubleValues(char a[][KEY_SIZE], int keyLength) {
	for (int big = 0; big < keyLength; big++) {
		for (int small = big + 1; small < keyLength; small++) {
			if (a[0][big] == a[0][small]) {
				char bigcor = a[1][big];
				char smallcor = a[1][small];
				if (bigcor != smallcor)
					return false;
			}
			if (a[1][big] == a[1][small]) {
				char bigcor = a[0][big];
				char smallcor = a[0][small];
				if (bigcor != smallcor)
					return false;
			}
		}
	}
	return true;
}