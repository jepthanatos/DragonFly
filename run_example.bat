rm -rf build

conan install . --output-folder=build --build=missing
cd build
cmake .. -G "Visual Studio 17 2022" -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_POLICY_DEFAULT_CMP0091=NEW
cmake --build . --config Release
cp ../WinterSong.ttf src/Release/WinterSong.ttf
src/Release/Dragonfly_run.exe
cd ..