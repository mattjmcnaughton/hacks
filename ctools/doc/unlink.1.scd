unlink(1) "ctools"

# NAME

unlink - unlink a file

# SYNOPSIS

*unlink* _file1_

# DESCRIPTION

*unlink* will unlink a file. This removes the directory entry and decrements
the reference count on the inode, reclaiming the disk space if the reference
count is zero (the reference count will be nonzero if a hard link has been made
with *link*(1) or by some other means).

# UNSPECIFIED BEHAVIOR

The POSIX standard does not unambiguously specify the behavior of this command
under certain conditions. Under such conditions, the ctools implementation of
*unlink* behaves as follows:

- If _file1_ is a symbolic link, *unlink* will exit with an error without
  unlinking the file.

# DISCLAIMER

This command is part of ctools and is compatible with POSIX-1.2017, and may
optionally support XSI extensions. This man page is not intended to be a
complete reference, and where it disagrees with the specification, the
specification takes precedence.
