#pragma once

#include "DNKHash.h"

class DNKBucketData
	: public DObject
{
	DClass(DNKBucketData)
public:
	DNKBucketData();
	~DNKBucketData();

	std::vector<DNKHash> User;

	void AddNode(const DNKHash &Hash);
	void RemoveNode(const DNKHash &Hash);
	
	void __Debug_Print();
};

