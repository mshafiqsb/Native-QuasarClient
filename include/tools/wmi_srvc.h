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

			bool simple_query(const std::string projection, const std::string from, std::string &output) const;
			bool simple_query(const std::string projection, const std::string from, const std::string where, std::string &output) const;

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