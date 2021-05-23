configRel:
	meson configure Build -Dbuildtype=release

configDeb:
	meson configure Build -Dbuildtype=release

build: configRel
	meson compile -C Build

buildDebug: configDeb
	meson compile -C Build

debug: buildDebug
	./Build/GrzesSFMLlib

run: build
	./Build/GrzesSFMLlib

valgrind: buildDebug
	valgrind -s ./Build/GrzesSFMLlib
