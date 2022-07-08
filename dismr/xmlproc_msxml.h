#pragma once
#include <vector>
#include <string>
#define PathFileExists(lpszPath) (GetFileAttributes(lpszPath) != (DWORD)-1)
#include<stdio.h>
#include<MsXml2.h>
#pragma comment(lib, "ole32.lib")
#pragma comment(lib, "oleaut32.lib")
HRESULT XmlUnInitialize();
HRESULT XmlInitialize();
HRESULT LoadXML(LPCWSTR pXML, IXMLDOMDocument2** pDocument);

struct SxSXmlDoc {
public:
	IXMLDOMDocument2* XmlDoc=NULL;
	HRESULT Load(LPCWSTR path) {
		//this->XmlDoc = (SxSXmlDoc*)malloc(sizeof(SxSXmlDoc));
		return LoadXML(path,&this->XmlDoc);
	}
	HRESULT Release() {
		if (!this->XmlDoc) return S_FALSE;
		return this->XmlDoc->Release();
	}
};

struct SxSXmlElement {
public:
	IXMLDOMNode* XmlNode = NULL;
	std::wstring GetText() {
		BSTR bstr;
		this->XmlNode->get_text(&bstr);
		std::wstring str = bstr;
		SysFreeString(bstr);
		return str;
	}
	std::wstring GetAttr(std::wstring attrname) {
		IXMLDOMNamedNodeMap* NodeMap=NULL;
		IXMLDOMNode* IDNode = NULL;
		BSTR bstr;
		std::wstring ret;
		HRESULT hr = this->XmlNode->get_attributes(&NodeMap);
		if (hr!=S_OK) { 
			NodeMap->Release();
			this->XmlNode->Release();
			return L""; 
		}
		BSTR attrbstr = ::SysAllocString(attrname.c_str());
		HRESULT result = NodeMap->getNamedItem(attrbstr, &IDNode);
		SysFreeString(attrbstr);
		if (result == S_OK) {
			//
			// Dump id => 1
			//

			if (IDNode->get_text(&bstr) == S_OK) {
				ret = bstr;
				SysFreeString(bstr);
			}
			IDNode->Release();
			NodeMap->Release();
		}
		else {
			if(IDNode)IDNode->Release();
			if(NodeMap)NodeMap->Release();
		}
		return ret;
	}

	HRESULT Release() {
		if (!this->XmlNode) return S_FALSE;
		return this->XmlNode->Release();
	}
};
struct SxSXmlElementTable {
public:
	IXMLDOMNodeList* XmlNodeList = NULL;
	HRESULT SelectFromDocument(SxSXmlDoc doc,LPCWSTR expr) {
		return doc.XmlDoc->selectNodes((WCHAR*)expr, &this->XmlNodeList);
	}
	HRESULT Length(long *result) {
		return this->XmlNodeList->get_length(result);
	}
	HRESULT SelectFromElement(SxSXmlElement element, LPCWSTR expr) {
		return element.XmlNode->selectNodes((WCHAR*)expr, &this->XmlNodeList);
	}
	std::vector<SxSXmlElement> GetElements();

	HRESULT Release() {
		"XmlNodeList";
		if (!this->XmlNodeList) return S_FALSE;
		return this->XmlNodeList->Release();
	}
};