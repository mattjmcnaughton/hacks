# deb-scratch

Scratch pad for experimenting creating `.deb` packages.

## Process

1. Set name: `PACKAGE_MAJOR.MINOR.PATCH-PACKAGE_VERSION-ARCH`. ARCH for all
   machines I have is `amd64`. For example, `zig_0.7.1-1_amd64`.
2. Put program files where I want them installed on the local system. For
   example, if I want the binary to be at `/usr/bin`, it should be at `usr/bin`
   in the package.
3. Create and populate the `control` file. The `Package`, `Version`,
   `Architecture`, `Maintainer` and `Description` fields are mandatory.
4. Build the package with `dpkg-deb --build --root-owner-group PATH_TO_DIR`. The
   `--root-owner-group` makes the files contained within the deb owned by the
   root, which is typically what we want.
5. Install deb with `sudo dpkg -i NAME.deb`
6. Uninstall with `sudo dpkg -r PACKAGE_NAME`.

## Useful resources

- https://www.internalpointers.com/post/build-binary-deb-package-practical-guide
