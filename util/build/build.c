/**
 * @file build.c
 * @brief Build system for basec
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <linux/limits.h>

#include "build.h"

static const char* _BUILD_SOURCE  = "/util/build/build.c";
static const char* _BUILD_INCLUDE = "/util/build";
static const char* _BUILD_BINARY  = "/bin/build";
static const char* _CC            = "gcc";
static const char* _CFLAGS        = "-Wall -Wextra -Werror -pedantic";
static const int   _MAX_TARGETS   = 1024;
static const int   _MAX_SOURCES   = 1024;

static char basec_path[PATH_MAX];
static char compile_command[1024];

static char* _get_basec_path(void) {
    if (basec_path[0] != '\0') return basec_path;

    char exe_path[PATH_MAX];
    if (readlink("/proc/self/exe", exe_path, PATH_MAX) == -1) {
        (void)printf("[Error] Failed to get the executable path\n");
        exit(1);
    }

    (void)strncpy(basec_path, exe_path, strlen(exe_path) - strlen("/bin/build"));
    return basec_path;
}

/**
 * @brief Check if the build system needs to be rebuilt
 * @return If needs to be rebuilt true, otherwise false
 */
static bool _need_rebuild(void) {
    const char* basec_path = _get_basec_path();

    char exe_path[PATH_MAX];
    (void)strncpy(exe_path, basec_path, PATH_MAX);
    (void)strncat(exe_path, _BUILD_BINARY, PATH_MAX - strlen(exe_path));

    char source_path[PATH_MAX];
    (void)strncpy(source_path, basec_path, strlen(basec_path));
    (void)strncat(source_path, _BUILD_SOURCE, PATH_MAX - strlen(source_path));

    struct stat build_stat, source_stat;
    if (stat(source_path, &source_stat) == -1) {
        (void)printf("[Error] %s does not exist\n", _BUILD_SOURCE);
        exit(1);
    }

    if (stat(exe_path, &build_stat) == -1) return true;
    return source_stat.st_mtime > build_stat.st_mtime;
}

/**
 * @brief Rebuild the build system
 */
static void _rebuild(void) {
    const char* basec_path = _get_basec_path();

    // gcc -Wall -Wextra -Werror -pedantic -o {basec_path}/bin/build {basec_path}/util/build/build.c -I{basec_path}/util/build
    compile_command[0] = '\0';
    (void)strncat(compile_command, _CC, sizeof(compile_command) - strlen(_CC));
    (void)strncat(compile_command, " ", sizeof(compile_command) - strlen(" "));
    (void)strncat(compile_command, _CFLAGS, sizeof(compile_command) - strlen(_CFLAGS));
    (void)strncat(compile_command, " -o ", sizeof(compile_command) - strlen(" -o "));
    (void)strncat(compile_command, basec_path, sizeof(compile_command) - strlen(basec_path));
    (void)strncat(compile_command, _BUILD_BINARY, sizeof(compile_command) - strlen(_BUILD_BINARY));
    (void)strncat(compile_command, " ", sizeof(compile_command) - strlen(" "));
    (void)strncat(compile_command, basec_path, sizeof(compile_command) - strlen(basec_path));
    (void)strncat(compile_command, _BUILD_SOURCE, sizeof(compile_command) - strlen(_BUILD_SOURCE));
    (void)strncat(compile_command, " -I", sizeof(compile_command) - strlen(" -I"));
    (void)strncat(compile_command, basec_path, sizeof(compile_command) - strlen(basec_path));
    (void)strncat(compile_command, _BUILD_INCLUDE, sizeof(compile_command) - strlen(_BUILD_INCLUDE));

    FILE* fp = popen(compile_command, "r");
    if (fp == NULL) {
        (void)printf("[Error] Unable to initiate the compilation process for the build system\n");
        exit(1);
    }

    char buffer[1024];
    (void)fgets(buffer, sizeof(buffer), fp);

    if (pclose(fp) != 0) {
        (void)printf("%s", buffer);
        (void)printf("[Error] Compilation failed with the above output\n");
        exit(1);
    }

    char exe_path[PATH_MAX];
    (void)strncpy(exe_path, basec_path, PATH_MAX);
    (void)strncat(exe_path, _BUILD_BINARY, PATH_MAX - strlen(_BUILD_BINARY));

    char* args[] = {exe_path, NULL};
    (void)execve(exe_path, args, __environ);
    
    (void)printf("[Error] Execution of the newly compiled build binary failed\n");
    exit(1);
}

/**
 * @brief Create a new build target
 * @param name The name of the target
 * @return A pointer to the newly created build target
 */
BuildTarget* build_target_create(const char* name) {
    BuildTarget* target = malloc(sizeof(BuildTarget));
    if (target == NULL) {
        (void)printf("[Error] Memory allocation for the build target failed\n");
        exit(1);
    }

    target->name = name;

    target->sources = malloc(sizeof(char*) * _MAX_SOURCES);
    if (target->sources == NULL) {
        (void)printf("[Error] Memory allocation for the build target sources failed\n");
        exit(1);
    }
    target->source_count = 0;

    target->include_dir = NULL;

    return target;
}

/**
 * @brief Add a source to the target
 * @param target The target to add the source to
 * @param source The source to add
 */
void build_target_add_source(BuildTarget* target, const char* source) {
    if (target == NULL || source == NULL) return;
    target->sources[target->source_count++] = source;
}

/**
 * @brief Add an include directory to the target
 * @param target The target to add the include directory to
 * @param include_dir The include directory to add
 */
void build_target_add_include(BuildTarget* target, const char* include_dir) {
    if (target == NULL || include_dir == NULL) return;
    target->include_dir = include_dir;
}

/**
 * @brief Destroy a build target
 * @param target The target to destroy
 */
void build_target_destroy(BuildTarget* target) {
    if (target == NULL) return;

    free(target->sources);
    free(target);
    target = NULL;
}

/**
 * @brief Create a new build system
 * @return A pointer to the newly created build system
 */
BuildSystem* build_system_create(void) {
    BuildSystem* build_system = malloc(sizeof(BuildSystem));
    if (build_system == NULL) {
        (void)printf("[Error] Memory allocation for the build system failed\n");
        exit(1);
    }

    build_system->targets = malloc(sizeof(BuildTarget*) * _MAX_TARGETS);
    if (build_system->targets == NULL) {
        (void)printf("[Error] Memory allocation for build targets failed\n");
        exit(1);
    }
    build_system->target_count = 0;

    return build_system;
}

/**
 * @brief Add a target to the build system
 * @param build_system The build system to add the target to
 * @param target The target to add
 */
void build_system_add_target(BuildSystem* build_system, BuildTarget* target) {
    if (build_system == NULL || target == NULL) return;

    if (build_system->target_count >= _MAX_TARGETS) {
        (void)printf("[Error] Maximum number of targets (%d) has been reached\n", _MAX_TARGETS);
        exit(1);
    }

    build_system->targets[build_system->target_count++] = target;
}

/**
 * @brief Build the project
 */
void build_system_build(BuildSystem* build_system) {
    if (build_system == NULL) return;

    if (_need_rebuild()) {
        (void)printf("[Info] Rebuilding build system...\n");
        _rebuild();
    }

    (void)printf("[Info] Building project...\n");

    const char* basec_path = _get_basec_path();
    for (int i = 0; i < build_system->target_count; i++) {
        if (build_system->targets[i] == NULL) break;
        
        (void)printf("[Info] Building target: %s\n", build_system->targets[i]->name);
        
        char bin_path[PATH_MAX];
        (void)strncpy(bin_path, basec_path, PATH_MAX);
        (void)strncat(bin_path, "/bin/", PATH_MAX - strlen(bin_path));
        (void)strncat(bin_path, build_system->targets[i]->name, PATH_MAX - strlen(bin_path));

        compile_command[0] = '\0';
        (void)strncpy(compile_command, _CC, sizeof(compile_command));
        (void)strncat(compile_command, " ", sizeof(compile_command) - 1);
        (void)strncat(compile_command, _CFLAGS, sizeof(compile_command) - strlen(_CFLAGS));
        (void)strncat(compile_command, " -o ", sizeof(compile_command) - 5);
        (void)strncat(compile_command, bin_path, sizeof(compile_command) - strlen(bin_path));
        (void)strncat(compile_command, " ", sizeof(compile_command) - 1);

        for (int j = 0; j < build_system->targets[i]->source_count; j++) {
            char source_path[PATH_MAX];
            (void)strncpy(source_path, basec_path, PATH_MAX);
            (void)strncat(source_path, "/", PATH_MAX - 1);
            (void)strncat(source_path, build_system->targets[i]->sources[j], PATH_MAX - strlen(source_path));

            (void)strncat(
                compile_command,
                source_path,
                sizeof(compile_command) - strlen(source_path)
            );
            (void)strncat(
                compile_command,
                " ",
                sizeof(compile_command) - 1
            );
        }

        if (build_system->targets[i]->include_dir != NULL) {
            char include_dir[PATH_MAX];
            (void)strncpy(include_dir, basec_path, PATH_MAX);
            (void)strncat(include_dir, "/", PATH_MAX - 1);
            (void)strncat(include_dir, build_system->targets[i]->include_dir, PATH_MAX - strlen(build_system->targets[i]->include_dir));

            (void)strncat(compile_command, "-I", sizeof(compile_command) - 2);
            (void)strncat(compile_command, include_dir, sizeof(compile_command) - strlen(include_dir));
        }

        (void)printf("[Info] Running: %s\n", compile_command);
        if (system(compile_command) != 0) {
            (void)printf("[Error] Build process failed for target %s\n", build_system->targets[i]->name);
            exit(1);
        }
    }

    (void)printf("[Info] Build process completed successfully\n");
}

/**
 * @brief Destroy a build system
 * @param build_system The build system to destroy
 */
void build_system_destroy(BuildSystem* build_system) {
    if (build_system == NULL) return;

    for (int i = 0; i < build_system->target_count; i++) {
        if (build_system->targets[i] == NULL) continue;
        build_target_destroy(build_system->targets[i]);
    }

    free(build_system->targets);
    free(build_system);
    build_system = NULL;
}

/**
 * @brief Builds the basec project
 * @return 0
 */
int main(void) {
    BuildTarget* target = build_target_create("basec");
    build_target_add_source(target, "src/main.c");
    build_target_add_source(target, "src/ds/basec_string.c");
    build_target_add_include(target, "include/ds");

    BuildSystem* build_system = build_system_create();
    build_system_add_target(build_system, target);
    build_system_build(build_system);
    build_system_destroy(build_system);
    return 0;
}