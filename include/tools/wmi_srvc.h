#pragma once

#include <string>

#ifdef USE_WMI

class wmi_srvc {
public:
	wmi_srvc();
	~wmi_srvc();

	std::string simple_query(const std::string projection, std::string from, std::string select);
};

std::string GetOsVersionString();
#endif