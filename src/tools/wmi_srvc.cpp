#include "stdafx.h"
#include "wmi_srvc.h"
#ifdef USE_WMI

#include <atlbase.h>
#include <wbemidl.h>
#pragma comment(lib, "wbemuuid.lib")

#endif


using namespace std;

#ifdef USE_WMI

wmi_srvc::wmi_srvc() {

}

wmi_srvc::~wmi_srvc() {

}

string simple_query(const string projection, string from, string select) {
	return "";
}

#endif