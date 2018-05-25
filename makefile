
all:
	pacman -Sy --noconfirm asciidoctor
	mkdir build
	asciidoctor -o build/index.html README.asciidoc
	asciidoctor -o build/codeforces.html docs/codeforces.asciidoc
	asciidoctor -o build/poi.html docs/poi.asciidoc

