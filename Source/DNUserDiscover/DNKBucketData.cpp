#include "stdafx.h"
#include "DNKBucketData.h"


DNKBucketData::DNKBucketData()
{
}


DNKBucketData::~DNKBucketData()
{
}

void DNKBucketData::AddNode(const DNKHash &Hash)
{
	this->User.push_back(Hash);
}

void DNKBucketData::RemoveNode(const DNKHash &Hash)
{
	this->User.erase(std::find(this->User.begin(), this->User.end(), Hash));
}

void DNKBucketData::__Debug_Print()
{
	for (auto &user : this->User)
	{
		std::cout << user.GetString() << std::endl;
	}
}