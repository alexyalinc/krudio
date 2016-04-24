prefix	?= /usr

all:
	cd src && qmake 
	cd src && make

clean:
	cd src && make clean

####### Install

install:
	install -Dm755 src/icons/48x48/apps/krudio.svg $(prefix)/share/icons/hicolor/48x48/apps/krudio.svg
	install -Dm755 src/krudio $(prefix)/bin/krudio
	install -Dm755 data/krudio.desktop $(prefix)/share/applications/krudio.desktop

uninstall: 
	rm $(prefix)/share/icons/hicolor/48x48/apps/krudio.svg
	rm $(prefix)/share/applications/krudio.desktop
	rm $(prefix)/bin/krudio

FORCE:
