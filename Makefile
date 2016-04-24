prefix	?= /usr

all:
	cd src && qmake 
	cd src && make

clean:
	cd src && make clean

####### Install

install:
	install -Dm644 data/icons/hicolor/16x16/status/krudio*.svg $(prefix)/share/icons/hicolor/16x16/status
	install -Dm644 data/icons/hicolor/22x22/status/krudio*.svg $(prefix)/share/icons/hicolor/22x22/status
	install -Dm644 data/icons/hicolor/24x24/status/krudio*.svg $(prefix)/share/icons/hicolor/24x24/status
	install -Dm644 data/icons/hicolor/48x48/apps/krudio.svg $(prefix)/share/icons/hicolor/48x48/apps/krudio.svg
	install -Dm755 src/krudio $(prefix)/bin/krudio
	install -Dm755 data/krudio.desktop $(prefix)/share/applications/krudio.desktop

uninstall:
	rm $(prefix)/share/icons/hicolor/16x16/status/krudio*.svg
	rm $(prefix)/share/icons/hicolor/22x22/status/krudio*.svg
	rm $(prefix)/share/icons/hicolor/24x24/status/krudio*.svg
	rm $(prefix)/share/icons/hicolor/48x48/apps/krudio.svg
	rm $(prefix)/share/applications/krudio.desktop
	rm $(prefix)/bin/krudio

FORCE:
