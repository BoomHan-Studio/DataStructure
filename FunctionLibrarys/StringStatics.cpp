#include "StringStatics.h"

uint32 UStringStatics::StringLength(ccstring inString)
{
	if (!inString)
	{
		return 0;
	}
	uint32 result = 0;
	while (inString[result] != EOS)
	{
		result++;
	}
	return result;
}

cstring UStringStatics::StringsCopy(cstring inTarget, ccstring inCopied)
{
	if (inTarget && inCopied)
	{
		for (uint32 i = 0; ; i++)
		{
			const char c = inCopied[i];
			inTarget[i] = c;
			if (c == EOS)
			{
				break;
			}
		}
	}
	return inTarget;
}

int16 UStringStatics::StringsCompare(ccstring inStringA, ccstring inStringB)
{
	if (inStringA && inStringB)
	{
		const uint32 lengthA = StringLength(inStringA);
		const uint32 lengthB = StringLength(inStringB);
		const bool equalLength = (lengthA == lengthB);
		for (uint32 i = 0; (!equalLength) || (equalLength && i < lengthA); i++)
		{
			const int16 delta = inStringA[i] - inStringB[i];
			if (delta)
			{
				return delta;
			}
		}
	}
	return 0;
}

cstring UStringStatics::StringsCatenate(cstring inTarget, ccstring inCombined)
{
	if (inTarget && inCombined)
	{
		const uint32 lengthOfTarget = StringLength(inTarget);
		for (uint32 i = 0; ; i++)
		{
			const char c = inCombined[i];
			inTarget[i + lengthOfTarget] = c;
			if (c == EOS)
			{
				break;
			}
		}
	}
	return inTarget;
}
