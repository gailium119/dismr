#pragma once
#include"getsxs.h"
HRESULT SxSStagePackage(std::wstring srcpkg, std::wstring imgdir, _Outptr_opt_ SxSPackage* ppkg = NULL, _In_opt_ bool bToInstall=false);
HRESULT SxSInstallPackage(std::wstring srcpkg, std::wstring imgdir);