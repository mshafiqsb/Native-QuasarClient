#include "stdafx.h"
#include "wmi_srvc.h"

using namespace std;

#ifdef USE_WMI

wmi_srvc::wmi_srvc() :
	m_is_init(true) {
	if (FAILED(CoInitialize(nullptr))) {
		m_is_init = false;
	}
	CoInitializeSecurity(nullptr, -1, nullptr, nullptr, RPC_C_AUTHN_LEVEL_DEFAULT,
		RPC_C_IMP_LEVEL_IMPERSONATE, nullptr, EOAC_NONE, nullptr);
	initialize_wbem();
}

wmi_srvc::~wmi_srvc() {
	if(m_is_init) {
		CoUninitialize();
	}
}

string wmi_srvc::simple_query(const string projection, const string from) const {
	return simple_query(projection, from, "");
}

string wmi_srvc::simple_query(const string projection, const string from, const string where) const {
	CComPtr<IEnumWbemClassObject> wbemEnum;
	string rawQueryStr("Select " + projection);
	rawQueryStr.append(" From " + from);
	
	if (!where.empty()) {
		rawQueryStr.append(" Where " + where);
	}
	CComBSTR query = rawQueryStr.c_str();

	if(FAILED(m_wbem_services->ExecQuery(CComBSTR("WQL"), query, WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY, nullptr, &wbemEnum))) {
		return "Failed to query WMI";
	}

	ULONG uObjectCount = 0;
	CComPtr<IWbemClassObject> pWmiObject;
	if(FAILED(wbemEnum->Next(WBEM_INFINITE, 1, &pWmiObject, &uObjectCount))) {
		return "Failed to query WMI";
	}

	CComVariant cvtVersion;
	if(FAILED(pWmiObject->Get(L"Version", 0, &cvtVersion, 0, 0))) {
		return "Failed to query WMI";
	}

	return string(CW2A(cvtVersion.bstrVal));
}

bool wmi_srvc::initialize_wbem() {
	if(FAILED(m_wbem_locator.CoCreateInstance(CLSID_WbemLocator))) {
		return false;
	}
	if(FAILED(m_wbem_locator->ConnectServer(CComBSTR(L"root\\cimv2"), nullptr, nullptr, 0, 0, 0, nullptr, &m_wbem_services))) {
		return false;
	}
	return true;
}

#endif