#pragma once

class DNKBucketData;

class DNKBucketNode
	: public DObject
{
	DClass(DNKBucketNode)
public:
	DNKBucketNode *Child[2];
	DNKBucketData *Data;

	DNKBucketNode();
	~DNKBucketNode();
};

