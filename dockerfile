FROM archlinux:latest
RUN pacman -Syu meson base-devel --noconfirm
WORKDIR /SFML
RUN git clone https://github.com/SFML/SFML.git
WORKDIR /BOX2D
RUN git clone https://github.com/erincatto/box2d.git
COPY . /main
