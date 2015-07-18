#include "stdafx.h"
#include "DNKHash.h"

DNKHash::DNKHash()
{
	this->_hash = new unsigned char[DNKHash_Size];
}

DNKHash::DNKHash(const unsigned char* Hash)
	: DNKHash()
{
	memcpy(this->_hash, Hash, DNKHash_Size);
}


DNKHash::DNKHash(const DNKHash &Hash)
	: DNKHash()
{
	memcpy(this->_hash, Hash._hash, DNKHash_Size);
}

DNKHash::DNKHash(DNKHash &&Hash)
{
	this->_hash = Hash._hash;
	Hash._hash = nullptr;
}


DNKHash::~DNKHash()
{
	DDel(this->_hash);
}

DNKHash DNKHash::operator= (const DNKHash &Hash)
{
	memcpy(this->_hash, Hash._hash, DNKHash_Size);
	return *this;
}

DNKHash DNKHash::operator= (DNKHash &&Hash)
{
	this->_hash = Hash._hash;
	Hash._hash = nullptr;
	return *this;
}

DNKHash DNKHash::operator= (const unsigned char* Hash)
{
	memcpy(this->_hash, Hash, DNKHash_Size);
	return *this;
}


bool DNKHash::operator == (const DNKHash &Hash) const
{
	for (int i = 0; i < DNKHash_Size; i++)
	{
		if (Hash[i] != this->_hash[i]) return false;
	}
	return true;
}

unsigned char DNKHash::operator [] (size_t pos) const
{
	return this->_hash[pos];
}

size_t DNKHash::KPos(const DNKHash &HashA, const DNKHash &HashB)
{
	for (int i = 0; i < DNKHash_Size; i++)
	{
		unsigned char __tmp = HashA[i] ^ HashB[i];
		if (__tmp != 0)
		{
			return log(__tmp) / log(2) + 8 * (DNKHash_Size - i - 1);
		}
	}
	return 0;
}

std::string DNKHash::GetString()
{
	std::string Hash("");
	std::bitset<8>bits;
	for (int i = 0; i < DNKHash_Size; i++)
	{
		bits = this->_hash[i];
		Hash += bits.to_string();
	}
	return std::move(Hash);
}