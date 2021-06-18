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

.PHONY: sfx setup graphs docs clean release

sfx: sfxr-raw/*.wav
	for file in $$(ls sfxr-raw/*.wav); do \
		newFile="$$(basename $${file})"; \
		ffmpeg -i $${file} -y resources/sfx/$${newFile}.aac; \
		done
 
clean:
	rm -r mingw/ Build/ || true

release: clean
	meson setup Build --buildtype release && \
	x86_64-w64-mingw32-meson mingw --buildtype release -Dwindows=true

setup: clean
	meson setup Build --buildtype debug && \
	x86_64-w64-mingw32-meson mingw --buildtype debug -Dwindows=true

graphs: 
	for file in $$(ls docs/*.dot); do \
		echo $${file}; \
		dot2tex --autosize --pgf210 --figonly --texmode raw $${file} > $$(echo $${file} | cut -d'.' -f1).tex; \
	done

docs: graphs
	cd docs; xelatex docs.tex

