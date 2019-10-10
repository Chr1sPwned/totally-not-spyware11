//
//  amfi.h
//  Meridian
//
//  Created by Ben Sparkes on 19/12/2017.
//  Copyright © 2017 Ben Sparkes. All rights reserved.
//

#include <stdint.h>
#include "cs_blobs.h"

typedef struct {
    const char *name;
    uint64_t file_off;
    int fd;
    const void *addr;
    size_t size;
} img_info_t;

typedef char hash_t[20];
        
struct trust_chain {
    uint64_t next;
    unsigned char uuid[16];
    unsigned int count;
    hash_t hash[1];
};

int init_amfi(void);
int inject_trust(const char *path);

void *put_dick_in_macho(const char *path, uint64_t file_off);
const uint8_t *find_code_signature(img_info_t *info, uint32_t *cs_size);
int find_best_codedir(const void *csblob, uint32_t blob_size, const CS_CodeDirectory **chosen_cd);
unsigned int hash_rank(const CS_CodeDirectory *cd);
int hash_code_directory(const CS_CodeDirectory *directory, uint8_t hash[CS_CDHASH_LEN]);
const char *get_hash_name(uint8_t hash_type);
int open_img(img_info_t* info);
void close_img(img_info_t* info);


// Not fully sure if any of ther other things in here is needed for supports ios 11, I'll check out later.
#ifndef apfs_util_h
#define apfs_util_h

#define get_dirfd(vol) open(vol, O_RDONLY, 0)

const char *find_snapshot_with_ref(const char *vol, const char *ref);
const char *find_system_snapshot(const char *rootfsmnt);

int do_create(const char *vol, const char *snap);
int do_delete(const char *vol, const char *snap);
int do_revert(const char *vol, const char *snap);
int do_rename(const char *vol, const char *snap, const char *nw);
int do_mount(const char *vol, const char *snap, const char *mntpnt);
int list_snapshots(const char *vol);
int check_snapshot(const char *vol, const char *snap);
char *copyBootHash(void);

#endif /* apfs_util_h */
