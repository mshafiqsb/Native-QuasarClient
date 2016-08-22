@ECHO OFF
IF NOT EXIST ".\lib\cryptopp.lib" (
	cd ".\cryptopp"
	cmake ".\CMakeLists.txt" -G "Visual Studio 14 2015" -DBUILD_SHARED=OFF -DBUILD_TESTING=OFF
	"%windir%\Microsoft.NET\Framework\v4.0.30319\msbuild.exe" ".\static.vcxproj"
	cd ".."
	IF NOT EXIST ".\lib" (
		mkdir ".\lib"
	)
	copy ".\cryptopp\Debug\cryptopp-static.lib" ".\lib\cryptopp.lib"
)
 
cmake ".\CMakeLists.txt" -G "Visual Studio 14 2015" -DBoost_USE_STATIC_LIBS=ON -DBoost_USE_STATIC_RUNTIME=ON
"%windir%\Microsoft.NET\Framework\v4.0.30319\msbuild.exe" ".\NativeClient.vcxproj"
PAUSE