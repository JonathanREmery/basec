/**
 * @file build.c
 * @brief Build system for basec
 */

#include "util/basec_build.h"

#define _BASEC_BUILD_DEFAULT_CC           "gcc"
#define _BASEC_BUILD_DEFAULT_CFLAGS       "-Wall -Wextra -Werror -pedantic"
#define _BASEC_BUILD_DEFAULT_DEBUG_FLAG   "-g"
#define _BASEC_BUILD_DEFAULT_BIN_FLAG     "-o"
#define _BASEC_BUILD_DEFAULT_SOURCE_FLAG  ""
#define _BASEC_BUILD_DEFAULT_INCLUDE_FLAG "-I"

#define _BASEC_BUILD_COMPILE_COMMAND_LENGTH       4096
#define _BASEC_BUILD_COMPILE_OUTPUT_LINE_LENGTH   256
#define _BASEC_BUILD_COMPILE_OUTPUT_BUFFER_LENGTH 4096

static c_str _exe_path  = NULL;
static c_str _root_path = NULL;

/**
 * @brief Get the path of the executable
 * 
 * @return The path of the executable
 */
static c_str _get_exe_path(void) {
    if (_exe_path != NULL) return _exe_path;

    c8 exe_path[PATH_MAX] = {0};
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
static c_str _get_root_path(c_str bin_path) {
    if (_root_path != NULL) return _root_path;

    c_str exe_path     = NULL;
    c_str bin_path_abs = NULL;

    exe_path = _get_exe_path();
    if (exe_path == NULL) return NULL;

    bin_path_abs = strstr(exe_path, bin_path);
    if (bin_path_abs == NULL) return NULL;

    _root_path = (c_str)malloc((u64)bin_path_abs - (u64)exe_path + 1);
    if (_root_path == NULL) return NULL;

    (void)strncpy(_root_path, exe_path, (u64)bin_path_abs - (u64)exe_path);
    _root_path[(u64)bin_path_abs - (u64)exe_path] = '\0';

    return _root_path;
}

/**
 * @brief Get the absolute path of a relative path
 * 
 * @param path The relative path to get the absolute path of
 * @return The absolute path of the relative path
 */
static c_str _absolute_path(c_str path, c_str bin_path) {
    if (path == NULL) return NULL;

    c_str root_path     = NULL;
    u16   path_len      = 0;
    u16   root_path_len = 0;
    c_str absolute_path = NULL;

    root_path = _get_root_path(bin_path);
    if (root_path == NULL) return NULL;

    path_len = strlen(path);
    root_path_len = strlen(root_path);

    absolute_path = (c_str)malloc(path_len + root_path_len + 1);
    if (absolute_path == NULL) return NULL;

    (void)strncpy(absolute_path, root_path, root_path_len);
    (void)strncpy(absolute_path + root_path_len, path, path_len);
    absolute_path[path_len + root_path_len] = '\0';

    return absolute_path;
}

/**
 * @brief Check if a target needs to be built
 * 
 * @param target The target to check
 * @return True if the target needs to be built, false otherwise
 */
static bool _needs_build(BuildTarget* target) {
    if (target == NULL) return false;

    struct stat bin_stat     = {0};
    struct stat source_stat  = {0};
    struct stat include_stat = {0};

    if (stat(target->bin, &bin_stat) != 0) return true;

    for (u16 i = 0; i < target->source_count; i++) {
        if (stat(target->sources[i], &source_stat) != 0) return true;
        if (source_stat.st_mtime > bin_stat.st_mtime)    return true;
    }

    for (u16 i = 0; i < target->include_count; i++) {
        if (stat(target->includes[i], &include_stat) != 0) return true;
        if (include_stat.st_mtime > bin_stat.st_mtime)     return true;
    }

    return false;
}

/**
 * @brief Handle the result of a build operation
 * 
 * @param result The result to handle
 */
void basec_build_handle_result(BasecBuildResult result) {
    switch (result) {
        case BASEC_BUILD_SUCCESS:
            break;
        case BASEC_BUILD_NULL_POINTER:
            (void)printf(
                "[Error][Build] Encountered a null pointer during the build process\n"
            );
            exit(1);
        case BASEC_BUILD_ALLOCATION_FAILURE:
            (void)printf(
                "[Error][Build] Memory allocation failed while attempting to build\n"
            );
            exit(1);
        case BASEC_BUILD_MAX_TARGETS_FAILURE:
            (void)printf(
                "[Error][Build] Exceeded the maximum number of build targets allowed\n"
            );
            exit(1);
        case BASEC_BUILD_MAX_SOURCES_FAILURE:
            (void)printf(
                "[Error][Build] Exceeded the maximum number of source files allowed\n"
            );
            exit(1);
        case BASEC_BUILD_MAX_INCLUDES_FAILURE:
            (void)printf(
                "[Error][Build] Exceeded the maximum number of include files allowed\n"
            );
            exit(1);
        case BASEC_BUILD_STRING_FAILURE:
            (void)printf(
                "[Error][Build] String operation failed during the build process\n"
            );
            exit(1);
        case BASEC_BUILD_MEMOP_FAILURE:
            (void)printf(
                "[Error][Build] Memory operation failed during the build process\n"
            );
            exit(1);
        case BASEC_BUILD_PROC_FAILURE:
            (void)printf(
                "[Error][Build] A failure occurred during the build process execution\n"
            );
            exit(1);
        case BASEC_BUILD_COMPILE_FAILURE:
            (void)printf(
                "[Error][Build] Compilation failed during the build process\n"
            );
            exit(1);
        default:
            (void)printf(
                "[Error][Build] An unknown error occurred during the build process\n"
            );
            exit(1);
    }
}

/**
 * @brief Create a new build system
 * 
 * @param build_system The build system to create
 * @return The result of the create operation
 */
BasecBuildResult basec_build_system_create(BuildSystem** build_system) {
    if (build_system == NULL) return BASEC_BUILD_NULL_POINTER;

    *build_system = (BuildSystem*)malloc(sizeof(BuildSystem));
    if (*build_system == NULL) return BASEC_BUILD_ALLOCATION_FAILURE;

    (*build_system)->target_count = 0;
    for (u16 i = 0; i < U16_MAX; i++) {
        (*build_system)->targets[i] = NULL;
    }

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
    if (build_system == NULL) return BASEC_BUILD_NULL_POINTER;
    
    if (target.name         == NULL || target.bin         == NULL ||
        target.sources[0]   == NULL || target.includes[0] == NULL) {
        return BASEC_BUILD_NULL_POINTER;
    }

    if (build_system->target_count >= U16_MAX) {
        return BASEC_BUILD_MAX_TARGETS_FAILURE;
    }
    
    if (target.cc           == NULL) target.cc           = _BASEC_BUILD_DEFAULT_CC;
    if (target.cflags       == NULL) target.cflags       = _BASEC_BUILD_DEFAULT_CFLAGS;
    if (target.debug_flag   == NULL) target.debug_flag   = _BASEC_BUILD_DEFAULT_DEBUG_FLAG;
    if (target.bin_flag     == NULL) target.bin_flag     = _BASEC_BUILD_DEFAULT_BIN_FLAG;
    if (target.source_flag  == NULL) target.source_flag  = _BASEC_BUILD_DEFAULT_SOURCE_FLAG;
    if (target.include_flag == NULL) target.include_flag = _BASEC_BUILD_DEFAULT_INCLUDE_FLAG;

    BuildTarget* new_target = NULL;

    new_target = (BuildTarget*)malloc(sizeof(BuildTarget));
    if (new_target == NULL) return BASEC_BUILD_ALLOCATION_FAILURE;

    new_target->name        = target.name;
    new_target->cc          = target.cc;
    new_target->cflags      = target.cflags;
    new_target->debug_flag  = target.debug_flag;
    new_target->bin_flag    = target.bin_flag;
    new_target->bin         = _absolute_path(target.bin, target.bin);

    new_target->source_flag = target.source_flag;
    for (u16 i = 0; i < U16_MAX; i++) {
        if (target.sources[i] == NULL) break;
        new_target->sources[new_target->source_count++] = _absolute_path(
            target.sources[i],
            target.bin
        );

        if (new_target->source_count >= U16_MAX) {
            free(new_target);
            return BASEC_BUILD_MAX_SOURCES_FAILURE;
        }
    }
    
    new_target->include_flag = target.include_flag;
    for (u16 i = 0; i < U16_MAX; i++) {
        if (target.includes[i] == NULL) break;
        new_target->includes[new_target->include_count++] = _absolute_path(
            target.includes[i],
            target.bin
        );

        if (new_target->include_count >= U16_MAX) {
            free(new_target);
            return BASEC_BUILD_MAX_INCLUDES_FAILURE;
        }
    }

    new_target->rebuild = target.rebuild;
    new_target->debug   = target.debug;

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
    if (build_system == NULL) return BASEC_BUILD_NULL_POINTER;
    
    BuildTarget* target                                                   = NULL;
    FILE*        compile_proc                                             = NULL;
    c8           output_line[_BASEC_BUILD_COMPILE_OUTPUT_LINE_LENGTH]     = {0};
    c8           output_buffer[_BASEC_BUILD_COMPILE_OUTPUT_BUFFER_LENGTH] = {0};
    u8           cur_output_len                                           = 0;
    bool         has_error                                                = false;
    u8           return_code                                              = 0;
    c_str        self                                                     = NULL;

    for (u16 i = 0; i < build_system->target_count; i++) {
        BasecStringResult string_result   = BASEC_STRING_SUCCESS;
        BasecString*      compile_command = NULL;

        target = build_system->targets[i];
        if (!target->rebuild || !_needs_build(target)) continue;

        string_result = basec_string_create(
            &compile_command,
            "",
            _BASEC_BUILD_COMPILE_COMMAND_LENGTH
        );
        if (string_result != BASEC_STRING_SUCCESS) return BASEC_BUILD_STRING_FAILURE;

        // "{cc}"
        string_result = basec_string_append(
            compile_command,
            target->cc
        );
        if (string_result != BASEC_STRING_SUCCESS) return BASEC_BUILD_STRING_FAILURE;

        // " "
        string_result = basec_string_append(
            compile_command,
            " "
        );
        if (string_result != BASEC_STRING_SUCCESS) return BASEC_BUILD_STRING_FAILURE;
        
        // "{cflags}"
        string_result = basec_string_append(
            compile_command,
            target->cflags
        );
        if (string_result != BASEC_STRING_SUCCESS) return BASEC_BUILD_STRING_FAILURE;
        
        // " "
        string_result = basec_string_append(
            compile_command,
            " "
        );
        if (string_result != BASEC_STRING_SUCCESS) return BASEC_BUILD_STRING_FAILURE;
        
        if (target->debug) {
            // "{debug_flag}"
            string_result = basec_string_append(
                compile_command,
                target->debug_flag
            );
            if (string_result != BASEC_STRING_SUCCESS) return BASEC_BUILD_STRING_FAILURE;
        
            // " "
            string_result = basec_string_append(
                compile_command,
                " "
            );
            if (string_result != BASEC_STRING_SUCCESS) return BASEC_BUILD_STRING_FAILURE;
        }
        
        // "{bin_flag}"
        string_result = basec_string_append(
            compile_command,
            target->bin_flag
        );
        if (string_result != BASEC_STRING_SUCCESS) return BASEC_BUILD_STRING_FAILURE;
        
        // "{bin}"
        string_result = basec_string_append(
            compile_command,
            target->bin
        );
        if (string_result != BASEC_STRING_SUCCESS) return BASEC_BUILD_STRING_FAILURE;

        // " "
        string_result = basec_string_append(
            compile_command,
            " "
        );
        if (string_result != BASEC_STRING_SUCCESS) return BASEC_BUILD_STRING_FAILURE;
        
        // "{source_flag}"
        string_result = basec_string_append(
            compile_command,
            target->source_flag
        );
        if (string_result != BASEC_STRING_SUCCESS) return BASEC_BUILD_STRING_FAILURE;

        // " "
        string_result = basec_string_append(
            compile_command,
            " "
        );
        if (string_result != BASEC_STRING_SUCCESS) return BASEC_BUILD_STRING_FAILURE;

        for (u16 j = 0; j < target->source_count; j++) {
            // "{target_source} "
            string_result = basec_string_append(
                compile_command,
                target->sources[j]
            );
            if (string_result != BASEC_STRING_SUCCESS) return BASEC_BUILD_STRING_FAILURE;
 
            // " "
            string_result = basec_string_append(
                compile_command,
                " "
            );
            if (string_result != BASEC_STRING_SUCCESS) return BASEC_BUILD_STRING_FAILURE;
        }

        // "{include_flag}"
        string_result = basec_string_append(
            compile_command,
            target->include_flag
        );
        if (string_result != BASEC_STRING_SUCCESS) return BASEC_BUILD_STRING_FAILURE;

        // " "
        string_result = basec_string_append(
            compile_command,
            " "
        );
        if (string_result != BASEC_STRING_SUCCESS) return BASEC_BUILD_STRING_FAILURE;

        for (u16 j = 0; j < target->include_count; j++) {
            // "{include} "
            string_result = basec_string_append(
                compile_command,
                target->includes[j]
            );
            if (string_result != BASEC_STRING_SUCCESS) return BASEC_BUILD_STRING_FAILURE;

            // " "
            string_result = basec_string_append(
                compile_command,
                " "
            );
            if (string_result != BASEC_STRING_SUCCESS) return BASEC_BUILD_STRING_FAILURE;
        }

        // Redirect stderr to stdout
        string_result = basec_string_append(
            compile_command,
            "2>&1"
        );
        if (string_result != BASEC_STRING_SUCCESS) return BASEC_BUILD_STRING_FAILURE;

        compile_proc = popen(compile_command->data, "r");
        if (compile_proc == NULL) {
            (void)printf("[Error][Build] Failed to open compilation process\n");
            return BASEC_BUILD_PROC_FAILURE;
        }

        while (fgets(output_line, sizeof(output_line), compile_proc) != NULL) {
            if (strstr(output_line, "error") != NULL) {
                has_error = true;
            }

            size_t line_len = strlen(output_line);
            if (cur_output_len + line_len < _BASEC_BUILD_COMPILE_OUTPUT_BUFFER_LENGTH) {
                strncat(output_buffer, output_line, line_len);
                cur_output_len += line_len;
            }
        }

        return_code = pclose(compile_proc);
        if (return_code != 0 || has_error) {
            (void)printf(
                "[Error][Build]"
                "Compilation failed for target '%s'\n\n",
                target->name
            );
            (void)printf("%s", output_buffer);
            exit(1);
        }

        self = _get_exe_path();
        if (self != NULL && target->bin != NULL) {
            if (strncmp(target->bin, self, strlen(self)) == 0) {
                char* argv[2];

                argv[0] = (char*)target->name;
                argv[1] = NULL;

                execv(target->bin, argv);

                (void)printf("[Error][Build] Failed to execute the newly compiled binary");
                return BASEC_BUILD_PROC_FAILURE;
            }
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
    if (build_system == NULL || *build_system == NULL) return BASEC_BUILD_NULL_POINTER;

    for (u16 i = 0; i < (*build_system)->target_count; i++) {
        free((*build_system)->targets[i]);
    }
    (*build_system)->target_count = 0;

    free(*build_system);
    *build_system = NULL;

    return BASEC_BUILD_SUCCESS;
}