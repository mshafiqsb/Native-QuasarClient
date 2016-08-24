#include <boost/range/iterator_range_core.hpp>
#include "stdafx.h"
#include "filesys_mgr.h"
#include "boost/filesystem.hpp"

using namespace std;
using namespace quasar::tools;
using namespace boost;
using namespace boost::filesystem;

using drive_info = filesys_mgr::drive_info;
using file_info = filesys_mgr::file_info;

#ifdef WIN32

const vector<drive_info> filesys_mgr::get_drives() {
	vector<drive_info> drives;
#ifdef WIN32
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
			info.m_root_dir = rootName;
			info.m_display_name = rootName;
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
				drive.m_root_dir.c_str(),
				volumeName,
				sizeof(volumeName),
				&serialNumber,
				&maxComponentLen,
				&fileSystemFlags,
				fileSystemName,
				sizeof(fileSystemName)
		)) {
			if (volumeName[0] != '\0') {
				drive.m_display_name.append("(" + string(volumeName) + ") ");
			}

			/* A: and B: are floppy */
			if (drive.m_display_name[0] < 'C') {
				drive.m_display_name.append("[Floppy Disk, ");
				/* C: is primary partition on windows */
			} else if (drive.m_display_name[0] == 'C') {
				drive.m_display_name.append("[Primary Partition, ");
				//TODO: maybe add more specific common assignments
			} else {
				drive.m_display_name.append("[Local Disk, ");
			}

			drive.m_display_name.append(string(fileSystemName) + "]");
		}
	}
#elif __linux__
	drive_info driveInf;
	driveInf.root_dir = "/";
	drives.push_back(driveInf);
#endif

	return drives;
}

#endif

const vector<file_info> filesys_mgr::get_files(const std::string path) {
	using boost_path = boost::filesystem::path;
	vector<file_info> files;
	string normalizedPath(path);
	normalize_path(normalizedPath);
	boost_path targetPath(normalizedPath);

	if (exists(targetPath) && is_directory(targetPath)) {
		try {
			for (auto &entry : boost::make_iterator_range(directory_iterator(targetPath))) {
				file_info fInf;

				fInf.m_is_directory = false;
				fInf.m_file_name = entry.path().filename().string();
				if (is_directory(entry.path())) {
					fInf.m_is_directory = true;
					fInf.m_file_size = 0;
				} else {
					fInf.m_is_directory = false;
					system::error_code ec;
					uint64_t size = 0;
					// i don't think this throws on error
					if ((size = filesystem::file_size(entry.path(), ec)) != static_cast<uint64_t>(-1)) {
						fInf.m_file_size = size;
					} else {
						fInf.m_file_size = 0;
					}
				}
				files.push_back(fInf);
			}
		} catch(const filesystem_error &ex){
			return files;
		}
	}

	return files;
}

void filesys_mgr::normalize_path(std::string &path) {
	//TODO: extend this

	/* trim path */
	/* left */
	path.erase(path.begin(), find_if(path.begin(), path.end(), not1(ptr_fun<int, int>(isspace))));
	/* right */
	path.erase(find_if(path.rbegin(), path.rend(), not1(ptr_fun<int,int>(isspace))).base(), path.end());
}