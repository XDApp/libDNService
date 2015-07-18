#pragma once

const int DNKHash_Size = 20;

class DNKHash
	: public DObject
{
	DClass(DNKHash)
private:
	unsigned char* _hash;
	DNKHash();
public:
	DNKHash(const unsigned char* Hash);
	DNKHash(const DNKHash &Hash);
	DNKHash(DNKHash &&Hash);
	~DNKHash();

	DNKHash operator= (const DNKHash &Hash);
	DNKHash operator= (DNKHash &&Hash);
	DNKHash operator= (const unsigned char* Hash);

	bool operator == (const DNKHash &Hash) const;
	unsigned char operator [] (size_t pos) const;

	static size_t KPos(const DNKHash &HashA, const DNKHash &HashB);

	std::string GetString();
};

