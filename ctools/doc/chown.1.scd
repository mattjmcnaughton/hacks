chown(1) "ctools"

# NAME

chown - change ownership of files

# SYNOPSIS

*chown* [<-h | -R [-H|-L|-P]>] _owner_[:_group_] _file_...

# DESCRIPTION

*chown* will update the ownership of each _file_ specified to the requested
_owner_ (and _group_), if the user has sufficient permissions.

# OPTIONS

*-h*
	Each _file_ specified which is a symbolic link will have the symbolic
	link's ownership updated, rather than the link target.

*-R*
	Descend into any directories specified on the command line and apply
	ownership changes to their children, recursively.

*-H*
	When a symlink which refers to a directory is specified on the command
	line, *chown* will update the directory it refers to rather than the
	symlink itself, as well as all of its children, recursively.

*-L*
	When a symlink which refers to a directory is specified on the command
	line or encountered while *chown* recursivly descends the filesystem,
	*chown* will update the directory it refers to rather than the symlink
	itself, as well as all of its children, recursively.

*-P*
	When a symlink which refers to a directory is specified on the command
	line or encountered while *chown* recursivly descends the filesystem,
	*chown* will update the ownership of the symlink itself and will not
	update the target or any of its children.

The *-h* option is mutually incompatible with the *-R* option. The *-H*, *-L*,
and *-P* options have no effect unless *-R* is also specified.

# UNSPECIFIED BEHAVIOR

The POSIX standard does not unambiguously specify the behavior of this command
under certain conditions. Under such conditions, the ctools implementation of
*chown* behaves as follows:

- If *-R* is specified but not any option between *-H*, *-L*, and *-P*, one of
  these options will be chosen randomly as the default behavior.

# NOTES

If an error occurs, *chown* will exit with a status code >0. If an error occurs
partway through processing, a subset of the files will have been updated.

# DISCLAIMER

This command is part of ctools and is compatible with POSIX-1.2017, and may
optionally support XSI extensions. This man page is not intended to be a
complete reference, and where it disagrees with the specification, the
specification takes precedence.
