#pragma once
#include"havesxs.h"
HRESULT RegAddSZ(std::wstring keyName, std::wstring name, std::wstring value);

HRESULT RegAddDWORD(std::wstring keyName, std::wstring name, DWORD value);

HRESULT RegGetDWORD(std::wstring keyName, std::wstring name, DWORD* outvalue);
HRESULT RegAddMulti(std::wstring keyName, std::wstring name, std::wstring value);
HRESULT RegGetSZ(std::wstring keyName, std::wstring name, std::wstring* outvalue);

std::vector<std::wstring> RegEnum(std::wstring keyName);
HRESULT RegDeleteSubKey(std::wstring keyName);