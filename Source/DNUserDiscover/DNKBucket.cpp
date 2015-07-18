#include "stdafx.h"
#include "DNKBucket.h"
#include "DNKBucketData.h"


DNKBucket::DNKBucket(const DNKHash &thisNode)
	: ThisNode(thisNode)
{

}

DNKBucket::~DNKBucket()
{
	while (!this->Data.empty())
	{
		DDel(Data.back());
		Data.pop_back();
	}
}

void DNKBucket::Initialize()
{
	this->Data.push_back(new DNKBucketData());
	for (int i = 0; i < 160; i++)
		this->Bucket[i] = this->Data.at(0);
}

void DNKBucket::AddNode(const DNKHash &Hash)
{
	this->Bucket[DNKHash::KPos(Hash, this->ThisNode)]->AddNode(Hash);
}

void DNKBucket::RemoveNode(const DNKHash &Hash)
{
	this->Bucket[DNKHash::KPos(Hash, this->ThisNode)]->RemoveNode(Hash);
}

void DNKBucket::__Debug_Print()
{
	for (int i = 0; i < DNKBucketSize; i++)
	{
		std::cout << "Bucket " << i << std::endl;
		this->Bucket[i]->__Debug_Print();
	}
}