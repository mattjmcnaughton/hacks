# ctools

A collection of core tools for a POSIX-compatible operating system.

## Goals

1. Each program is self-contained, with no external dependencies even among
   other parts of ctools.
2. All programs presume the locale is UTF-8.
3. Each program is C99 and compatible with its POSIX.1-2017 specification *and*
   may be built in an environment which provides POSIX.1-2017 system interfaces.
4. Where the specification is ambiguous, implementation-defined, or unspecified,
   the programs choose their behavior at random, to discourage relying on these
   behaviors; or will abort, if practical.

## Compiling

Each "one-shot" tool is a single C file under src/ and can be compiled with the
following:

	c99 -o $tool -D_POSIX_C_SOURCE=200809L src/$tool.c

More complex tools may have several files under one directory:

	c99 -o $tool -D_POSIX_C_SOURCE=200809L -Isrc/$tool/ src/$tool/*.c

To enable optional XSI support, use `-D_XOPEN_SOURCE=700` instead of
`-D_POSIX_C_SOURCE`.

Alternatively, you can compile all of the tools with meson:

	meson . build
	ninja -C build

This is recommended when packaging ctools for meson-supported systems. Some
options are available when building with meson, consult meson_options.txt.

## Documentation

Man pages are provided via [scdoc](https://git.sr.ht/~sircmpwn/scdoc) and may be
found in the `doc` directory. If using meson and scdoc is installed, man pages
are built and installed by default. Note that a manual reader is not provided by
ctools, though the `man` command must do something useful for your system to be
considered POSIX compatible.

## Conformance tests

Build with meson and run `ninja -C build test` to run POSIX conformance tests
against ctools.

Some conformance tests require Linux to be run, and will be skipped on other
systems. These tests generally require some non-portable behavior to verify the
behavior of some commands; for example the `nice` tests will inspect `/proc` to
verify its behavior. Unsupported systems will skip these tests.

Additional tests may be skipped if certain external environment variables are
not provided. To run all supported tests for your system, set the following
variables in your environment:

- `ARCH` to the value expected to be printed by `uname -m`.
- `ESCALATE` to the name of a command which will run an arbitrary program as the
  system administrator, such as `sudo`.

## Scope

ctools includes POSIX.1-2017 base utilities, but does not support any
POSIX.1-2017 [option groups][conformance], with the exception of XSI support
where relevant to POSIX base utilities (optional). See the STATUS file for a
summary of utilities defined by POSIX and their status for inclusion in ctools.

[conformance]: https://pubs.opengroup.org/onlinepubs/9699919799/basedefs/V1_chap02.html#tag_02_01_06_02

A shell is not provided. [mrsh](https://mrsh.sh) is recommended for this
purpose.

## Contributing

Mail patches, bugs, etc, to the mailing list:
[~sircmpwn/ctools@lists.sr.ht][mailto]

[mailto]: mailto:~sircmpwn/ctools@lists.sr.ht

Consult https://git-send-email.io for information on preparing patches.
