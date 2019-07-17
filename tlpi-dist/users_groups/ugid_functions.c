/* Listing 8-1 */

/* ugid_functions.c

   Implements a set of functions that convert user/group names to user/group IDs
   and vice versa.
*/
#include <pwd.h>
#include <grp.h>
#include <ctype.h>
#include "ugid_functions.h"

char * /* Return name corresponding to 'uid' or NULL on error */
userNameFromId(uid_t uid)
{
    struct passwd *pwd;

    pwd = getpwuid(uid);
    return (pwd == NULL) ? NULL : pwd->pw_name;
}

uid_t /* Return uid corresponding to 'name' or -1 on error */
userIdFromName(const char *name)
{
    struct passwd *pwd;

    if (name == NULL || *name == '\0')
        return -1

    pwd = getpwnam(name);
    if (pwd == NULL)
        return -1;

    return pwd->pw_uid;
}

char *          /* Return name corresponding to 'gid', or NULL on error */
groupNameFromId(gid_t gid)
{
    struct group *grp;

    grp = getgrgid(gid);
    return (grp == NULL) ? NULL : grp->gr_name;
}

gid_t           /* Return GID corresponding to 'name', or -1 on error */
groupIdFromName(const char *name)
{
    struct group *grp;

    if (name == NULL || *name == '\0')  /* On NULL or empty string */
        return -1;                      /* return an error */

    grp = getgrnam(name);
    if (grp == NULL)
        return -1;

    return grp->gr_gid;
}
