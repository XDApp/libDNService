#pragma once

#include "DNKHash.h"

class DNKBucketData;

const int DNKBucketSize = 160;

class DNKBucket
	: public DObject
{
	DClass(DNKBucket)
private:
	std::vector<DNKBucketData*>Data;
	DNKHash ThisNode;
public:
	DNKBucket(const DNKHash &thisNode);
	~DNKBucket();
	
	void Initialize();

	DNKBucketData* Bucket[DNKBucketSize];

	void AddNode(const DNKHash &Hash);
	void RemoveNode(const DNKHash &Hash);

	void __Debug_Print();
};

