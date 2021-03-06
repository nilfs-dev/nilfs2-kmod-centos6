/*
 * kern_feature.h - Kernel dependent features
 *
 * Licensed under GPLv2: the complete text of the GNU General Public
 * License can be found in COPYING file of the nilfs-kmod package.
 *
 * Copyright (C) 2006-2011 Nippon Telegraph and Telephone Corporation.
 */

#ifndef NILFS_KERN_FEATURE_H
#define NILFS_KERN_FEATURE_H

#include <linux/version.h>

/*
 * Please define as 0/1 here if you want to override
 */

/*
 * for Red Hat Enterprise Linux 6.x (and clones like CentOS or SL)
 */
#if defined(RHEL_MAJOR) && (RHEL_MAJOR == 6)
# if (RHEL_MINOR > 0)
#  define	HAVE_BH_ORDERED		0
#  define	HAVE_BIO_BARRIER	0
#  define	HAVE_FITRIM_IOCTL	1
#  define	HAVE_DISCARD_GRANULARITY	1
#  define	HAVE_BLOCK_PAGE_MKWRITE_RETURN	1
#  define	HAVE_ROUNDDOWN		1
# endif
# if (RHEL_MINOR > 3)
#  define	HAVE_NEW_SB_FREEZE	1
#  define	HAVE_NEW_SB_FREEZE_FLAG	1
# endif
#endif

/*
 * defaults
 */
#ifndef HAVE_NEW_SB_FREEZE_FLAG
# define HAVE_NEW_SB_FREEZE_FLAG	0
#endif
#ifndef HAVE_INODE_SET_FLAGS
# define HAVE_INODE_SET_FLAGS		0
#endif
#ifndef HAVE_SET_MASK_BITS
# define HAVE_SET_MASK_BITS		0
#endif

/*
 * defaults dependent to kernel versions
 */
#ifdef LINUX_VERSION_CODE
/*
 * linux-2.6.37 and later kernels have rounddown macro.
 */
#ifndef HAVE_ROUNDDOWN
# define HAVE_ROUNDDOWN \
	(LINUX_VERSION_CODE > KERNEL_VERSION(2, 6, 36))
#endif
/*
 * linux-2.6.37 and later kernels have FITRIM ioctl.
 */
#ifndef HAVE_FITRIM_IOCTL
# define HAVE_FITRIM_IOCTL \
	(LINUX_VERSION_CODE > KERNEL_VERSION(2, 6, 36))
#endif
/*
 * linux-3.6 and later kernels use new file system freezing mechanism
 * with routines sb_start_pagefault/sb_end_pagefault,
 * sb_start_intwrite/sb_end_intwrite, and
 * sb_start_write()/sb_end_write().  These are used to provide proper
 * freeze protection.
 */
#ifndef HAVE_NEW_SB_FREEZE
# define HAVE_NEW_SB_FREEZE \
	(LINUX_VERSION_CODE > KERNEL_VERSION(3, 5, 0))
#endif
/*
 * linux-3.0 and later kernels use block_page_mkwrite_return()
 * and __block_page_mkwrite().
 */
#ifndef HAVE_BLOCK_PAGE_MKWRITE_RETURN
# define HAVE_BLOCK_PAGE_MKWRITE_RETURN \
	(LINUX_VERSION_CODE > KERNEL_VERSION(2, 6, 39))
#endif
/*
 * barrier bio was deprecated at linux-2.6.37.
 * Newer kernels use FLUSH/FUA instead.
 */
#ifndef HAVE_BIO_BARRIER
# define HAVE_BIO_BARRIER \
	(LINUX_VERSION_CODE < KERNEL_VERSION(2, 6, 37))
#endif
/*
 * Ordered flag of buffer head was deprecated at linux-2.6.36.
 */
#ifndef HAVE_BH_ORDERED
# define HAVE_BH_ORDERED \
	(LINUX_VERSION_CODE < KERNEL_VERSION(2, 6, 36))
#endif
/*
 * Linux-2.6.36 and later kernels support atomic64_t type for all
 * platforms.  Earlier kernels may need some glue code to keep
 * backward compatibility.
 */
#ifndef HAVE_ATOMIC64_T
# define HAVE_ATOMIC64_T \
	(LINUX_VERSION_CODE > KERNEL_VERSION(2, 6, 35))
#endif
/*
 * BLKDEV_IFL_SECURE flag was introduced in kernel 2.6.36 and replaced
 * with BLKDEV_DISCARD_SECURE in kernel 2.6.37.
 */
#ifndef HAVE_BLKDEV_IFL_SECURE
# define HAVE_BLKDEV_IFL_SECURE \
	(LINUX_VERSION_CODE > KERNEL_VERSION(2, 6, 35) && \
	 LINUX_VERSION_CODE < KERNEL_VERSION(2, 6, 37))
#endif
/*
 * dentry argument was removed from fop->fsync() in kernel 2.6.35.
 */
#ifndef HAVE_DENTRY_ARG_IN_FSYNC
# define HAVE_DENTRY_ARG_IN_FSYNC \
	(LINUX_VERSION_CODE < KERNEL_VERSION(2, 6, 35))
#endif
/*
 * linux-2.6.35 and the later kernels have inode_init_owner().
 */
#ifndef HAVE_INODE_INIT_OWNER
# define HAVE_INODE_INIT_OWNER \
	(LINUX_VERSION_CODE > KERNEL_VERSION(2, 6, 34))
#endif
/*
 * blkdev_issue_flush() function has a gfp flag argument since
 * kernel 2.6.35.
 */
#ifndef HAVE_GFP_ARG_IN_BLKDEV_ISSUE_FLUSH
# define HAVE_GFP_ARG_IN_BLKDEV_ISSUE_FLUSH \
	(LINUX_VERSION_CODE > KERNEL_VERSION(2, 6, 34))
#endif
/*
 * Both BLKDEV_IFL_WAIT flag and BLKDEV_IFL_BARRIER flag were
 * introduced in kernel 2.6.35 and removed in kernel 2.6.37.
 */
#ifndef HAVE_BLKDEV_IFL_WAIT
# define HAVE_BLKDEV_IFL_WAIT \
	(LINUX_VERSION_CODE > KERNEL_VERSION(2, 6, 34) && \
	 LINUX_VERSION_CODE < KERNEL_VERSION(2, 6, 37))
# define HAVE_BLKDEV_IFL_BARRIER HAVE_BLKDEV_IFL_WAIT
#endif
/*
 * The queue_limits struct in linux-2.6.33 and later kernels has
 * discard_granularity parameter.
 */
#ifndef HAVE_DISCARD_GRANULARITY
# define HAVE_DISCARD_GRANULARITY \
	(LINUX_VERSION_CODE > KERNEL_VERSION(2, 6, 32))
#endif
/*
 * DISCARD_FL_BARRIER flag was introduced in kernel 2.6.32 and
 * replaced with two flags BLKDEV_IFL_BARRIER and BLKDEV_IFL_WAIT in
 * kernel 2.6.35.
 */
#ifndef HAVE_DISCARD_FL_BARRIER
# define HAVE_DISCARD_FL_BARRIER \
	(LINUX_VERSION_CODE > KERNEL_VERSION(2, 6, 31) && \
	 LINUX_VERSION_CODE < KERNEL_VERSION(2, 6, 35))
#endif
/*
 * blkdev_issue_discard() function has a flag argument since
 * 2.6.32.
 */
#ifndef HAVE_FLAG_ARG_IN_BLKDEV_ISSUE_DISCARD
# define HAVE_FLAG_ARG_IN_BLKDEV_ISSUE_DISCARD \
	(LINUX_VERSION_CODE > KERNEL_VERSION(2, 6, 31))
#endif
#endif /* LINUX_VERSION_CODE */


#include <linux/sched.h>	/* current_fsuid() and current_fsgid() */
#include <linux/fs.h>
#include <linux/buffer_head.h>
#include <linux/blkdev.h>

/*
 * definitions dependent to above macros
 */
#if !HAVE_INODE_SET_FLAGS
static inline void inode_set_flags(struct inode *inode, unsigned int flags,
				   unsigned int mask)
{
	unsigned int old_flags, new_flags;

	WARN_ON_ONCE(flags & ~mask);
	do {
		old_flags = ACCESS_ONCE(inode->i_flags);
		new_flags = (old_flags & ~mask) | flags;
	} while (unlikely(cmpxchg(&inode->i_flags, old_flags,
				  new_flags) != old_flags));
}
#endif

#if !HAVE_SET_MASK_BITS
#define set_mask_bits(ptr, _mask, _bits)	\
({								\
	const typeof(*ptr) mask = (_mask), bits = (_bits);	\
	typeof(*ptr) old, new;					\
								\
	do {							\
		old = ACCESS_ONCE(*ptr);			\
		new = (old & ~mask) | bits;			\
	} while (cmpxchg(ptr, old, new) != old);		\
								\
	new;							\
})
#endif

#if !HAVE_NEW_SB_FREEZE
#define sb_start_pagefault(sb)  do { } while (0)
#define sb_end_pagefault(sb)  do { } while (0)
#define sb_start_intwrite(sb) \
	do { vfs_check_frozen(sb, SB_FREEZE_WRITE); } while (0)
#define sb_end_intwrite(sb)  do { } while (0)
#else
#undef vfs_check_frozen
#define vfs_check_frozen(sb, level)  do { } while (0)
#endif

#if !HAVE_NEW_SB_FREEZE_FLAG
#define FS_HAS_NEW_FREEZE	0
#endif

#if !HAVE_BLOCK_PAGE_MKWRITE_RETURN
#ifndef VM_FAULT_RETRY
#define VM_FAULT_RETRY	0x0400	/* ->fault blocked, must retry */
#endif
static inline int block_page_mkwrite_return(int err)
{
	if (err == 0)
		return VM_FAULT_LOCKED;
	if (err == -EFAULT)
		return VM_FAULT_NOPAGE;
	if (err == -ENOMEM)
		return VM_FAULT_OOM;
	if (err == -EAGAIN)
		return VM_FAULT_RETRY;
	/* -ENOSPC, -EDQUOT, -EIO ... */
	return VM_FAULT_SIGBUS;
}

static inline int __block_page_mkwrite(struct vm_area_struct *vma,
				       struct vm_fault *vmf,
				       get_block_t get_block)
{
	int ret;

	ret = block_page_mkwrite(vma, vmf, get_block);
	return ret != VM_FAULT_LOCKED ? ret : 0;
}
#endif

#if !HAVE_INODE_INIT_OWNER
static inline void
inode_init_owner(struct inode *inode, const struct inode *dir, mode_t mode)
{
	inode->i_uid = current_fsuid();
	if (dir && dir->i_mode & S_ISGID) {
		inode->i_gid = dir->i_gid;
		if (S_ISDIR(mode))
			mode |= S_ISGID;
	} else
		inode->i_gid = current_fsgid();
	inode->i_mode = mode;
}
#endif

#if !HAVE_ATOMIC64_T
#ifndef ATOMIC64_INIT
typedef atomic_t atomic64_t;
#define atomic64_read(v)	atomic_read(v)
#define atomic64_set(v, i)	atomic_set(v, i)
#define atomic64_add(a, v)	atomic_add(a, v)
#define atomic64_sub(a, v)	atomic_sub(a, v)
#define atomic64_inc(v)		atomic_inc(v)
#define atomic64_dec(v)		atomic_dec(v)
#endif
#endif

enum {
	/*
	 * 64 bit checkpoint number, 64 bit inode number,
	 * 32 bit generation number.
	 */
	FILEID_NILFS_WITHOUT_PARENT = 0x61,

	/*
	 * 64 bit checkpoint number, 64 bit inode number,
	 * 32 bit generation number, 32 bit parent generation.
	 * 64 bit parent inode number.
	 */
	FILEID_NILFS_WITH_PARENT = 0x62,
};

#if !HAVE_FITRIM_IOCTL
struct fstrim_range {
	__u64 start;
	__u64 len;
	__u64 minlen;
};
#define FITRIM		_IOWR('X', 121, struct fstrim_range)	/* Trim */
#endif

#if !HAVE_ROUNDDOWN
#define rounddown(x, y) (				\
{							\
	typeof(x) __x = (x);				\
	__x - (__x % (y));				\
}							\
)
#endif

static inline int compat_blkdev_issue_flush(struct block_device *bdev,
					    gfp_t gfp, sector_t *error_sector)
{
#if HAVE_GFP_ARG_IN_BLKDEV_ISSUE_FLUSH
# if HAVE_BLKDEV_IFL_WAIT
	return blkdev_issue_flush(bdev, gfp, error_sector, BLKDEV_IFL_WAIT);
# else
	return blkdev_issue_flush(bdev, gfp, error_sector);
# endif
#else
	return blkdev_issue_flush(bdev, error_sector);
#endif
}

static inline int
compat_blkdev_issue_discard(struct block_device *bdev, sector_t sector,
			    sector_t nr_sects, gfp_t gfp, unsigned long flags)
{
#if HAVE_FLAG_ARG_IN_BLKDEV_ISSUE_DISCARD
# if HAVE_DISCARD_FL_BARRIER
#  if HAVE_BIO_BARRIER
	int compat_flags = DISCARD_FL_BARRIER;
#  else
	int compat_flags = 0;
#  endif
# elif HAVE_BLKDEV_IFL_BARRIER
	unsigned long compat_flags = BLKDEV_IFL_BARRIER | BLKDEV_IFL_WAIT;
#  if HAVE_BLKDEV_IFL_SECURE
	if (flags & 0x01) /* BLKDEV_DISCARD_SECURE */
		compat_flags |= BLKDEV_IFL_SECURE;
#  endif
# else /* neither HAVE_DISCARD_FL_BARRIER nor HAVE_BLKDEV_IFL_BARRIER */
	unsigned long compat_flags = flags;
# endif
	return blkdev_issue_discard(bdev, sector, nr_sects, gfp, compat_flags);
#else /* HAVE_FLAG_ARG_IN_BLKDEV_ISSUE_DISCARD */
	return blkdev_issue_discard(bdev, sector, nr_sects, gfp);
#endif /* HAVE_FLAG_ARG_IN_BLKDEV_ISSUE_DISCARD */
}

/*
 * The following patches are left unapplied during backporting later
 * patches:
 *
 * commit 7b6d91daee5cac6402186ff224c3af39d79f4a0e
 *   "block: unify flags for struct bio and struct request"
 * commit eafdc7d190a944c755a9fe68573c193e6e0217e7
 *   "sort out blockdev_direct_IO variants"
 * commit f4e420dc423148fba637af1ab618fa8896dfb2d6
 *   "clean up write_begin usage for directories in pagecache"
 * commit 6e1db88d536adcbbfe562b2d4b7d6425784fff12
 *   "introduce __block_write_begin"
 * commit 155130a4f7848b1aac439cab6bda1a175507c71c
 *   "get rid of block_write_begin_newtrunc"
 * commit 1025774ce411f2bd4b059ad7b53f0003569b74fa
 *   "remove inode_setattr"
 * commit a4ffdde6e56fdf8c34ddadc2674d6eb978083369
 *   "simplify checks for I_CLEAR/I_FREEING"
 * commit 6fd1e5c994c392ebdbe45600051b2a32ec4860f1
 *   "convert nilfs2 to ->evict_inode()"
 * commit 87e99511ea54510ffb60b98001d108794d5037f8
 *   "kill BH_Ordered flag"
 * commit 7de9c6ee3ecffd99e1628e81a5ea5468f7581a1f
 *   "new helper: ihold()"
 * commit f629d1c9bd0dbc44a6c4f9a4a67d1646c42bfc6f
 *   "mm: add account_page_writeback()"
 * commit e4c59d61e80529aebca4a3690b4378f2c6fc4e82
 *   "convert nilfs"
 * commit e525fd89d380c4a94c0d63913a1dd1a593ed25e7
 *   "block: make blkdev_get/put() handle exclusive access"
 * commit d4d77629953eabd3c14f6fa5746f6b28babfc55f
 *   "block: clean up blkdev_get() wrappers and their users"
 * commit fa0d7e3de6d6fc5004ad9dea0dd6b286af8f03e9
 *   "fs: icache RCU free inodes"
 * commit b74c79e99389cd79b31fcc08f82c24e492e63c7e
 *   "fs: provide rcu-walk aware permission i_ops"
 * commit b004a5eb0babec7ef91558f73315ef49e5a1f285
 *   "fs/nilfs2/super.c: Use printf extension %pV"
 * commit 2aa15890f3c191326678f1bd68af61ec6b8753ec
 *   "mm: prevent concurrent unmap_mapping_range() on the same inode"
 * commit 7eaceaccab5f40bbfda044629a6298616aeaed50
 *   "block: remove per-queue plugging"
 * commit 721a9602e6607417c6bc15b18e97a2f35266c690
 *   "block: kill off REQ_UNPLUG"
 * commit 4d3cf1bc557dc8b88e1cabf1980b3baa3380a641
 *   "nilfs2: move NILFS_SUPER_MAGIC to linux/magic.h"
 * commit a49ebbabb084d345991b72818a119616431416f2
 *   "nilfs2: use little-endian bitops"
 * commit 2e1496707560ecf98e9b0604622c0990f94861d3
 *   "userns: rename is_owner_or_cap to inode_owner_or_capable"
 * commit d611b22f1a5ddd0823e9d6a30bac91219f800e41
 *   "nilfs2: fix oops due to a bad aops initialization"
 * commit 7dcda1c96d7c643101d4a05579ef4512a4baa7ef
 *   "fs: export empty_aops"
 * commit eaae0f37d83bed7ccd0c6d0f52de1de44f92aecc
 *   "nilfs2: merge list_del()/list_add_tail() to list_move_tail()"
 * commit 293ce0ed8c2d22ff044e6e9fa7b1d4be425d189b
 *   "nilfs2: use empty_aops for gc-inodes"
 * commit 79bf7c732b5ff75b96022ed9d29181afd3d2509c
 *   "vfs: push dentry_unhash on rmdir into file systems"
 * commit e4eaac06bcccb2a70bca6a2de9871882dce2aa14
 *   "vfs: push dentry_unhash on rename_dir into file systems"
 * commit aa38572954ade525817fe88c54faebf85e5a61c0
 *   "fs: pass exact type of data dirties to ->dirty_inode"
 * commit a9049376ee05bf966bfe2b081b5071326856890a
 *   "make d_splice_alias(ERR_PTR(err), dentry) = ERR_PTR(err)"
 * commit dfb55de89879a1c32a70d0a510b3701ed9a6b855
 *   "nilfs2: remove unnecessary dentry_unhash from rmdir, dir rename"
 * commit 730e908f3539066d4aa01f4720ebfc750ce4d045
 *   "nilfs2_permission() doesn't need to bail out in RCU mode"
 */

#endif /* NILFS_KERN_FEATURE_H */
