/*!
*	@file
*	@date 2022-Feb
*	@author Richard Chin
*
*/
#pragma once
#include <string>
#include <Windows.h>
#include <libloaderapi.h>

class LocalResource
{
    LocalResource() = delete;

public:

    /*! @brief Returns the string dump of the given local resource
    */
    static bool GetResourceAsString(UINT nResId, LPCTSTR pszName, std::string& str)
    {
        HINSTANCE hInst = ::GetModuleHandle(nullptr);
        HRSRC hRsrc = ::FindResource(hInst, MAKEINTRESOURCE(nResId), pszName);

        if (nullptr != hRsrc)
        {
            DWORD dwLen = SizeofResource(hInst, hRsrc);
            HGLOBAL hdl = LoadResource(hInst, hRsrc);
            if (hdl == nullptr)
                return false;

            BYTE* pstr = (BYTE*)LockResource(hdl);
            if (nullptr != pstr)
            {
                BYTE* a = new BYTE[dwLen + 1];
                memcpy(a, pstr, dwLen);
                a[dwLen] = (TCHAR)'\0';
                str = reinterpret_cast<char*>(a);
                delete[] a;
                return true;
            }
        }
        return false;
    }
};
