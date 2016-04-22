prefix	?= /usr

all:
	cd src && qmake 
	cd src && make

clean:
	cd src && make clean

####### Install

install:
	cp -r data/icons/hicolor/16x16/* $(prefix)/share/icons/hicolor/16x16/
	cp -r data/icons/hicolor/22x22/* $(prefix)/share/icons/hicolor/22x22/
	cp -r data/icons/hicolor/24x24/* $(prefix)/share/icons/hicolor/24x24/
	cp -r data/icons/hicolor/48x48/* $(prefix)/share/icons/hicolor/48x48/
	cp -r src/krudio /usr/bin/
	cp -r data/krudio.desktop $(prefix)/share/applications/
	install -Dm644 data/icons/hicolor/16x16/status/krudio-dark-off-tray16.svg $(prefix)/share/icons/hicolor/16x16/status/krudio-dark-off-tray16.svg
	install -Dm644 data/icons/hicolor/16x16/status/krudio-dark-on-tray16.svg $(prefix)/share/icons/hicolor/16x16/status/krudio-dark-on-tray16.svg
	install -Dm644 data/icons/hicolor/16x16/status/krudio-light-off-tray16.svg $(prefix)/share/icons/hicolor/16x16/status/krudio-light-off-tray16.svg
	install -Dm644 data/icons/hicolor/16x16/status/krudio-light-on-tray16.svg $(prefix)/share/icons/hicolor/16x16/status/krudio-light-on-tray16.svg
	install -Dm644 data/icons/hicolor/22x22/status/krudio-dark-off-tray22.svg $(prefix)/share/icons/hicolor/22x22/status/krudio-dark-off-tray22.svg
	install -Dm644 data/icons/hicolor/22x22/status/krudio-dark-on-tray22.svg $(prefix)/share/icons/hicolor/22x22/status/krudio-dark-on-tray22.svg
	install -Dm644 data/icons/hicolor/22x22/status/krudio-light-off-tray22.svg $(prefix)/share/icons/hicolor/22x22/status/krudio-light-off-tray22.svg
	install -Dm644 data/icons/hicolor/22x22/status/krudio-light-on-tray22.svg $(prefix)/share/icons/hicolor/22x22/status/krudio-light-on-tray22.svg
	install -Dm644 data/icons/hicolor/24x24/status/krudio-dark-off-tray24.svg $(prefix)/share/icons/hicolor/24x24/status/krudio-dark-off-tray24.svg
	install -Dm644 data/icons/hicolor/24x24/status/krudio-dark-on-tray24.svg $(prefix)/share/icons/hicolor/24x24/status/krudio-dark-on-tray24.svg
	install -Dm644 data/icons/hicolor/24x24/status/krudio-light-off-tray24.svg $(prefix)/share/icons/hicolor/24x24/status/krudio-light-off-tray24.svg
	install -Dm644 data/icons/hicolor/24x24/status/krudio-light-on-tray24.svg $(prefix)/share/icons/hicolor/24x24/status/krudio-light-on-tray24.svg
	install -Dm644 data/icons/hicolor/48x48/apps/krudio.svg $(prefix)/share/icons/hicolor/48x48/apps/krudio.svg
	install -Dm755 src/krudio $(prefix)/bin/krudio
	install -Dm755 data/krudio.desktop $(prefix)/share/applications/krudio.desktop

uninstall:
	rm /usr/share/icons/hicolor/16x16/status/krudio-dark-off-tray16.svg
	rm /usr/share/icons/hicolor/16x16/status/krudio-dark-on-tray16.svg
	rm /usr/share/icons/hicolor/16x16/status/krudio-light-off-tray16.svg
	rm /usr/share/icons/hicolor/16x16/status/krudio-light-on-tray16.svg
	rm /usr/share/icons/hicolor/22x22/status/krudio-dark-off-tray22.svg
	rm /usr/share/icons/hicolor/22x22/status/krudio-dark-on-tray22.svg
	rm /usr/share/icons/hicolor/22x22/status/krudio-light-off-tray22.svg
	rm /usr/share/icons/hicolor/22x22/status/krudio-light-on-tray22.svg
	rm /usr/share/icons/hicolor/24x24/status/krudio-dark-off-tray24.svg
	rm /usr/share/icons/hicolor/24x24/status/krudio-dark-on-tray24.svg
	rm /usr/share/icons/hicolor/24x24/status/krudio-light-off-tray24.svg
	rm /usr/share/icons/hicolor/24x24/status/krudio-light-on-tray24.svg
	rm /usr/share/icons/hicolor/16x16/status/krudio-dark-off-tray.svg
	rm /usr/share/icons/hicolor/16x16/status/krudio-dark-on-tray.svg
	rm /usr/share/icons/hicolor/16x16/status/krudio-light-off-tray.svg
	rm /usr/share/icons/hicolor/16x16/status/krudio-light-on-tray.svg
	rm /usr/share/icons/hicolor/22x22/status/krudio-dark-off-tray.svg
	rm /usr/share/icons/hicolor/22x22/status/krudio-dark-on-tray.svg
	rm /usr/share/icons/hicolor/22x22/status/krudio-light-off-tray.svg
	rm /usr/share/icons/hicolor/22x22/status/krudio-light-on-tray.svg
	rm /usr/share/icons/hicolor/24x24/status/krudio-dark-off-tray.svg
	rm /usr/share/icons/hicolor/24x24/status/krudio-dark-on-tray.svg
	rm /usr/share/icons/hicolor/24x24/status/krudio-light-off-tray.svg
	rm /usr/share/icons/hicolor/24x24/status/krudio-light-on-tray.svg
	rm /usr/share/icons/hicolor/32x32/status/krudio-dark-off-tray.svg
	rm /usr/share/icons/hicolor/32x32/status/krudio-dark-on-tray.svg
	rm /usr/share/icons/hicolor/32x32/status/krudio-light-off-tray.svg
	rm /usr/share/icons/hicolor/32x32/status/krudio-light-on-tray.svg
	rm /usr/share/icons/hicolor/48x48/apps/krudio.svg
	rm /usr/share/applications/krudio.desktop
	rm /usr/bin/krudio

FORCE:
