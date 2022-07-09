#pragma once
#include"havesxs.h"
#include "regstub.h"
HRESULT SxSAddRegPackage(SxSPackage package, std::wstring regpath, int operation);
HRESULT SxSAddRegAssembly(SxSAssembly assembly, std::wstring regpath, int operation);
HRESULT SxSAddRegDeployment(SxSAssembly assembly, std::wstring regpath, int operation);
HRESULT SxSRemovePendingPackages(std::wstring regpath);
HRESULT SxSRemovePendingDeployments(std::wstring regpath);