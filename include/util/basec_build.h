/**
 * @file build.h
 * @brief Build system for basec
 */

#ifndef BASEC_BUILD_H
#define BASEC_BUILD_H

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <linux/limits.h>

#include "basec_types.h"
#include "ds/basec_string.h"

/**
 * @brief A build target
 * 
 * @param name The name of the target
 * @param cc The compiler to use
 * @param cflags The compiler flags
 * @param debug_flag The debug flag
 * @param bin_flag The binary flag
 * @param bin The path to the binary file
 * @param source_flag The source flag
 * @param source_count The number of sources
 * @param sources The sources of the target
 * @param include_flag The include flag
 * @param include_count The number of includes
 * @param includes The includes of the target
 * @param rebuild Whether to rebuild the target
 * @param debug Whether to enable debug mode
 */
typedef struct {
    c_str name;
    c_str cc;
    c_str cflags; 
    c_str debug_flag;
    c_str bin_flag;
    c_str bin;
    c_str source_flag;
    u16   source_count;
    c_str sources[U16_MAX];
    c_str include_flag;
    u16   include_count;
    c_str includes[U16_MAX];
    bool  rebuild;
    bool  debug;
} BuildTarget;

/**
 * @brief A build system
 * 
 * @param target_count The number of targets
 * @param targets The targets of the build system
 */
typedef struct {
    u16          target_count;
    BuildTarget* targets[U16_MAX];
} BuildSystem;

/**
 * @brief The result of a build operation
 * 
 * @param BASEC_BUILD_SUCCESS The build operation was successful
 * @param BASEC_BUILD_FAILURE The build operation failed
 */
typedef enum {
    BASEC_BUILD_SUCCESS,
    BASEC_BUILD_NULL_POINTER,
    BASEC_BUILD_ALLOCATION_FAILURE,
    BASEC_BUILD_MAX_TARGETS_FAILURE,
    BASEC_BUILD_MAX_SOURCES_FAILURE,
    BASEC_BUILD_MAX_INCLUDES_FAILURE,
    BASEC_BUILD_STRING_FAILURE,
    BASEC_BUILD_MEMOP_FAILURE,
    BASEC_BUILD_PROC_FAILURE,
    BASEC_BUILD_COMPILE_FAILURE,
} BasecBuildResult;

/**
 * @brief Handle the result of a build operation
 * 
 * @param result The result to handle
 */
void basec_build_handle_result(BasecBuildResult result);

/**
 * @brief Create a new build system
 * 
 * @param build_system The build system to create
 * @return The result of the build operation
 */
BasecBuildResult basec_build_system_create(BuildSystem** build_system);

/**
 * @brief Add a target to the build system
 * 
 * @param build_system The build system to add the target to
 * @param target The target to add
 * @return The result of the add operation
 */
BasecBuildResult basec_build_system_add_target(BuildSystem* build_system, BuildTarget target);

/**
 * @brief Build the targets in the build system
 * 
 * @param build_system The build system to build the targets of
 * @return The result of the build operation
 */
BasecBuildResult basec_build_system_build(BuildSystem* build_system);

/**
 * @brief Destroy a build system
 * 
 * @param build_system The build system to destroy
 * @return The result of the destroy operation
 */
BasecBuildResult basec_build_system_destroy(BuildSystem** build_system);

#endif