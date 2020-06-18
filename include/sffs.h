/* Copyright 2011-2018 Tyler Gilbert;
 * This file is part of Stratify OS.
 *
 * Stratify OS is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Stratify OS is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Stratify OS.  If not, see <http://www.gnu.org/licenses/>. */


#ifndef SFFS_H_
#define SFFS_H_

#include <dirent.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/lock.h>

#include <sos/dev/drive.h>
#include <sos/fs/sysfs.h>


typedef struct {
	sysfs_shared_state_t drive;
	int list_block;
	int serialno_killed;
	int serialno;
	drive_info_t dattr;
} sffs_state_t;

typedef struct {
	sysfs_shared_config_t drive;
} sffs_config_t;


int sffs_init(const void * cfg); //initialize the filesystem
int sffs_mkfs(const void * cfg);

int sffs_opendir(const void * cfg, void ** handle, const char * path);
int sffs_readdir_r(const void * cfg, void * handle, int loc, struct dirent * entry);
int sffs_closedir(const void * cfg, void ** handle);


int sffs_mkdir(const void * cfg, const char * path, int mode); //full featured only
int sffs_rmdir(const void * cfg, const char * path); //full featured only

int sffs_fstat(const void * cfg, void * handle, struct stat * stat);
int sffs_open(const void * cfg, void ** handle, const char * path, int flags, int mode);
int sffs_read(const void * cfg, void * handle, int flags, int loc, void * buf, int nbyte);
int sffs_write(const void * cfg, void * handle, int flags, int loc, const void * buf, int nbyte);
int sffs_close(const void * cfg, void ** handle);
int sffs_remove(const void * cfg, const char * path);
int sffs_unlink(const void * cfg, const char * path);

void sffs_unlock(const void * cfg);

int sffs_stat(const void * cfg, const char * path, struct stat * stat);

int sffs_unmount(const void * cfg);
int sffs_ismounted(const void * cfg);

#define SFFS_MOUNT(mount_loc_name, cfgp, permissions_value, owner_value) { \
	.mount_path = mount_loc_name, \
	.permissions = permissions_value, \
	.owner = owner_value, \
	.mount = sffs_init, \
	.unmount = sffs_unmount, \
	.ismounted = sffs_ismounted, \
	.startup = SYSFS_NOTSUP, \
	.mkfs = sffs_mkfs, \
	.open = sffs_open, \
	.aio = SYSFS_NOTSUP, \
	.read = sffs_read, \
	.write = sffs_write, \
	.close = sffs_close, \
	.fsync = SYSFS_NOTSUP, \
	.ioctl = SYSFS_NOTSUP, \
	.rename = SYSFS_NOTSUP, \
	.unlink = sffs_unlink, \
	.mkdir = SYSFS_NOTSUP, \
	.rmdir = SYSFS_NOTSUP, \
	.remove = sffs_remove, \
	.opendir = sffs_opendir, \
	.closedir = sffs_closedir, \
	.readdir_r = sffs_readdir_r, \
	.link = SYSFS_NOTSUP, \
	.symlink = SYSFS_NOTSUP, \
	.stat = sffs_stat, \
	.lstat = SYSFS_NOTSUP, \
	.fstat = sffs_fstat, \
	.chmod = SYSFS_NOTSUP, \
	.chown = SYSFS_NOTSUP, \
	.unlock = sffs_unlock, \
	.config = cfgp, \
	}

#define SFFS_FULL_MOUNT(mount_loc_name, cfgp, permissions_value, owner_value) { \
	.mount_path = mount_loc_name, \
	.permissions = permissions_value, \
	.owner = owner_value, \
	.mount = sffs_init, \
	.unmount = sffs_unmount, \
	.ismounted = sffs_ismounted, \
	.startup = SYSFS_NOTSUP, \
	.mkfs = sffs_mkfs, \
	.open = sffs_open, \
	.aio = SYSFS_NOTSUP, \
	.read = sffs_read, \
	.write = sffs_write, \
	.close = sffs_close, \
	.fsync = SYSFS_NOTSUP, \
	.ioctl = SYSFS_NOTSUP, \
	.rename = SYSFS_NOTSUP, \
	.unlink = sffs_unlink, \
	.mkdir = sffs_mkdir, \
	.rmdir = sffs_rmdir, \
	.remove = sffs_remove, \
	.opendir = sffs_opendir, \
	.closedir = sffs_closedir, \
	.readdir_r = sffs_readdir_r, \
	.link = SYSFS_NOTSUP, \
	.symlink = SYSFS_NOTSUP, \
	.stat = sffs_stat, \
	.lstat = SYSFS_NOTSUP, \
	.fstat = sffs_fstat, \
	.chmod = SYSFS_NOTSUP, \
	.chown = SYSFS_NOTSUP, \
	.unlock = sffs_unlock, \
	.config = cfgp, \
	}


#endif /* SFFS_H_ */
