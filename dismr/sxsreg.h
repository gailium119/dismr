#pragma once
#include"havesxs.h"
#include "regstub.h"
HRESULT SxSAddRegPackage(SxSPackage package, std::wstring regpath, int operation, _In_opt_ bool bToInstall=false);
HRESULT SxSAddRegAssembly(SxSAssembly assembly, std::wstring regpath, int operation, _In_opt_ bool bToInstall = false);
HRESULT SxSAddRegDeployment(SxSAssembly assembly, std::wstring regpath, int operation, _In_opt_ bool bToInstall = false);
HRESULT SxSRemovePendingPackages(std::wstring regpath);
HRESULT SxSRemovePendingDeployments(std::wstring regpath);
HRESULT SxSRemovePendingAssemblies(std::wstring regpath);