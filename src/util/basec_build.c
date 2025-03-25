/**
 * @file build.c
 * @brief Build system for basec
 */

#include "util/basec_build.h"

#define BASEC_BUILD_BIN_DIR "bin"
#define BASEC_BUILD_COMPILE_COMMAND "gcc -Wall -Wextra -Werror -pedantic -o "
#define BASEC_BUILD_COMPILE_COMMAND_LENGTH 4096

static c_str _exe_path   = NULL;
static c_str _basec_path = NULL;

/**
 * @brief Get the path of the executable
 * 
 * @return The path of the executable
 */
static c_str _get_exe_path(void) {
    if (_exe_path != NULL) return _exe_path;

    c8 exe_path[PATH_MAX];
    if (readlink("/proc/self/exe", exe_path, PATH_MAX) == -1) return NULL;

    _exe_path = (c_str)malloc(strlen(exe_path) + 1);
    if (_exe_path == NULL) return NULL;

    strcpy(_exe_path, exe_path);
    return _exe_path;
}

/**
 * @brief Get the path of the basec directory
 * 
 * @return The path of the basec directory
 */
static c_str _get_basec_path(void) {
    if (_basec_path != NULL) return _basec_path;

    c_str exe_path = _get_exe_path();
    if (exe_path == NULL) return NULL;

    c_str bin_dir = strstr(exe_path, BASEC_BUILD_BIN_DIR);
    if (bin_dir == NULL) return NULL;

    u16 exe_path_len = strlen(exe_path);
    u16 bin_dir_len = strlen(bin_dir);

    _basec_path = (c_str)malloc(exe_path_len - bin_dir_len + 1);
    if (_basec_path == NULL) return NULL;

    (void)strncpy(_basec_path, exe_path, exe_path_len - bin_dir_len);
    _basec_path[exe_path_len - bin_dir_len] = '\0';

    return _basec_path;
}

/**
 * @brief Get the absolute path of a relative path
 * 
 * @param path The relative path to get the absolute path of
 * @return The absolute path of the relative path
 */
static c_str _absolute_path(c_str path) {
    if (path == NULL) return NULL;

    c_str basec_path = _get_basec_path();
    if (basec_path == NULL) return NULL;

    u16 path_len = strlen(path);
    u16 basec_path_len = strlen(basec_path);

    c_str absolute_path = (c_str)malloc(path_len + basec_path_len + 1);
    if (absolute_path == NULL) return NULL;

    (void)strncpy(absolute_path, basec_path, basec_path_len);
    (void)strncpy(absolute_path + basec_path_len, path, path_len);
    absolute_path[path_len + basec_path_len] = '\0';

    return absolute_path;
}

/**
 * @brief Check if a target needs to be rebuilt
 * 
 * @param target The target to check
 * @return True if the target needs to be rebuilt, false otherwise
 */
static bool _needs_rebuild(BuildTarget* target) {
    if (target == NULL) return false;

    struct stat bin_stat;
    if (stat(target->bin, &bin_stat) != 0) return true;

    for (u16 i = 0; i < target->source_count; i++) {
        struct stat source_stat;
        if (stat(target->sources[i], &source_stat) != 0) return true;
        if (source_stat.st_mtime > bin_stat.st_mtime) return true;
    }

    for (u16 i = 0; i < target->include_count; i++) {
        struct stat include_stat;
        if (stat(target->includes[i], &include_stat) != 0) return true;
        if (include_stat.st_mtime > bin_stat.st_mtime) return true;
    }

    return false;
}

/**
 * @brief Create a new build system
 * 
 * @param build_system The build system to create
 * @return The result of the create operation
 */
BasecBuildResult basec_build_system_create(BuildSystem** build_system) {
    if (build_system == NULL) return BASEC_BUILD_FAILURE;

    *build_system = (BuildSystem*)malloc(sizeof(BuildSystem));
    if (*build_system == NULL) return BASEC_BUILD_FAILURE;

    for (u16 i = 0; i < BASEC_BUILD_MAX_TARGETS; i++) {
        (*build_system)->targets[i] = NULL;
    }
    (*build_system)->target_count = 0;

    return BASEC_BUILD_SUCCESS;
}

/**
 * @brief Add a target to the build system
 * 
 * @param build_system The build system to add the target to
 * @param target The target to add
 * @return The result of the add operation
 */
BasecBuildResult basec_build_system_add_target(BuildSystem* build_system, BuildTarget target) {
    if (build_system == NULL) return BASEC_BUILD_FAILURE;
    if (build_system->target_count >= BASEC_BUILD_MAX_TARGETS) return BASEC_BUILD_FAILURE;
    if (target.name == NULL) return BASEC_BUILD_FAILURE;

    BuildTarget* new_target = (BuildTarget*)malloc(sizeof(BuildTarget));
    if (new_target == NULL) return BASEC_BUILD_FAILURE;

    new_target->name = target.name;

    c8 bin_path[PATH_MAX];
    (void)snprintf(
        bin_path,
        sizeof(bin_path),
        "%s/%s",
        BASEC_BUILD_BIN_DIR,
        target.name
    );
    new_target->bin = _absolute_path(bin_path);

    for (u16 i = 0; i < BASEC_BUILD_MAX_SOURCES; i++) {
        if (target.sources[i] == NULL) break;
        new_target->sources[i] = _absolute_path(target.sources[i]);
        new_target->source_count++;
    }

    for (u16 i = 0; i < BASEC_BUILD_MAX_INCLUDES; i++) {
        if (target.includes[i] == NULL) break;
        new_target->includes[i] = _absolute_path(target.includes[i]);
        new_target->include_count++;
    }

    build_system->targets[build_system->target_count++] = new_target;

    return BASEC_BUILD_SUCCESS;
}

/**
 * @brief Build the targets in the build system
 * 
 * @param build_system The build system to build the targets of
 * @return The result of the build operation
 */
BasecBuildResult basec_build_system_build(BuildSystem* build_system) {
    if (build_system == NULL) return BASEC_BUILD_FAILURE;

    for (u16 i = 0; i < build_system->target_count; i++) {
        BuildTarget* target = build_system->targets[i];
        if (!_needs_rebuild(target)) continue;

        c8 compile_command[BASEC_BUILD_COMPILE_COMMAND_LENGTH];

        // "gcc -Wall -Wextra -Werror -pedantic -o "
        (void)strncpy(
            compile_command,
            BASEC_BUILD_COMPILE_COMMAND,
            sizeof(compile_command)
        );

        // "{target_binary}"
        (void)strncat(
            compile_command,
            target->bin,
            strlen(target->bin)
        );

        // " "
        (void)strncat(compile_command, " ", 2);

        for (u16 j = 0; j < target->source_count; j++) {
            // "{target_source} "
            (void)strncat(
                compile_command,
                target->sources[j],
                strlen(target->sources[j])
            );
            (void)strncat(compile_command, " ", 2);
        }

        for (u16 j = 0; j < target->include_count; j++) {
            // "-I{target_include} "
            (void)strncat(
                compile_command,
                "-I",
                3
            );
            (void)strncat(
                compile_command,
                target->includes[j],
                strlen(target->includes[j])
            );
            (void)strncat(compile_command, " ", 2);
        }

        FILE* compile_proc = popen(compile_command, "r");
        if (compile_proc == NULL) {
            fprintf(stderr, "Failed to run command: %s\n", compile_command);
            return BASEC_BUILD_FAILURE;
        }

        char output_buffer[128];
        while (fgets(output_buffer, sizeof(output_buffer), compile_proc) != NULL);

        int return_code = pclose(compile_proc);
        if (return_code != 0) {
            fprintf(stderr, "%s", output_buffer);
            fprintf(
                stderr,
                "[Error][Build] Compilation failed with return code: %d\n",
                return_code
            );
            return BASEC_BUILD_FAILURE;
        }

        c_str self = _get_exe_path();
        if (strncmp(target->bin, self, strlen(self)) == 0) {
            execl(target->bin, target->bin, (char *)NULL);

            fprintf(stderr, "[Error][Build] Failed to execute process: %s\n", target->bin);
            return BASEC_BUILD_FAILURE;
        }
    }

    return BASEC_BUILD_SUCCESS;
}

/**
 * @brief Destroy a build system
 * 
 * @param build_system The build system to destroy
 * @return The result of the destroy operation
 */
BasecBuildResult basec_build_system_destroy(BuildSystem** build_system) {
    if (build_system == NULL || *build_system == NULL) return BASEC_BUILD_FAILURE;

    for (u16 i = 0; i < (*build_system)->target_count; i++) {
        free((*build_system)->targets[i]);
    }
    (*build_system)->target_count = 0;

    free(*build_system);
    *build_system = NULL;

    return BASEC_BUILD_SUCCESS;
}