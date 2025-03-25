/**
 * @file build.h
 * @brief Build system for basec
 */

#ifndef BASEC_BUILD_H
#define BASEC_BUILD_H

#include "basec_types.h"

/**
 * @brief Target to build
 */
typedef struct {
    c_str  name;
    c_str* sources;
    u16    source_count;
    c_str  include_dir;
} BuildTarget;

/**
 * @brief Build system
 */
typedef struct {
    BuildTarget** targets;
    u16           target_count;
} BuildSystem;

/**
 * @brief Create a new build target
 * @param name The name of the target
 * @return A pointer to the new build target
 */
BuildTarget* build_target_create(const c_str name);

/**
 * @brief Add a source to the target
 * @param target The target to add the source to
 * @param source The source to add
 */
void build_target_add_source(BuildTarget* target, const c_str source);

/**
 * @brief Add an include directory to the target
 * @param target The target to add the include directory to
 * @param include_dir The include directory to add
 */
void build_target_add_include(BuildTarget* target, const c_str include_dir);

/**
 * @brief Destroy a build target
 * @param target The target to destroy
 */
void build_target_destroy(BuildTarget* target);

/**
 * @brief Create a new build system
 * @return A pointer to the new build system
 */
BuildSystem* build_system_create(void);

/**
 * @brief Add a target to the build system
 * @param build_system The build system to add the target to
 * @param target The target to add
 */
void build_system_add_target(BuildSystem* build_system, BuildTarget* target);

/**
 * @brief Build the project
 * @param build_system The build system to build
 */
void build_system_build(BuildSystem* build_system);

/**
 * @brief Destroy a build system
 * @param build_system The build system to destroy
 */
void build_system_destroy(BuildSystem* build_system);

#endif