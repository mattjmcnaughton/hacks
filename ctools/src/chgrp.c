/* This file implements both chgrp(1) and chown(1) */
#include <assert.h>
#include <dirent.h>
#include <errno.h>
#include <getopt.h>
#include <grp.h>
#include <libgen.h>
#include <limits.h>
#include <pwd.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

enum program_mode {
	MODE_CHOWN,
	MODE_CHGRP,
};

enum symlink_behavior {
	UNSPECIFIED_LINKS,
	EXPLICIT_LINKS,
	FOLLOW_LINKS,
	UPDATE_LINKS,
};

struct context {
	enum program_mode mode;
	bool explicit_links, recursive;
	enum symlink_behavior symlinks;
	uid_t uid;
	gid_t gid;
};

static void
usage(enum program_mode mode)
{
	switch (mode) {
	case MODE_CHGRP:
		fprintf(stderr, "usage: chgrp [<-h | -R [-H|-L|-P]>] "
				"group file...\n");
		break;
	case MODE_CHOWN:
		fprintf(stderr, "usage: chown [<-h | -R [-H|-L|-P]>] "
				"owner[:group] file...\n");
		break;
	}
}

static int
process(const char *path, struct context *ctx, int depth)
{
	struct stat s;
	if (lstat(path, &s) < 0) {
		perror(path);
		return 1;
	}
	bool recurse = false, chlink = false;
	if (S_ISLNK(s.st_mode) && ctx->recursive) {
		switch (ctx->symlinks) {
		case EXPLICIT_LINKS:
			recurse = depth == 0;
			break;
		case FOLLOW_LINKS:
			recurse = true;
			break;
		case UPDATE_LINKS:
			chlink = true;
			break;
		default:
			assert(0);
		}
	}
	if (S_ISLNK(s.st_mode) && ctx->explicit_links) {
		chlink = true;
	}
	if (S_ISDIR(s.st_mode) && ctx->recursive) {
		recurse = true;
	}

	gid_t gid;
	uid_t uid;
	switch (ctx->mode) {
	case MODE_CHGRP:
		gid = ctx->gid;
		uid = s.st_uid;
		break;
	case MODE_CHOWN:
		uid = ctx->uid;
		gid = ctx->gid ? ctx->gid : s.st_gid;
		break;
	}

	int res;
	if (chlink) {
		res = lchown(path, uid, gid);
	} else {
		res = chown(path, uid, gid);
	}
	if (res < 0) {
		perror(path);
		return 1;
	}

	DIR *dir = NULL;
	int r = 0;
	if (recurse) {
		dir = opendir(path);
		if (!dir) {
			perror(path);
			return 1;
		}
		errno = 0;
		struct dirent *dirent;
		char subpath[PATH_MAX + 1];
		while ((dirent = readdir(dir))) {
			if (strcmp(dirent->d_name, ".") == 0
					|| strcmp(dirent->d_name, "..") == 0) {
				continue;
			}
			assert(strlen(path) + strlen(dirent->d_name)
					+ 1 < PATH_MAX);
			strcpy(subpath, path);
			strcat(subpath, "/");
			strcat(subpath, dirent->d_name);
			if (process(subpath, ctx, depth + 1) != 0) {
				r = -1;
				goto out;
			}
		}
		if (errno != 0) {
			perror(path);
			r = -1;
			goto out;
		}
	}

out:
	if (dir != NULL) {
		closedir(dir);
	}

	return r;
}

int
main(int argc, char *argv[])
{
	struct context ctx = { 0 };

	if (strcmp(basename(argv[0]), "chgrp") == 0) {
		ctx.mode = MODE_CHGRP;
	} else if (strcmp(basename(argv[0]), "chown") == 0) {
		ctx.mode = MODE_CHOWN;
	}

	char c;
	while ((c = getopt(argc, argv, "hRHLP")) != -1) {
		switch (c) {
		case 'h':
			if (ctx.recursive) {
				fprintf(stderr, "%s: -h and -R are mutually "
						"exclusive\n", argv[0]);
				return 1;
			}
			ctx.explicit_links = true;
			break;
		case 'R':
			if (ctx.explicit_links) {
				fprintf(stderr, "%s: -h and -R are mutually "
						"exclusive\n", argv[0]);
				return 1;
			}
			ctx.recursive = true;
			break;
		case 'H':
			ctx.symlinks = EXPLICIT_LINKS;
			break;
		case 'L':
			ctx.symlinks = FOLLOW_LINKS;
			break;
		case 'P':
			ctx.symlinks = UPDATE_LINKS;
			break;
		default:
			usage(ctx.mode);
			return 1;
		}
	}

	if (ctx.recursive && ctx.symlinks == UNSPECIFIED_LINKS) {
		/* Unless a -H, -L, or -P option is specified, it is unspecified
		 * which of these options will be used as the default. */
		srand((unsigned int)time(NULL));
		ctx.symlinks = (enum symlink_behavior)((rand() % 3) + 1);
	}

	argc -= optind;
	argv = &argv[optind];

	if (argc < 2) {
		usage(ctx.mode);
		return 1;
	}

	char *owner, *group;
	struct group *gr;
	struct passwd *pw;
	switch (ctx.mode) {
	case MODE_CHGRP:
		if ((gr = getgrnam(argv[0])) == 0) {
			if (errno == 0) {
				fprintf(stderr, "%s: no such group\n", argv[0]);
			} else {
				perror(argv[0]);
			}
			return 1;
		}
		ctx.gid = gr->gr_gid;
		break;
	case MODE_CHOWN:
		owner = strtok(argv[0], ":");
		if ((pw = getpwnam(owner)) == 0) {
			if (errno == 0) {
				fprintf(stderr, "%s: no such user\n", owner);
			} else {
				perror(owner);
			}
			return 1;
		}
		ctx.uid = pw->pw_uid;
		group = strtok(NULL, ":");
		if (group) {
			if ((gr = getgrnam(group)) == 0) {
				if (errno == 0) {
					fprintf(stderr, "%s: no such group\n",
							group);
				} else {
					perror(group);
				}
				return 1;
			}
			ctx.gid = gr->gr_gid;
		}
		break;
	}

	for (int i = 1; i < argc; ++i) {
		if (process(argv[i], &ctx, 0) != 0) {
			return 1;
		}
	}

	return 0;
}
