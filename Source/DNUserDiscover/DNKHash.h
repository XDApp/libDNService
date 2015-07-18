#pragma once

const int DNKHash_Size = 20;

class DNKHash
	: public DObject
{
	DClass(DNKHash)
private:
	char* _hash;
	DNKHash();
public:
	DNKHash(const char* Hash);
	DNKHash(char* &&Hash);
	DNKHash(const DNKHash &Hash);
	DNKHash(DNKHash &&Hash);
	~DNKHash();

	DNKHash operator= (const DNKHash &Hash);
	DNKHash operator= (DNKHash &&Hash);
	DNKHash operator= (char* &&Hash);
	DNKHash operator= (const char* Hash);

	bool operator == (const DNKHash &Hash) const;
	char operator [] (size_t pos) const;
};

