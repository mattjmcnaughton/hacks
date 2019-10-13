link(1) "ctools"

# NAME

link - create a hard link

# SYNOPSIS

*link* _file1_ _file2_

# DESCRIPTION

*link* creates a hard link from _file1_ to _file2_. A hard link creates a new
directory entry which refers to the same underlying file.

# UNSPECIFIED BEHAVIOR

The POSIX standard does not unambiguously specify the behavior of this command
under certain conditions. Under such conditions, the ctools implementation of
*link* behaves as follows:

- If _file1_ is a symbolic link, *link* will exit with an error without
  creating a link.

# DISCLAIMER

This command is part of ctools and is compatible with POSIX-1.2017, and may
optionally support XSI extensions. This man page is not intended to be a
complete reference, and where it disagrees with the specification, the
specification takes precedence.
