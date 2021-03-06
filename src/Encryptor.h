#ifndef ENCODER_H
#define ENCODER_H

#include <deque>
#include <string>
#include <iostream>
#include <vector>
#include "AESUtils.h"

class Encryptor {
public:
	// singleton class stuff, we only want one encryptor.
	static Encryptor& getInstance() {
		static Encryptor instance;
		return instance;
	}
	Encryptor(Encryptor const&) = delete;
	void operator=(Encryptor const&) = delete;

	void printStringFromDeque(bool isKey);

	Encryptor() {}
	~Encryptor() {}
	void encrypt(std::string s, bool verbose);
	void decrypt(std::string s, bool verbose);
	bool setKey(std::string new_key);
	std::string getKey();
    bool parseString(std::string s, bool isKey, int& n);
    void printMessage();
    std::deque<Block> getMessage();
private:
	std::string key_string;

	const unsigned int rounds = 10; // will change eventually
	std::deque<Block> message;
	std::deque<Block> key;
	std::string generateRandomKey(); // Will require libSodium or another external library for good random numbers.
	// inline all the things!
	// operations.

    void subBytes();
    void shiftRows();
    void mixColumns();
	// inverse operations.
    void invSubBytes();
    void invShiftRows();
    void invMixColumns();
	// addRoundKey is just a XOR, which is its own inverse.
	inline void addRoundKey(unsigned int round) {
		for (auto& value: message) {
            value ^= key[round]; // Overloaded operator^=, because I can.
		}
	}
	bool generateSubKeys();
};
#endif
