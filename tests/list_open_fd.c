#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include "pipex.h"

// Fallback in case PATH_MAX is not defined
#ifndef PATH_MAX
#define PATH_MAX 4096
#endif

void list_open_fds(const char *label) {
	const char *fd_dir = "/proc/self/fd";
	DIR *dir = opendir(fd_dir);
	if (!dir) {
		perror("opendir(/proc/self/fd)");
		return;
	}

	struct dirent *entry;
	char link_path[PATH_MAX];
	char resolved_path[PATH_MAX];

	ft_printf_fd(STDERR_FILENO, "\n=== Open FDs [%s] ===\n", label);

	while ((entry = readdir(dir)) != NULL) {
		// Skip . and ..
		if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
			continue;

		int fd = atoi(entry->d_name);
		snprintf(link_path, sizeof(link_path), "%s/%s", fd_dir, entry->d_name);

		ssize_t len = readlink(link_path, resolved_path, sizeof(resolved_path) - 1);
		if (len != -1) {
			resolved_path[len] = '\0';
			ft_printf_fd(STDERR_FILENO, "fd %d -> %s\n", fd, resolved_path);
		} else {
			ft_printf_fd(STDERR_FILENO, "fd %d -> [unreadable] (%s)\n", fd, strerror(errno));
		}
	}

	closedir(dir);
}
