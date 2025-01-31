#include "stdafx.h"
#include <conio.h>
//控制台操作 - 标准输入
/*
	调用格式： 〈文本型〉 标准输入 （［逻辑型 是否回显］） - 系统核心支持库->控制台操作
	英文名称：fgets
	在标准输入设备上请求输入最多包含2048个字符的一行文本，返回用户所输入的内容。注意本命令只能在控制台程序中使用。本命令为初级命令。
	参数<1>的名称为“是否回显”，类型为“逻辑型（bool）”，可以被省略。本参数决定输入时是否显示所输入字符，为假不显示，为真显示。如果被省略，默认值为真，即回显。可以通过将本参数设置为假以输入密码等特殊信息。
*/
LIBAPI(char*, krnln_fgets)
{
	char Buff[4096]; //虽然说明中为2048，但实际为4096
	if (ArgInf.m_dtDataType == _SDT_NULL || ArgInf.m_bool)
	{
		HANDLE hCon = GetStdHandle(STD_INPUT_HANDLE);
		if (hCon == NULL)
			return NULL;

		DWORD dwSize;
		LPSTR pText = NULL;
		if (ReadConsole(hCon, Buff, sizeof(Buff), &dwSize, NULL))
		//if(ReadFile(hCon,Buff,sizeof(Buff),&dwSize,NULL))
		{
			DWORD i;
			for (i = 0; i < dwSize; i++)
			{
				if (Buff[i] == 0)
					break;
				else if (Buff[i] == '\r')
				{
					Buff[i] = 0;
					break;
				}
				else if (Buff[i] == '\n')
				{
					Buff[i] = 0;
					break;
				}
			}
			if (i == 0 && dwSize > 1)
			{
				Buff[0] = '\n';
				Buff[1] = 0;
			}
			pText = CloneTextData(Buff, dwSize);
		}
		return pText;
	}
	else {
		INT nIdx = 0;
		do
		{
#if _MSC_VER > 1200
			INT nChr = _getch();
#else
			INT nChr = getch();
#endif
			if (nChr == 13)
			{
				Buff[nIdx] = 0;
				break;
			}
			Buff[nIdx] = (char)nChr;
			++nIdx;
		} while (nIdx < sizeof(Buff));
		return CloneTextData(Buff, nIdx);
	}
}
