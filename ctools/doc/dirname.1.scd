dirname(1) "ctools"

# NAME

dirname - print the directory part of a pathname

# SYNOPSIS

*dirname* _string_

# DESCRIPTION

*dirname* will interpret _string_ as a pathname and print only the directory
portion of the path.

# UNSPECIFIED BEHAVIOR

The POSIX standard does not unambiguously specify the behavior of this command
under certain conditions. Under such conditions, the ctools implementation of
*dirname* behaves as follows:

- If the directory part of _string_ is equal to "//", *dirname* may randomly
  choose to output either "/" or "//".

# DISCLAIMER

This command is part of ctools and is compatible with POSIX-1.2017, and may
optionally support XSI extensions. This man page is not intended to be a
complete reference, and where it disagrees with the specification, the
specification takes precedence.
