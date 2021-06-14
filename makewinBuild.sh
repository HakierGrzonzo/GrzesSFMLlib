#!/usr/bin/fish

rm -rf release
echo "Copying application"
mkdir release
cp -v ./mingw/GrzesSFMLlib.exe ./release/GrzesSFMLlib.exe
echo "Copying dlls"
cp -v /usr/x86_64-w64-mingw32/bin/libgcc_s_seh-1.dll \
    /usr/x86_64-w64-mingw32/bin/libwinpthread-1.dll \
    /usr/x86_64-w64-mingw32/bin/libstdc++-6.dll \
    /usr/x86_64-w64-mingw32/bin/OpenAL32.dll \
    /usr/x86_64-w64-mingw32/bin/avcodec-58.dll \
    /usr/x86_64-w64-mingw32/bin/zlib1.dll \
    /usr/x86_64-w64-mingw32/bin/avutil-56.dll \
    /usr/x86_64-w64-mingw32/bin/swresample-3.dll \
    /usr/x86_64-w64-mingw32/bin/avformat-58.dll \
    /usr/x86_64-w64-mingw32/bin/libbz2-1.dll \
    /usr/x86_64-w64-mingw32/bin/libbox2d.dll \
    /usr/x86_64-w64-mingw32/bin/sfml-graphics-2.dll \
    /usr/x86_64-w64-mingw32/bin/sfml-system-2.dll \
    /usr/x86_64-w64-mingw32/bin/sfml-window-2.dll \
    /usr/x86_64-w64-mingw32/bin/libfreetype-6.dll \
    /usr/x86_64-w64-mingw32/bin/libssp-0.dll \
    ./release/
echo "Copying resources"
cp -vr ./resources ./release
echo "Zipping"
zip -r GrzegorzKoperwas.zip ./release/
