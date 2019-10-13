chgrp(1) "ctools"

# NAME

chgrp - change group ownership of files

# SYNOPSIS

*chgrp* [<-h | -R [-H|-L|-P]>] _group_ _file_...

# DESCRIPTION

*chgrp* will update the group ownership of each _file_ specified to the
requested _group_, if the user has sufficient permissions.

# OPTIONS

*-h*
	Each _file_ specified which is a symbolic link will have the symbolic
	link's ownership updated, rather than the link target.

*-R*
	Descend into any directories specified on the command line and apply
	ownership changes to their children, recursively.

*-H*
	When a symlink which refers to a directory is specified on the command
	line, *chgrp* will update the directory it refers to rather than the
	symlink itself, as well as all of its children, recursively.

*-L*
	When a symlink which refers to a directory is specified on the command
	line or encountered while *chgrp* recursivly descends the filesystem,
	*chgrp* will update the directory it refers to rather than the symlink
	itself, as well as all of its children, recursively.

*-P*
	When a symlink which refers to a directory is specified on the command
	line or encountered while *chgrp* recursivly descends the filesystem,
	*chgrp* will update the ownership of the symlink itself and will not
	update the target or any of its children.

The *-h* option is mutually incompatible with the *-R* option. The *-H*, *-L*,
and *-P* options have no effect unless *-R* is also specified.

# UNSPECIFIED BEHAVIOR

The POSIX standard does not unambiguously specify the behavior of this command
under certain conditions. Under such conditions, the ctools implementation of
*chgrp* behaves as follows:

- If *-R* is specified but not any option between *-H*, *-L*, and *-P*, one of
  these options will be chosen randomly as the default behavior.

# NOTES

If an error occurs, *chgrp* will exit with a status code >0. If an error occurs
partway through processing, a subset of the files will have been updated.

# DISCLAIMER

This command is part of ctools and is compatible with POSIX-1.2017, and may
optionally support XSI extensions. This man page is not intended to be a
complete reference, and where it disagrees with the specification, the
specification takes precedence.
