mkdir build\bin
cmake -S  . -B build/
cmake --build build --config Release
xcopy resources\ build\bin\release\resources\ /E /y
@RD /S /Q %cd%"/build/release"