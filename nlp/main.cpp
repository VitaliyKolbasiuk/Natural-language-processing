#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <unordered_map>
#include <algorithm>
#include <stdlib.h>
#include <time.h>

std::unordered_map<std::string, unsigned> capitalLetters;
std::unordered_map<std::string, std::unordered_map<std::string, unsigned>> wordTransitions, capitalWordTransitions;

std::string weightedRandomChoice(const std::unordered_map<std::string, unsigned>& map) {
	unsigned totalWeight = 0;
	for (const auto& pair : map) {
		totalWeight += pair.second;

	}
	const unsigned randomWeight = rand() % totalWeight;
	unsigned currentWeight = 0;
	for (const auto& pair : map) {
		currentWeight += pair.second;
		if (currentWeight > randomWeight) {
			return pair.first;
		}
	}
	return map.begin()->first;
}

void deleteSymbols(std::string& word) {
	static const std::regex symbols("[\"();]");
	word = std::regex_replace(word, symbols, "");
}

void generateSentence(const unsigned numberOfSentences) {
	for (int index = 0; index < numberOfSentences; ++index) {
		const std::string randomKey = weightedRandomChoice(capitalLetters);
		if (randomKey.back() == '.' || randomKey.back() == '!' || randomKey.back() == '?') {
			std::cout << index + 1 << ": " << randomKey << '\n';
			continue;
		}
		std::string randomValue = weightedRandomChoice(capitalWordTransitions[randomKey]);
		std::cout << index + 1 << ": " << randomKey << ' ' << randomValue;
		while (true) {
			if (randomValue.back() == '.' || randomValue.back() == '?' || randomValue.back() == '!') {
				break;
			}
			randomValue = weightedRandomChoice(wordTransitions[randomValue]);
			std::cout << ' ' << randomValue;
		}
		std::cout << '\n';
	}
}

void processInput() {
	std::string previousWord, currentWord;
	std::cin >> previousWord;
	bool check = true;
	while (std::cin >> currentWord) {
		bool lastSymbolCheck = previousWord.back() != '.' &&
			previousWord.back() != '?' &&
			previousWord.back() != '!';
		deleteSymbols(currentWord);
		if (check) {
			++capitalLetters[previousWord];
			if (lastSymbolCheck) {
				++capitalWordTransitions[previousWord][currentWord];
				check = false;
			}
		}
		else if (lastSymbolCheck) {
			++wordTransitions[previousWord][currentWord];
		}
		else {
			check = true;
		}
		previousWord = currentWord;
	}
}

int main() {
	srand(time(NULL));
	processInput();
	generateSentence(100);
	return 0;
}