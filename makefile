
all:
	pacman -Sy --noconfirm asciidoctor
	mkdir build
	asciidoctor -o build/index.html README.asciidoc

