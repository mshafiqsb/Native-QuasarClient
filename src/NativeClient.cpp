#include <iostream>
#include <tools/filesys_mgr.h>
#include "stdafx.h"
#include "quasar_client.h"
#include "wmi_srvc.h"
struct HelloWorld {
	void operator()() const {
		std::cout << "Hello, World!" << std::endl;
	}
};

int main(int argc, char *argv[]) {
	boost::asio::io_service io_srvc;

	HelloWorld h;

	quasar::quasar_client c(io_srvc);

	c.connect(argv[1], "4782");
	io_srvc.run();

	for (;;) {
#ifdef WIN32
		Sleep(1000);
#elif __linux__
		sleep(1000);
#endif
	}
	return 0;
}

