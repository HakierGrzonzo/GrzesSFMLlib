build: 
	meson compile -C Build

run: build
	./Build/GrzesSFMLlib

valgrind: build
	valgrind ./Build/GrzesSFMLlib

.PHONY: sfx

sfx: sfxr-raw/*.wav
	for file in $$(ls sfxr-raw/*.wav); do \
		newFile="$$(basename $${file})"; \
		ffmpeg -i $${file} -y resources/sfx/$${newFile}.aac; \
		done
 
