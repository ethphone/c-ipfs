/***
 * handles a repo on the file system
 */
#ifndef fs_repo_h
#define fs_repo_h

#include <stdio.h>
#include "ipfs/repo/config/config.h"


/**
 * a structure to hold the repo info
 */
struct FSRepo {
	int closed;
	char* path;
	struct IOCloser* lock_file;
	struct RepoConfig* config;
};

/**
 * opens a fsrepo
 * @param repo the repo struct. Should contain the path. This method will do the rest
 * @return 0 if there was a problem, otherwise 1
 */
int ipfs_repo_fsrepo_open(struct FSRepo* repo);

/***
 * checks to see if the repo is initialized
 * @param repo_path the path to the repo
 * @returns true(1) if it is initialized, otherwise false(0)
 */
int fs_repo_is_initialized(char* repo_path);

/**
 * write the config file to disk
 * @param path the path to the file
 * @param config the config structure
 * @returns true(1) on success
 */
int fs_repo_write_config_file(char* path, struct RepoConfig* config);

/**
 * constructs the FSRepo struct.
 * Remember: ipfs_repo_fsrepo_free must be called
 * @param repo_path the path to the repo
 * @param config the optional config file. NOTE: if passed, fsrepo_free will free resources of the RepoConfig.
 * @param repo the struct to allocate memory for
 * @returns false(0) if something bad happened, otherwise true(1)
 */
int ipfs_repo_fsrepo_new(const char* repo_path, struct RepoConfig* config, struct FSRepo** fs_repo);

/***
 * Free all resources used by this struct
 * @param repo the repo to clean up
 * @returns true(1) on success
 */
int ipfs_repo_fsrepo_free(struct FSRepo* config);

/***
 * Initialize a new repo with the specified configuration
 * @param config the information in order to build the repo
 * @returns true(1) on success
 */
int ipfs_repo_fsrepo_init(struct FSRepo* config);

/***
 * Write a block to the datastore and blockstore
 * @param block the block to write
 * @param fs_repo the repo to write to
 * @returns true(1) on success
 */
int ipfs_repo_fsrepo_block_write(struct Block* block, const struct FSRepo* fs_repo);
int ipfs_repo_fsrepo_block_read(const unsigned char* hash, size_t hash_length, struct Block** block, const struct FSRepo* fs_repo);

#endif /* fs_repo_h */
