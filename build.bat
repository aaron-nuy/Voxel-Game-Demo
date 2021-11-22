mkdir build\bin
cmake -S  . -B build/
cmake --build build --config Release
@RD /S /Q %cd%"/build/release"