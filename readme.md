Native QuasarClient
======================
### Table of contents

* [What is it](#what-is-it)
* [Feature list](#feature-list)
    * [Windows](#windows-features)
    * [Linux](#linux-features)
* [Compiling](#compiling)
    * [Prerequisites](#prerequisites)
		* [Windows](#windows)
        * [Linux](#linux)
	* [Windows](#compiling-on-windows)
    * [Linux](#compiling-on-linux)

## What is it?
Native QuasarClient is a native implementation of the client part for [QuasarRAT](https://github.com/quasar/QuasarRAT). Since the original client is created in C# and depends on the .NET framework it creates some portability issues. This client aims to maximize the clients portability by creating it in C++ and using native APIs for multiple platforms and operating systems. 

## Feature list
*: not completetely implemented
### Windows features
- [x] TCP network stream
    - [x] IPv4 Support
    - [ ] IPv6 Support
- [x] Compressed (QuickLZ) & Encrypted (AES-128) communication
- [x] Multi-Threaded
- [ ] UPnP Support
- [ ] No-Ip.com Support
- [ ] Visit Website (hidden & visible)
- [x] Show MessageBox
- [x] Task Manager
- [x] File Manager *
- [ ] Startup Manager
- [ ] Remote Desktop
- [ ] Remote Webcam
- [ ] Remote Shell
- [ ] Download & Execute
- [ ] Upload & Execute
- [x] System information *
- [ ] Computer Commands (Restart, Shutdown, Standby)
- [ ] Keylogger (Unicode Support)
- [ ] Reverse Proxy (SOCKS5)
- [ ] Password Recovery (Common Browsers and FTP Clients)
- [ ] Registry Editor

### Linux features
- [x] TCP network stream
    - [x] IPv4 Support
    - [ ] IPv6 Support
- [x] Compressed (QuickLZ) & Encrypted (AES-128) communication
- [x] Multi-Threaded
- [ ] UPnP Support
- [ ] No-Ip.com Support
- [ ] Visit Website (hidden & visible)
- [ ] Show MessageBox
- [x] Task Manager *
- [x] File Manager *
- [ ] Startup Manager
- [ ] Remote Desktop
- [ ] Remote Webcam
- [ ] Remote Shell
- [ ] Download & Execute
- [ ] Upload & Execute
- [x] System information *
- [x] Computer Commands (Restart, Shutdown, Standby)
- [ ] Keylogger (Unicode Support)
- [ ] Reverse Proxy (SOCKS5)
- [ ] Password Recovery (Common Browsers and FTP Clients)
- [ ] ~~Registry Editor~~ (Registry on Linux? I think not)

## Compiling
### Prerequisites
##### Windows
* CMake >= 3.5
* Boost >= 1.58.0
* GCC >= 4.9.2 (See [MinGW](http://www.mingw.org/wiki/howto_install_the_mingw_gcc_compiler_suite))
* MSVC (Alternative to GCC/MinGW)

##### Linux
* CMake Ver >= 3.5
* Boost >= 1.58.0
* GCC >= 4.9.2
* Make >= 4.1

### Compiling on windows
(Requires proper setup of MinGW including PATH environment variables set to use build script)

1. Clone the repository
    * `> git clone --recursive https://github.com/UbbeLoL/Native-QuasarClient.git`
2. Navigate to the NativeClient directory
    * `> cd .\QuasarRAT\NativeClient`
3. Run "*build-(configuration)-(toolset).bat*"

### Compiling on linux
(Step 2 to 4 is only required first compilation)

1. Clone the repository
    * `$ git clone --recursive https://github.com/UbbeLoL/Native-QuasarClient.git`
2. Navigate to the CryptoPP directory
    * `$ cd ./QuasarRAT/NativeClient/cryptopp`
3. Build cryptopp (Only need to do this once)
    * `$ cmake CMakeLists.txt && make`
4. Create "*lib/*" directory and copy "*cryptopp.a*" to it
    * `$ mkdir ../lib && mv libcryptopp.a ../lib/libcryptopp.a`
5. Navigate to the NativeClient directory
    * `$ cd ../`
6. Build NativeClient
    * `$ cmake CMakeLists.txt && make`
