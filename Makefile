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
	install -Dm644 src/data/icons/*.svg $(datadir)/krudio/icons
	install -Dm755 src/data/krudio.desktop $(datadir)/applications/krudio.desktop
	install -Dm755 src/krudio $(bindir)/krudio
	ln -s $(datadir)/krudio/icons/krudio.svg $(datadir)/icons/hicolor/48x48/apps/krudio.svg
	ln -s $(datadir)/krudio/icons/krudiotray-dark-off16.svg $(datadir)/icons/hicolor/16x16/status/krudiotray-dark-off16.svg
	ln -s $(datadir)/krudio/icons/krudiotray-dark-on16.svg $(datadir)/icons/hicolor/16x16/status/krudiotray-dark-on16.svg
	ln -s $(datadir)/krudio/icons/krudiotray-light-off16.svg $(datadir)/icons/hicolor/16x16/status/krudiotray-light-off16.svg
	ln -s $(datadir)/krudio/icons/krudiotray-light-on16.svg $(datadir)/icons/hicolor/16x16/status/krudiotray-light-on16.svg
	ln -s $(datadir)/krudio/icons/krudiotray-dark-off22.svg $(datadir)/icons/hicolor/22x22/status/krudiotray-dark-off22.svg
	ln -s $(datadir)/krudio/icons/krudiotray-dark-on22.svg $(datadir)/icons/hicolor/22x22/status/krudiotray-dark-on22.svg
	ln -s $(datadir)/krudio/icons/krudiotray-light-off22.svg $(datadir)/icons/hicolor/22x22/status/krudiotray-light-off22.svg
	ln -s $(datadir)/krudio/icons/krudiotray-light-on22.svg $(datadir)/icons/hicolor/22x22/status/krudiotray-light-on22.svg
	ln -s $(datadir)/krudio/icons/krudiotray-dark-off24.svg $(datadir)/icons/hicolor/24x24/status/krudiotray-dark-off24.svg
	ln -s $(datadir)/krudio/icons/krudiotray-dark-on24.svg $(datadir)/icons/hicolor/24x24/status/krudiotray-dark-on24.svg
	ln -s $(datadir)/krudio/icons/krudiotray-light-off24.svg $(datadir)/icons/hicolor/24x24/status/krudiotray-light-off24.svg
	ln -s $(datadir)/krudio/icons/krudiotray-light-on24.svg $(datadir)/icons/hicolor/24x24/status/krudiotray-light-on24.svg

uninstall: 
	rm -rf $(datadir)/krudio
	rm $(datadir)/applications/krudio.desktop
	rm $(bindir)/krudio
	rm $(datadir)/icons/hicolor/48x48/apps/krudio.svg
	rm $(datadir)/icons/hicolor/16x16/status/krudiotray*
	rm $(datadir)/icons/hicolor/22x22/status/krudiotray*
	rm $(datadir)/icons/hicolor/24x24/status/krudiotray*
FORCE:
