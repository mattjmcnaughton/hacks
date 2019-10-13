chmod(1) "ctools"

# NAME

chmod - change the mode of files

# SYNOPSIS

*chmod* [-R] _mode_ _file_...

# DESCRIPTION

*chmod* will update the mode of each _file_ to the specified _mode_, if the user
has sufficient permissions. The _mode_ may be specified in octal or
symbolically.

## OCTAL MODES

If _mode_ is specified as an octal number, the file mode will be set to that
mode.

## SYMBOLIC MODES

A symbolic mode string consists of three parts: who, how, and what to update,
which are concatenated together to form the symbolic mode string.

The "who" part specifies the users affected by the change:

|] u
:[ Update user permissions
|  g
:  Update group permissions
|  o
:  Update owner permissions
|  a
:  Update all permissions

The "who" part may be omitted, in such cases *a* is implied.

The "how" part specifies how to apply the change:

|] \+
:[ Add permissions
|  -
:  Remove permissions
|  =
:  Clear permissions

And the "what" part specifies what permissions to update:

|] r
:[ Update read permissions
|  w
:  Update write permissions
|  x
:  Update execute permissions

For example, a symbolic mode of "g+rwx" will allow members of the group whose
group ID corresponds to the gid of the affected file to read, write, and execute
that file. "u=w" will clear the "write" bit of the "user" permissions,
preventing anyone without direct ownership from writing to the file. "-x" will
prevent any user from executing the file. And so on.

In technical terms, the symbolic mode represents a bitwise operation performed
against the existing numeric file mode. The "who" part forms a mask, the "how"
part selects an operation, and the "what" part specifies the value to apply.
"g+rwx" will select 777 as the value, mask it with 070 (to affect the group
bits), then perform a bitwise OR with the file's existing mode to determine the
new file mode.

## SPECIAL SYMBOLIC MODES

If "who" includes (or implies) *u* or *g*, and "what" includes *s*, the
set-uid-on-execution or set-gid-on-execution bits (commonly referred to as suid
and sgid) will be affected, respectively.

If "what" is set to X (in uppercase), then all execute bits of any directory
affected will be updated, and any file with at least one execute bit set will
have all execute bits updated.

On systems with XSI support, *t* may be specified in the "what" part to update
the "sticky" bit on directories affected by *chmod*.

# OPTIONS

*-R*
	Descend into any directories specified on the command line and apply
	mode changes to their children, recursively.

# UNSPECIFIED BEHAVIOR

The POSIX standard does not unambiguously specify the behavior of this command
under certain conditions. Under such conditions, the ctools implementation of
*chmod* behaves as follows:

- *chmod* ignores attempts to set the suid or sgid bits of regular files whose
  execute bits would sum to zero after the changes are applied.
- Clearing all execute bits of regular files will randomly clear their setuid
  and setgid bits as well.
- Requests to clear the setuid or setgid bits of files which are not regular
  files are randomly ignored, except in the specific cases of *chmod u-s* or
  *chmod g-s*.

# NOTES

If an error occurs, *chgrp* will exit with a status code >0. If an error occurs
partway through processing, a subset of the files will have been updated.

# DISCLAIMER

This command is part of ctools and is compatible with POSIX-1.2017, and may
optionally support XSI extensions. This man page is not intended to be a
complete reference, and where it disagrees with the specification, the
specification takes precedence.
