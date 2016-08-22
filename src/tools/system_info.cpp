#include "stdafx.h"
#include "system_info.h"
#include "helpers.h"

#ifdef __linux__
#include <unistd.h>
#include <limits.h>

#endif

#ifdef WIN32
#define XP_VER_MAJOR 5

#define VISTA_VER_MAJOR 6

#define W7_VER_MAJOR 6
#define W7_VER_MINOR 1

#define W8_VER_MAJOR 6
#define W8_VER_MINOR 2
#define W8_VER_BUILD 9200

#define W81_VER_MAJOR 6
#define W81_VER_MINOR 3

#define W10_VER_MAJOR 10
#define W10_VER_MINOR 0
#endif

using namespace std;
using namespace quasar::tools;
using namespace boost;

system_info::system_info() {
	initialize_data();
	initialize_extended_data();
}

#if WIN32 && !__x86_64

typedef struct _TOKEN_ELEVATION {
	DWORD TokenIsElevated;
} TOKEN_ELEVATION, *PTOKEN_ELEVATION;

#endif

string system_info::get_account_type() {
	return m_account_type;
}

string system_info::get_pcname() {
	return m_pcname;
}

string system_info::get_username() {
	return m_username;
}

string system_info::get_operating_system() {
	return m_os;
}

string system_info::get_city() {
	return m_city;
}

string system_info::get_country() {
	return m_country;
}

string system_info::get_country_code() {
	return m_country_code;
}

string system_info::get_region() {
	return m_region;
}

void system_info::initialize_data() {
#ifdef WIN32
	TCHAR infoBuf[255];
	DWORD bufCharCount = 255;

	bufCharCount = 255;
	if (!GetComputerName(infoBuf, &bufCharCount)) {
		m_pcname = "<unknown>";
	}

	m_pcname = string(infoBuf);

	if (!GetUserName(infoBuf, &bufCharCount)) {
		m_username = "<unknown>";
	}

	m_username = string(infoBuf);

	bool fRet = false;
	HANDLE hToken = nullptr;
	if (OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken)) {
		TOKEN_ELEVATION Elevation;
		int cbSize = sizeof(TOKEN_ELEVATION);
		if (GetTokenInformation(hToken, (TOKEN_INFORMATION_CLASS) 20 /* TokenElevation */, &Elevation,
								sizeof(Elevation), reinterpret_cast<PDWORD>(&cbSize))) {
			fRet = Elevation.TokenIsElevated;
		}
	}
	if (hToken) {
		CloseHandle(hToken);
	}
	m_account_type = fRet ? "Admin" : "Guest";

	string outStr("Unknown OS");
	OSVERSIONINFO osVInf;
	ZeroMemory(&osVInf, sizeof(OSVERSIONINFO));
	osVInf.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);

	if (GetVersionEx(&osVInf) != 0 || osVInf.dwPlatformId != VER_PLATFORM_WIN32_NT) {
		if (osVInf.dwMajorVersion >= XP_VER_MAJOR) {
			outStr = "Windows XP";
		}
		if (osVInf.dwMajorVersion >= VISTA_VER_MAJOR) {
			outStr = "Windows Vista";
		}
		if (osVInf.dwMajorVersion >= W7_VER_MAJOR && osVInf.dwMinorVersion >= W7_VER_MINOR) {
			outStr = "Windows 7";
		}
		if (osVInf.dwMajorVersion >= W8_VER_MAJOR && osVInf.dwMinorVersion >= W8_VER_MINOR
			&& osVInf.dwBuildNumber >= W8_VER_BUILD) {
			outStr = "Windows 8";
		}
		if (osVInf.dwMajorVersion >= W81_VER_MAJOR && osVInf.dwMinorVersion >= W81_VER_MINOR) {
			outStr = "Windows 8.1";
		}
		if (osVInf.dwMajorVersion >= W10_VER_MAJOR && osVInf.dwMinorVersion >= W10_VER_MINOR) {
			outStr = "Windows 10";
		}
	}
	m_os = outStr;
#elif __linux__
	char hostname[256];
	if(gethostname(hostname, 256) != 0) {
		m_pcname = "<unknown>";
	}

	m_pcname = string(hostname);

	register struct passwd *pw;
	register uid_t uid;
	int c;

	uid = geteuid ();
	pw = getpwuid (uid);
	if (!pw) {
		m_username = "<unknown>";
	}

	m_username = string(pw->pw_name);
	m_account_type = geteuid() == 0 ? "Root" : "Guest";

	filesystem::path file("/etc/lsb-release");
	if (!filesystem::exists(file)) {
		m_os = "Linux";
	}
	filesystem::ifstream lsbrelStream(file);
	if (!lsbrelStream) {
		m_os = "Linux";
	}
	std::string curLine;
	while (std::getline(lsbrelStream, curLine)) {
		if (helpers::string_startswith(curLine, "DISTRIB_DESCRIPTION=")) {
			boost::erase_all(curLine, "\"");
			int32_t pos = curLine.find('=')+1;
			if(pos != string::npos && curLine.size() - pos > 0) {
				m_os = "Linux (" + curLine.substr(pos) + ")";
			}
		}
	}
#endif

}

void system_info::initialize_extended_data() {
	string json;
	if (helpers::download_webpage("www.ip-api.com", "/json/", json) && json.size() > 0) {
		map<string, string> jsonTokens = helpers::shallow_json_parse(json);
		m_city = jsonTokens["city"];
		m_country = jsonTokens["country"];
		m_country_code = jsonTokens["countryCode"];
		m_region = jsonTokens["regionName"];

	}
}