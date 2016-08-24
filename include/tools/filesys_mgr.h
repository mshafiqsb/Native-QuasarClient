#pragma once

#include "stdafx.h"
#include <vector>
#include <string>

namespace quasar {
	namespace tools {

		class filesys_mgr {
		public:
			struct drive_info {
				std::string m_display_name;
				std::string m_root_dir;
			};

			struct file_info {
				std::string m_file_name;
				bool m_is_directory;
				uint32_t m_file_size;
			};

			static const std::vector<drive_info> get_drives();
			static const std::vector<file_info> get_files(const std::string path);

		private:
			static void normalize_path(std::string &path);
		};

	}
}