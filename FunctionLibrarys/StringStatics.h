#pragma once
#include "CoreMinimal.h"
#include "Statics.h"

class UStringStatics : UStatics
{
private:
	/**
	 *@brief 此类禁止构造。
	 */
	UStringStatics() = delete;

public:

	//typedef char* cstring;
	//typedef const char* ccstring;

	/**
	 *@brief 与strlen功能一致，获得字符串的长度。
	 *@param inString 输入字符串字面值
	 *@return 该字符串的长度(除去\0)
	 *--------------------------------------------
	 *例如，输入"123456789"，返回9。
	 *--------------------------------------------
	 */
	static uint32 StringLength(ccstring inString);

	/**
	 *@brief 与strcpy功能一致，复制字符串。
	 *@param inTarget 被复制的字符串
	 *@param inCopied 复制的字符串
	 *@note 当被复制的字符串容量较小而复制的字符串较大时，可能发生越界错误！
	 *--------------------------------------------
	 *例如，输入"123456","789456"，前者会变为"789456"。
	 *--------------------------------------------
	 */
	static cstring StringsCopy(cstring inTarget, ccstring inCopied);

	/**
	 *@brief 与strcmp功能一致，比较两个字符串。
	 *@param inStringA 字符串A
	 *@param inStringB 字符串B
	 *@return 当两个字符串的某一个相同位置的值不一样时，返回A-B的差值；否则返回0
	 *--------------------------------------------
	 *例如，输入"1234567","1234557"，它们的第[5]个字符不同，因此返回'6'-'5'=1。
	 *--------------------------------------------
	 */
	static int16 StringsCompare(ccstring inStringA, ccstring inStringB);

	/**
	 *@brief 与ctrcat功能一致，实现字符串的拼接。
	 *@param inTarget 被拼接的字符串
	 *@param inCombined 拼接的字符串
	 *@return 被拼接的字符串首地址
	 *@note 当被拼接的字符串容量较小而拼接的字符串较大时，可能发生越界错误！
	 *--------------------------------------------
	 *例如，输入"BoomBoom","Han"，前者会变为"BoomBoomHan"并被返回。
	 *--------------------------------------------
	 */
	static cstring StringsCatenate(cstring inTarget, ccstring inCombined);
};
