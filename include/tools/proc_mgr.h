#pragma once

#include <cstdint>
#include <string>
#include <vector>

#ifdef WIN32

#include <windows.h>

#endif

namespace quasar {
	namespace tools {

		struct process_info {
			int32_t pid;
			std::string proc_name;
			std::string main_wnd_title;
		};

		class proc_mgr {
		public:
			static std::vector<process_info> get_proc_infos();
			static void kill_process(int32_t pid);
			static bool start_process(std::string file);

		private:
#ifdef WIN32
			static std::string get_proc_name(DWORD pid);
			static std::string get_proc_main_title(DWORD pid);
#elif __linux__
			static std::string get_proc_name(int32_t pid);
			static std::string get_proc_main_title(int32_t pid);
#endif
#ifdef WIN32
			static BOOL CALLBACK
			enum_windows_proc_cb(HWND
													 hwnd,
													 LPARAM lParam
			);
			static bool is_main_window(HWND hwnd);
#endif
		};

	}
}