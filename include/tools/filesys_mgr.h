#include "stdafx.h"

namespace quasar {
	namespace tools {

		class filesys_mgr {
		public:
#ifdef WIN32
			struct drive_info {
				std::string display_name;
				std::string root_dir;
			};
#endif

		};

	}
}