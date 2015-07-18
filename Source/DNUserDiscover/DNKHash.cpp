#include "stdafx.h"
#include "DNKHash.h"

DNKHash::DNKHash()
{
	this->_hash = new char[DNKHash_Size];
}

DNKHash::DNKHash(const char* Hash)
	: DNKHash()
{
	memcpy(this->_hash, Hash, DNKHash_Size);
}

DNKHash::DNKHash(char* &&Hash)
{
	this->_hash = Hash;
	Hash = nullptr;
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
}

DNKHash DNKHash::operator= (DNKHash &&Hash)
{
	this->_hash = Hash._hash;
	Hash._hash = nullptr;
}

DNKHash DNKHash::operator= (const char* Hash)
{
	memcpy(this->_hash, Hash, DNKHash_Size);
}

DNKHash DNKHash::operator = (char* &&Hash)
{
	this->_hash = Hash;
	Hash = nullptr;
}

bool DNKHash::operator == (const DNKHash &Hash) const
{
	for (int i = 0; i < DNKHash_Size; i++)
	{
		if (Hash[i] != this->_hash[i]) return false;
	}
	return true;
}

char DNKHash::operator [] (size_t pos) const
{
	return this->_hash[pos];
}