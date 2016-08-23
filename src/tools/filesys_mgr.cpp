#include "stdafx.h"
#include "filesys_mgr.h"

using namespace std;
using namespace quasar::tools;

#ifdef WIN32

using drive_info = filesys_mgr::drive_info;

const vector<drive_info> filesys_mgr::get_drives() {
	vector<drive_info> drives;
	DWORD drivesMask = GetLogicalDrives();
	if (drivesMask == 0) {
		return drives;
	}

	for (int32_t i = 0; i < sizeof(DWORD) * 4; i++) {
		// if bit is set there is a drive here
		if (drivesMask & 1) {
			drive_info info;
			string rootName(".:\\ "); // placeholder string
			rootName[0] = (char) ('A' + i);
			info.root_dir = rootName;
			drives.push_back(info);
		}
		drivesMask >>= 1;
	}

	char volumeName[MAX_PATH + 1];
	char fileSystemName[MAX_PATH + 1];
	DWORD serialNumber = 0;
	DWORD maxComponentLen = 0;
	DWORD fileSystemFlags = 0;

	for (auto &drive : drives) {
		ZeroMemory(volumeName, sizeof(volumeName));
		ZeroMemory(fileSystemName, sizeof(fileSystemName));

		if (GetVolumeInformation(
				drive.root_dir.c_str(),
				volumeName,
				sizeof(volumeName),
				&serialNumber,
				&maxComponentLen,
				&fileSystemFlags,
				fileSystemName,
				sizeof(fileSystemName)
		)) {
			if (volumeName[0] == '\0') {
				drive.display_name = "";
			} else {
				drive.display_name = "(" + string(volumeName) + ") ";
			}

			/* A: and B: are floppy */
			if(drive.display_name[0] < 'C') {
				drive.display_name.append("[Floppy Disk, ");
			/* C: is primary partition on windows */
			} else if(drive.display_name[0] == 'C') {
				drive.display_name.append("[Primary Partition, ");
			} else {
				drive.display_name.append("[Local Disk, ");
			}

			drive.display_name.append(string(fileSystemName) + "]");
		}
	}

	return drives;
}

#endif