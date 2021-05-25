build: 
	meson compile -C Build

run: build
	./Build/GrzesSFMLlib

valgrind: build
	valgrind -s --leak-check=full ./Build/GrzesSFMLlib
