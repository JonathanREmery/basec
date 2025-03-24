/**
 * @file build.h
 * @brief Build system for basec
 */

#ifndef BASEC_BUILD_H
#define BASEC_BUILD_H

/**
 * @brief Target to build
 */
typedef struct {
    const char*  name;
    const char** sources;
    const char*  include_dir;
} BuildTarget;

/**
 * @brief Build system
 */
typedef struct {
    BuildTarget* targets;
} BuildSystem;

/**
 * @brief Create a new build system
 * @return A pointer to the new build system
 */
BuildSystem* build_system_create(void);

/**
 * @brief Add a target to the build system
 * @param build_system The build system to add the target to
 * @param name The name of the target
 * @param sources The sources to compile
 * @param include_dir The include directory
 */
void build_system_add_target(BuildSystem* build_system, const char* name, const char** sources, const char* include_dir);

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