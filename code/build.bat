@Echo off

mkdir ..\..\build > nul
pushd ..\..\build
cl -Zi ..\handmade\code\win32_handmade.cpp user32.lib
popd