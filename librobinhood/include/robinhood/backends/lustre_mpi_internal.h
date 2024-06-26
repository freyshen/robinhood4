/* This file is part of RobinHood 4
 *
 * Copyright (C) 2024 Commissariat a l'energie atomique et aux energies
 *                    alternatives
 *
 * SPDX-License-Identifer: LGPL-3.0-or-later
 */

#ifndef RBH_LUSTRE_MPI_H
#define RBH_LUSTRE_MPI_H

/**
 * @file
 *
 * Internal header which defines the mpi_iterator
 *
 */

#include "mfu.h"
#include "robinhood/iterator.h"
#include "robinhood/sstack.h"
#include "robinhood/value.h"
#include "robinhood/id.h"
#include "robinhood/statx.h"

#include "common.h"

/*----------------------------------------------------------------------------*
 |                                mpi_iterator                                |
 *----------------------------------------------------------------------------*/

struct mpi_iterator {
    struct rbh_mut_iterator iterator;
    inode_xattrs_callback_t inode_xattrs_callback;
    int statx_sync_type;
    size_t prefix_len;

    /**
     * Boolean to indicate if we want to skip errors while synchronizing two
     * backends
     */
    bool skip_error;

    /**
     * Boolean to indicate if we are synchronizing a branch
     */
    bool is_branch;

    /**
     * Index of current file in the flist in the process
     */
    uint64_t current;

    /**
     * Size of the flist in the process,
     * this is not the global size of the flist
     */
    uint64_t total;
    mfu_flist flist;
};

/*----------------------------------------------------------------------------*
 |                               mpi_file_info                                |
 *----------------------------------------------------------------------------*/

struct mpi_file_info {
    /**
     * File path from the root
     */
    const char *path;

    /**
     * File name
     */
    char *name;

    /**
     * rbh_id of parent entry
     */
    struct rbh_id *parent_id;
};

/*----------------------------------------------------------------------------*
 |                       lustre_mpi operations                                |
 *----------------------------------------------------------------------------*/

struct rbh_backend *
lustre_mpi_backend_branch(void *backend, const struct rbh_id *id,
                          const char *path);

#endif
