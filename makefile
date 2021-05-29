build: 
	meson compile -C Build

run: build
	./Build/GrzesSFMLlib

valgrind: build
	valgrind ./Build/GrzesSFMLlib
