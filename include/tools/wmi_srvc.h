#pragma once

#include "stdafx.h"

#ifdef USE_WMI

#include <atlbase.h>
#include <wbemidl.h>
#pragma comment(lib, "wbemuuid.lib")

#endif

#include <string>

#ifdef USE_WMI

namespace quasar {
	namespace tools {

		class wmi_srvc {
		public:
			wmi_srvc();
			~wmi_srvc();

			std::string simple_query(const std::string projection, const std::string from) const;
			std::string simple_query(const std::string projection, const std::string from, const std::string where) const;

		private:
			bool m_is_init;
			bool m_can_query;
			CComPtr<IWbemLocator> m_wbem_locator;
			CComPtr<IWbemServices> m_wbem_services;

			bool initialize_wbem();
		};

	}
}

#endif