#include "stdafx.h"
#include "tools/proc_mgr.h"
#include "helpers.h"
#include "boost/filesystem.hpp"
#include "boost/algorithm/string.hpp"
#include "boost/filesystem/fstream.hpp"

#ifdef WIN32

#include <TlHelp32.h>
#include <psapi.h>
#include <shellapi.h>

#endif
#ifdef __linux__

#include <csignal>

#endif

using namespace std;
using namespace boost;

#ifdef __linux

#define BASE_PROC_PATH "/proc/"

#endif

using namespace quasar::tools;

vector<process_info> proc_mgr::get_proc_infos() {
	vector<process_info> procInfos;

#ifdef __WINDOWS__
	DWORD procs[1024], needed;

	if (EnumProcesses(procs, sizeof procs, &needed)) {
		DWORD procCount = needed / sizeof(DWORD);

		for (int32_t i = 0; i < procCount; i++) {
			process_info pinfo;
			pinfo.pid = static_cast<int32_t>(procs[i]);
			pinfo.proc_name = get_proc_name(procs[i]);
			//TODO: fix widechar string stuff for deserializer...
			pinfo.main_wnd_title = ""; //get_proc_main_title(procs[i]);
			procInfos.push_back(pinfo);
		}
	}
#elif __linux__
	filesystem::path baseProcPath(BASE_PROC_PATH);
	if(filesystem::exists(baseProcPath) && filesystem::is_directory(baseProcPath)){
		for(auto &file : boost::make_iterator_range(filesystem::directory_iterator(baseProcPath), {})) {
			string name = file.path().filename().string();
			// we only want proc/pid/*
			if(!helpers::is_number(name)) {
				continue;
			}
			int32_t pid = 0;
			try {
				pid = stoi(name);
			} catch(...) {
				continue;
			}
			process_info pinfo;
			pinfo.pid = pid;
			pinfo.proc_name = get_proc_name(pid);
			procInfos.push_back(pinfo);
		}
	}
#endif
	return procInfos;
}

void proc_mgr::kill_process(int32_t pid) {
#ifdef __WINDOWS__
	HANDLE proc = OpenProcess(PROCESS_TERMINATE, false, static_cast<DWORD>(pid));
	if (proc == nullptr) {
		return;
	}
	TerminateProcess(proc, -1);
	CloseHandle(proc);
#elif __linux__
	// Just to be safe we don't want to send
	// to more than just one specific process
	if(pid > 0) {
		kill(pid, SIGKILL);
	}
#endif
}

bool proc_mgr::start_process(std::string file) {
#ifdef __WINDOWS__
	if (file.empty() || file == "") {
		return false;
	}

//TODO: fix
	HINSTANCE res = ShellExecute(nullptr, "open", file.c_str(), nullptr, nullptr, SW_SHOW);
	return reinterpret_cast<int>(res) > 32;
#endif
	return false;
}

#ifdef __WINDOWS__

string proc_mgr::get_proc_name(DWORD pid) {
#elif __linux__
	string proc_mgr::get_proc_name(int32_t pid) {
#endif
#ifdef __WINDOWS__
/* http://stackoverflow.com/a/35623208 */
	PROCESSENTRY32 processInfo;
	processInfo.dwSize = sizeof(processInfo);
	auto processesSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (processesSnapshot == INVALID_HANDLE_VALUE) {
		return "<unknown>";
	}

	for (bool bok = static_cast<bool>(Process32First(processesSnapshot, &processInfo)); bok; bok = Process32Next(
			processesSnapshot,
			&processInfo)) {
		if (pid == processInfo.th32ProcessID) {
			CloseHandle(processesSnapshot);
			return string(processInfo.szExeFile);
		}
	}

	CloseHandle(processesSnapshot);
#elif __linux__
	filesystem::path procPath(BASE_PROC_PATH + to_string(pid) + "/status");
	if (filesystem::exists(procPath) && filesystem::is_regular_file(procPath)) {
		filesystem::ifstream procStream(procPath);
		stringstream sstr;
		sstr << procStream.rdbuf();

		vector<string> tokens = helpers::tokenize_string(sstr.str(), '\n');
		for (auto it = tokens.cbegin(); it != tokens.cend(); ++it) {
			if (helpers::string_startswith(*it, "Name")) {
				string procName = *it;
				boost::erase_all(procName, "\t");
				int32_t pos = procName.find(':')+1;
				if(pos != string::npos && procName.size() - pos > 0) {
					procName = procName.substr(pos);
				}
				return procName;
			}
		}
	}
#endif
	return "<unknown>";
}

#ifdef __WINDOWS__

string proc_mgr::get_proc_main_title(DWORD pid) {
#elif __linux__
	string proc_mgr::get_proc_main_title(int32_t pid) {
#endif
#ifdef __WINDOWS__
	process_info pinfo;
	pinfo.main_wnd_title = "";
	pinfo.pid = pid;
	EnumWindows(enum_windows_proc_cb, reinterpret_cast<LPARAM>(&pinfo));
	return pinfo.main_wnd_title;
#endif
	return "";
}

#ifdef __WINDOWS__

BOOL proc_mgr::enum_windows_proc_cb(HWND hwnd, LPARAM lParam) {
	unsigned long pid;
	GetWindowThreadProcessId(hwnd, &pid);
	process_info *procInf = reinterpret_cast<process_info *>(lParam /* pid */);
	if (procInf->pid == pid) {
		if (is_main_window(hwnd)) {
			char title[MAX_PATH];
			GetWindowText(hwnd, title, sizeof(title));
			procInf->main_wnd_title = string(title);
			return false;
		}
	}
	return true;
}

bool proc_mgr::is_main_window(HWND hwnd) {
	/* this is how the .NET CLR does it */
	if (GetWindow(hwnd, GW_OWNER) != nullptr || !IsWindowVisible(hwnd)) {
		return false;
	}
	return true;
}

#endif
