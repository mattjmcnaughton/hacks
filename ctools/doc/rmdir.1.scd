rmdir(1) "ctools"

# NAME

rmdir - remove directories

# SYNOPSYS

*rmdir* [-p] _dir_...

# DESCRIPTION

*rmdir* will remove empty directories.

# OPTIONS

*-p*
	Remove a directory and all of its ancestors. For example, rmdir a/b/c
	will remove a/b/c, then a/b, and finally a.

# DISCLAIMER

This command is part of ctools and is compatible with POSIX-1.2017, and may
optionally support XSI extensions. This man page is not intended to be a
complete reference, and where it disagrees with the specification, the
specification takes precedence.
