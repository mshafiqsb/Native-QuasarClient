@ECHO OFF
IF NOT EXIST ".\lib\libcryptopp.a" (
	cd ".\cryptopp"
	cmake ".\CMakeLists.txt" -G "MinGW Makefiles" -DBUILD_SHARED=OFF -DBUILD_TESTING=OFF
	mingw32-make
	cd ".."
	IF NOT EXIST ".\lib" (
		mkdir ".\lib"
	)
	copy ".\cryptopp\libcryptopp.a" ".\lib\libcryptopp.a"
)
 
cmake ".\CMakeLists.txt" -G "MinGW Makefiles"
mingw32-make
PAUSE