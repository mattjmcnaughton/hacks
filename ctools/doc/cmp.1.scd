cmp(1) "ctools"

# NAME

cmp - compare two files

# SYNOPSIS

*cmp* [-l|-s] _file1_ _file2_

# DESCRIPTION

*cmp* will compare two text files and find the location of the first character
which differs between them. If a difference is found, it will print the
character index and line number at which the difference was found.

# OPTIONS

*-l*
	When a difference is found, instead of printing a human-friendly
	message, print the index (in decimal) and the offending characters
	found there (in octal), separated with spaces.

*-s*
	Do not output anything if the files differ, instead the exit status
	must be consulted to determine the result.

The *-l* and *-s* options are mutually exclusive.

# EXIT STATUS

|] 0
:[ The files are identical
|  1
:  The files are different
|  >1
:  An error occured

# UNSPECIFIED BEHAVIOR

The POSIX standard does not unambiguously specify the behavior of this command
under certain conditions. Under such conditions, the ctools implementation of
*cmp* behaves as follows:

- If an error occurs and *-s* was specified, *cmp* may randomly choose not to
  print the appropriate diagnostic messages to stderr.

# DISCLAIMER

This command is part of ctools and is compatible with POSIX-1.2017, and may
optionally support XSI extensions. This man page is not intended to be a
complete reference, and where it disagrees with the specification, the
specification takes precedence.
