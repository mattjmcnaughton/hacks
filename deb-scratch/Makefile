build_zig_deb:
	dpkg-deb --build --root-owner-group zig_0.7.1-1_amd64

install_zig_deb:
	sudo dpkg -i zig_0.7.1-1_amd64.deb

uninstall_zig_deb:
	sudo dpkg -r zig

build_all: build_zig_deb

clean_all:
	rm *.deb
