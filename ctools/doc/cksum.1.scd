cksum(1) "ctools"

# NAME

cksum - calculate the cyclic redundancy check (CRC) for files

# SYNOPSIS

*cksum* _file_...

# DESCRIPTION

*cksum* will calculate the cyclic redundancy check value (CRC, per ISO/IEC
8802-3:1996) and print it, as well as the file size, for each _file_ to stdout.
This purpose of this command is to check the integrity of a file against a
reference copy, for example to verify a file transmitted over a noisy
connection. It is not a cryptographic-grade algorithm.

# DISCLAIMER

This command is part of ctools and is compatible with POSIX-1.2017, and may
optionally support XSI extensions. This man page is not intended to be a
complete reference, and where it disagrees with the specification, the
specification takes precedence.
