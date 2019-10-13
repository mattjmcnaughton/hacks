cat(1) "ctools"

# NAME

cat - concatenate files

# SYNOPSIS

*cat* [-u] [_file_...]

# DESCRIPTION

*cat* will read and copy each specified file to _stdout_ in order. If no files
are specified, or "-" is specified, cat will read from _stdin_ instead of a
named file.

# OPTIONS

*-u*
	According to the standard, this option will ostensibly "write bytes from
	the input file to the standard output without delay as each is read",
	but in practice is ignored by the ctools implementation.

# DISCLAIMER

This command is part of ctools and is compatible with POSIX-1.2017, and may
optionally support XSI extensions. This man page is not intended to be a
complete reference, and where it disagrees with the specification, the
specification takes precedence.
