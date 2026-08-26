#pragma once
#include "DxLib.h"

inline void PickRandomDistinct(int poolSize, int pickCount, int* outIndices)
{
	int count = 0;
	while (count < pickCount)
	{
		int candidate = GetRand(poolSize - 1);
		bool duplicate = false;
		for (int i = 0; i < count; i++)
		{
			if (outIndices[i] == candidate) { duplicate = true; break; }
		}
		if (!duplicate)
		{
			outIndices[count] = candidate;
			count++;
		}
	}
}