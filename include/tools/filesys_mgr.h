#include "stdafx.h"
#include <vector>
#include <string>

namespace quasar {
	namespace tools {

		class filesys_mgr {
		public:

#ifdef WIN32
			struct drive_info {
				std::string display_name;
				std::string root_dir;
			};

			static const std::vector<drive_info> get_drives();
#elif __linux__
			inline static const std::string get_drive() {
				return "/";
			}
#endif


		};

	}
}