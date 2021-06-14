build: 
	meson compile -C Build

run: build
	./Build/GrzesSFMLlib

valgrind: build
	valgrind ./Build/GrzesSFMLlib

buildWindows:
	meson compile -C mingw

wine: buildWindows
	x86_64-w64-mingw32-wine ./mingw/GrzesSFMLlib.exe

.PHONY: sfx setup

sfx: sfxr-raw/*.wav
	for file in $$(ls sfxr-raw/*.wav); do \
		newFile="$$(basename $${file})"; \
		ffmpeg -i $${file} -y resources/sfx/$${newFile}.aac; \
		done
 
setup:
	meson setup Build && \
	x86_64-w64-mingw32-meson mingw --buildtype release -Dwindows=true
