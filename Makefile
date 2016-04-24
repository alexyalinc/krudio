prefix	?= /usr
bindir := $(prefix)/bin
datadir := $(prefix)/share

all:
	cd src && qmake 
	cd src && make

clean:
	cd src && make clean

####### Install

install:
	mkdir -p $(datadir)/krudio/icons
	install -Dm644 src/data/icons/krudio.svg $(datadir)/icons/hicolor/48x48/apps/krudio.svg
	install -Dm644 src/data/icons/*.svg $(datadir)/krudio/icons
	install -Dm755 src/data/krudio.desktop $(datadir)/applications/krudio.desktop
	install -Dm755 src/krudio $(bindir)/krudio

uninstall: 
	rm -rf $(datadir)/krudio
	rm $(datadir)/icons/hicolor/48x48/apps/krudio.svg
	rm $(datadir)/applications/krudio.desktop
	rm $(bindir)/krudio

FORCE:
