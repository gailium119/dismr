#include"havesxs.h"
std::wstring generate_pseudo_key(SxSAssembly assembly) {
	std::wstring ret;
	std::wstring md5 = md5_text(assembly.name);
	if (_wcsicmp(assembly.type.c_str(), L"win32") == 0) {
		return L"deadbeef";
	}
	ret = md5.substr(12, 8);
	return ret;
}

std::wstring generate_sxs_name(SxSAssembly assembly) {
	std::wstring pseudo_key = generate_pseudo_key(assembly);
	
	std::wstring sxs_name = L""; 
	//assembly.name.erase(std::remove(assembly.name.begin(), assembly.name.end(), ' '), assembly.name.end());
	if (assembly.name.length() > 40) {
		assembly.name = assembly.name.substr(0, 19) + L".." + assembly.name.substr(assembly.name.length() - 19, assembly.name.length());
	}
	if (assembly.culture.length() > 8) {
		assembly.culture = assembly.culture.substr(0, 3) + L".." + assembly.culture.substr(assembly.culture.length() - 3, assembly.culture.length());
	}
	sxs_name += assembly.processorArchitecture;
	sxs_name += L"_";
	sxs_name += assembly.name;
	sxs_name += L"_";
	sxs_name += assembly.publicKeyToken;
	sxs_name += L"_";
	if (!assembly.winners) {
		sxs_name += assembly.version;
		sxs_name += L"_";
	}
	sxs_name += assembly.culture;
	sxs_name += L"_";
	sxs_name += pseudo_key;
	transform(sxs_name.begin(), sxs_name.end(), sxs_name.begin(), ::tolower);
	return sxs_name;
}
std::wstring SxSAssembly::genname() {
	return generate_sxs_name(*this);
}
std::wstring SxSPackage::genname() {
	return name + L"~" + publicKeyToken + L"~" + processorArchitecture + L"~" + lang + L"~" + version;
}
HRESULT SxSPackage::LoadFromFile(std::wstring filename)
{
	HRESULT hr = this->sxsxmldoc.Load(filename.c_str());
	if (FAILED(hr)) return hr;
	SxSXmlElementTable table;
	hr = table.SelectFromDocument(this->sxsxmldoc, L"./assembly/assemblyIdentity");
	auto elements = table.GetElements();

	this->name = elements[0].GetAttr(L"name");
	this->lang = elements[0].GetAttr(L"language");
	this->processorArchitecture = elements[0].GetAttr(L"processorArchitecture");
	this->publicKeyToken = elements[0].GetAttr(L"publicKeyToken");
	this->version = elements[0].GetAttr(L"version");
	if (_wcsicmp(this->lang.c_str(), L"neutral") == 0) this->lang = L"";
	if (_wcsicmp(this->lang.c_str(), L"none") == 0) this->lang = L"";
	if (_wcsicmp(this->processorArchitecture.c_str(), L"neutral") == 0) this->processorArchitecture = L"";
	if (_wcsicmp(this->processorArchitecture.c_str(), L"*") == 0) this->processorArchitecture = L"";
	if (_wcsicmp(this->processorArchitecture.c_str(), L"none") == 0) this->processorArchitecture = L"";
	table.Release();
	elements[0].Release();
	return hr;
}
HRESULT SxSPackage::Verify(std::wstring folder)
{
	std::wstring filename = folder + L"\\" + this->genname() + L".rum";
	if (!PathFileExists(filename.c_str())) return 0x80070002;
	HRESULT hr = this->sxsxmldoc.Load(filename.c_str());
	if (FAILED(hr)) return hr;
	SxSXmlElementTable table;
	hr = table.SelectFromDocument(this->sxsxmldoc, L"./assembly/assemblyIdentity");
	auto elements = table.GetElements();

	auto name = elements[0].GetAttr(L"name");
	auto lang = elements[0].GetAttr(L"language");
	auto processorArchitecture = elements[0].GetAttr(L"processorArchitecture");
	auto publicKeyToken = elements[0].GetAttr(L"publicKeyToken");
	auto version = elements[0].GetAttr(L"version");
	if (_wcsicmp(lang.c_str(), L"none") == 0) lang = L"";
	if (_wcsicmp(lang.c_str(), L"neutral") == 0) lang = L"";
	if (_wcsicmp(lang.c_str(), L"*") == 0) lang = L"";
	if (_wcsicmp(version.c_str(), L"") == 0) version = L"";
	if (_wcsicmp(processorArchitecture.c_str(), L"neutral") == 0) processorArchitecture = L"none";
	if (_wcsicmp(processorArchitecture.c_str(), L"*") == 0) processorArchitecture = L"none";
	if (_wcsicmp(processorArchitecture.c_str(), L"") == 0) processorArchitecture = L"none";
	if (_wcsicmp(name.c_str(), this->name.c_str())) hr = 0x80073716;
	if (_wcsicmp(lang.c_str(), this->lang.c_str())) hr = 0x80073716;
	if (_wcsicmp(processorArchitecture.c_str(), this->processorArchitecture.c_str())) hr = 0x80073716;
	if (_wcsicmp(publicKeyToken.c_str(), this->publicKeyToken.c_str())) hr = 0x80073716;
	if (_wcsicmp(version.c_str(), this->version.c_str())) hr = 0x80073716;
	table.Release();
	elements[0].Release();
	if (hr == S_OK) this->status = 1;
	return hr;
}
void SxSPackage::Release()
{
	if(this->sxsxmldoc.XmlDoc)this->sxsxmldoc.XmlDoc->Release();
}
std::vector<SxSDeployment> SxSPackage::GetComponents()
{
	SxSXmlElementTable table;
	HRESULT hr = table.SelectFromDocument(this->sxsxmldoc, L"./assembly/package/update/component/assemblyIdentity");
	auto elements = table.GetElements();
	std::vector<SxSDeployment> components;
	for (int i = 0; i < elements.size(); i++) {
		SxSDeployment deployment;
		deployment.name = elements[i].GetAttr(L"name");
		deployment.culture = elements[i].GetAttr(L"language");
		deployment.processorArchitecture = elements[i].GetAttr(L"processorArchitecture");
		deployment.publicKeyToken = elements[i].GetAttr(L"publicKeyToken");
		deployment.type = elements[0].GetAttr(L"type");
		deployment.version = elements[i].GetAttr(L"version");
		if (_wcsicmp(deployment.culture.c_str(), L"") == 0) deployment.culture = L"none";
		if (_wcsicmp(deployment.type.c_str(), L"") == 0) deployment.type = L"none";
		if (_wcsicmp(deployment.culture.c_str(), L"neutral") == 0) deployment.culture = L"none";
		if (_wcsicmp(deployment.culture.c_str(), L"*") == 0) deployment.culture = L"none";
		if (_wcsicmp(deployment.version.c_str(), L"") == 0) deployment.version = L"none";
		if (_wcsicmp(deployment.processorArchitecture.c_str(), L"neutral") == 0) deployment.processorArchitecture = L"none";
		if (_wcsicmp(deployment.processorArchitecture.c_str(), L"*") == 0) deployment.processorArchitecture = L"none";
		if (_wcsicmp(deployment.processorArchitecture.c_str(), L"") == 0) deployment.processorArchitecture = L"none";
		if (_wcsicmp(deployment.versionScope.c_str(), L"") == 0) deployment.versionScope = L"none";
		components.push_back(deployment);
	}
	table.Release();
	this->sxsxmldoc.Release();
	for (int i = 0; i < elements.size(); i++) elements[i].Release();
	return components;
}
std::vector<SxSPackage> SxSPackage::GetSubPackages()
{
	SxSXmlElementTable table;
	HRESULT hr = table.SelectFromDocument(this->sxsxmldoc, L"./assembly/package/update/package/assemblyIdentity");
	auto elements = table.GetElements();
	std::vector<SxSPackage> pkgs;
	for (int i = 0; i < elements.size(); i++) {
		SxSPackage pkg;
		pkg.name = elements[i].GetAttr(L"name");
		pkg.lang = elements[i].GetAttr(L"language");
		pkg.processorArchitecture = elements[i].GetAttr(L"processorArchitecture");
		pkg.publicKeyToken = elements[i].GetAttr(L"publicKeyToken");
		pkg.version = elements[i].GetAttr(L"version");
		if (_wcsicmp(pkg.lang.c_str(), L"none") == 0) pkg.lang = L"";
		if (_wcsicmp(pkg.lang.c_str(), L"neutral") == 0) pkg.lang = L"";
		if (_wcsicmp(pkg.lang.c_str(), L"*") == 0) pkg.lang = L"";
		if (_wcsicmp(pkg.version.c_str(), L"none") == 0) pkg.version = L"";
		if (_wcsicmp(pkg.processorArchitecture.c_str(), L"neutral") == 0) pkg.processorArchitecture = L"";
		if (_wcsicmp(pkg.processorArchitecture.c_str(), L"*") == 0) pkg.processorArchitecture = L"";
		if (_wcsicmp(pkg.processorArchitecture.c_str(), L"none") == 0) pkg.processorArchitecture = L"";
		pkgs.push_back(pkg);
	}
	table.Release();
	for (int i = 0; i < elements.size(); i++) elements[i].Release();
	return pkgs;
}
HRESULT SxSAssembly::LoadFromFile(std::wstring filename) {
	HRESULT hr=this->sxsxmldoc.Load(filename.c_str());
	if (FAILED(hr)) return hr;
	SxSXmlElementTable table;
	hr=table.SelectFromDocument(this->sxsxmldoc, L"./assembly/assemblyIdentity");
	auto elements = table.GetElements();
	
	this->name=elements[0].GetAttr(L"name");
	this->culture = elements[0].GetAttr(L"language");
	this->processorArchitecture = elements[0].GetAttr(L"processorArchitecture");
	this->publicKeyToken = elements[0].GetAttr(L"publicKeyToken");
	this->type = elements[0].GetAttr(L"type");
	this->version= elements[0].GetAttr(L"version");
	if (_wcsicmp(this->culture.c_str(), L"") == 0) this->culture = L"none";
	if (_wcsicmp(this->type.c_str(), L"") == 0) this->type = L"none";
	if (_wcsicmp(this->culture.c_str(), L"neutral") == 0) this->culture = L"none";
	if (_wcsicmp(this->culture.c_str(), L"*") == 0) this->culture = L"none";
	if (_wcsicmp(this->version.c_str(), L"") == 0) this->version = L"none";
	if (_wcsicmp(this->processorArchitecture.c_str(), L"neutral") == 0) this->processorArchitecture = L"none";
	if (_wcsicmp(this->processorArchitecture.c_str(), L"*") == 0) this->processorArchitecture = L"none";
	if (_wcsicmp(this->processorArchitecture.c_str(), L"") == 0) this->processorArchitecture = L"none";
	if (_wcsicmp(this->versionScope.c_str(), L"") == 0) this->versionScope = L"none";
	table.Release();
	elements[0].Release();
	return hr;
}
void SxSAssembly::Release() {
	//free(this->sxsxmldoc.XmlDoc);
	if (this->sxsxmldoc.XmlDoc)this->sxsxmldoc.XmlDoc->Release();
}
std::vector<SxSFile> SxSAssembly::GetFiles()
{  
	std::vector<SxSFile> filelist;

	SxSXmlElementTable table,subtable;
	HRESULT hr = table.SelectFromDocument(this->sxsxmldoc, L"./assembly/file");
	auto elements = table.GetElements();
	SxSFile tmpfile;
	for (int i = 0; i < elements.size(); i++) {
		 tmpfile.name=elements[i].GetAttr(L"name");
		 tmpfile.srcname = elements[i].GetAttr(L"sourceName");
		 tmpfile.dest= elements[i].GetAttr(L"destinationPath");
		 hr=subtable.SelectFromElement(elements[i], L"./hash/DigestValue");
		 auto hashelements = subtable.GetElements();
		 tmpfile.hash=hashelements[0].GetText();
		 filelist.push_back(tmpfile);
		 hashelements[0].Release();
		 subtable.Release();
		 elements[i].Release();
	}
	table.Release();
	return filelist;
}

std::vector<SxSRegistry> SxSAssembly::GetReg()
{
	std::vector<SxSRegistry> reglist;

	SxSXmlElementTable table, subtable;
	HRESULT hr = table.SelectFromDocument(this->sxsxmldoc, L"./assembly/registryKeys/registryKey");
	auto elements = table.GetElements();
	SxSRegistry tmpreg;
	for (int i = 0; i < elements.size(); i++) {
		tmpreg.keyname = elements[i].GetAttr(L"keyName");
		hr = subtable.SelectFromElement(elements[i], L"./registryValue");
		auto regsubkeys = subtable.GetElements();
		SxSRegistrySubKey keys;
		for (int j=0;j< regsubkeys.size();j++){
		keys.name = regsubkeys[j].GetAttr(L"name");
		keys.valuetype = regsubkeys[j].GetAttr(L"valueType");
		keys.value = regsubkeys[j].GetAttr(L"value");
		tmpreg.keys.push_back(keys);
		regsubkeys[j].Release();
		}
		reglist.push_back(tmpreg);
		subtable.Release();
		elements[i].Release();
	}
	table.Release();
	return reglist;
}
HRESULT SxSAssembly::Load2(std::wstring filename) {
	HRESULT hr = this->sxsxmldoc.Load(filename.c_str());
	if (FAILED(hr)) return hr;
	return hr;
}
std::vector<SxSAssembly> SxSDeployment::GetDependencies() {
	SxSXmlElementTable table;
	HRESULT hr = table.SelectFromDocument(this->sxsxmldoc, L"./assembly/dependency/dependentAssembly/assemblyIdentity");
	auto elements = table.GetElements();
	std::vector<SxSAssembly> dependentassemblies;
	for (int i=0;i<elements.size();i++){
	SxSAssembly assembly;
	assembly.name = elements[i].GetAttr(L"name");
	assembly.culture = elements[i].GetAttr(L"language");
	assembly.processorArchitecture = elements[i].GetAttr(L"processorArchitecture");
	assembly.publicKeyToken = elements[i].GetAttr(L"publicKeyToken");
	assembly.type = elements[0].GetAttr(L"type");
	assembly.version = elements[i].GetAttr(L"version");
	if (_wcsicmp(assembly.culture.c_str(), L"") == 0) assembly.culture = L"none";
	if (_wcsicmp(assembly.type.c_str(), L"") == 0) assembly.type = L"none";
	if (_wcsicmp(assembly.culture.c_str(), L"neutral") == 0) assembly.culture = L"none";
	if (_wcsicmp(assembly.culture.c_str(), L"*") == 0) assembly.culture = L"none";
	if (_wcsicmp(assembly.version.c_str(), L"") == 0) assembly.version = L"none";
	if (_wcsicmp(assembly.processorArchitecture.c_str(), L"neutral") == 0) assembly.processorArchitecture = L"none";
	if (_wcsicmp(assembly.processorArchitecture.c_str(), L"*") == 0) assembly.processorArchitecture = L"none";
	if (_wcsicmp(assembly.processorArchitecture.c_str(), L"") == 0) assembly.processorArchitecture = L"none";
	if (_wcsicmp(assembly.versionScope.c_str(), L"") == 0) assembly.versionScope = L"none";
	dependentassemblies.push_back(assembly);
	}
	table.Release();
	this->sxsxmldoc.Release();
	for (int i = 0; i < elements.size(); i++) elements[i].Release();
	return dependentassemblies;
}
HRESULT SxSAssembly::Verify(std::wstring folder) {
	std::wstring filename = folder + L"\\" + this->genname()+L".manifest";
	if (!PathFileExists(filename.c_str())) return 0x80070002;
	HRESULT hr = this->sxsxmldoc.Load(filename.c_str());
	if (FAILED(hr)) return hr;
	SxSXmlElementTable table;
	hr = table.SelectFromDocument(this->sxsxmldoc, L"./assembly/assemblyIdentity");
	auto elements = table.GetElements();

	auto name = elements[0].GetAttr(L"name");
	auto culture = elements[0].GetAttr(L"language");
	auto processorArchitecture = elements[0].GetAttr(L"processorArchitecture");
	auto publicKeyToken = elements[0].GetAttr(L"publicKeyToken");
	auto type = elements[0].GetAttr(L"type");
	auto version = elements[0].GetAttr(L"version");
	if (_wcsicmp(culture.c_str(), L"") == 0) culture = L"none";
	if (_wcsicmp(type.c_str(), L"") == 0) type = L"none";
	if (_wcsicmp(culture.c_str(), L"neutral") == 0) culture = L"none";
	if (_wcsicmp(culture.c_str(), L"*") == 0) culture = L"none";
	if (_wcsicmp(version.c_str(), L"") == 0) version = L"none";
	if (_wcsicmp(processorArchitecture.c_str(), L"neutral") == 0) processorArchitecture = L"none";
	if (_wcsicmp(processorArchitecture.c_str(), L"*") == 0) processorArchitecture = L"none";
	if (_wcsicmp(processorArchitecture.c_str(), L"") == 0) processorArchitecture = L"none";
	if (_wcsicmp(name.c_str(),this->name.c_str())) hr=0x80073716;
	if (_wcsicmp(culture.c_str(), this->culture.c_str())) hr=0x80073716;
	if (_wcsicmp(processorArchitecture.c_str(), this->processorArchitecture.c_str())) hr=0x80073716;
	if (_wcsicmp(publicKeyToken.c_str(), this->publicKeyToken.c_str())) hr=0x80073716;
	if (_wcsicmp(type.c_str(), this->type.c_str())) hr=0x80073716;
	if (_wcsicmp(version.c_str(), this->version.c_str())) hr=0x80073716;
	table.Release();
	elements[0].Release();
	if (hr == S_OK) this->status = 1;
	return hr;
}