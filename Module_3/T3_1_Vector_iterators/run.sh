#!/bin/bash

REPO_ROOT=/submission-repo/
EXERCISE_DIR=/exercise
MODULE=Module_3
EXERCISE=T3_1_Vector_iterators
SRC_DIR=src
SOLUTION_FILES=("vector_it.cpp")
SUPPLEMENTARY_FILES=("vector_it.hpp")

if sudo-capture pre git-clone-submission /exercise/git_rsa; then

    for file in "${SOLUTION_FILES[@]}"; do
        file_path="$REPO_ROOT/$MODULE/$EXERCISE/$SRC_DIR/$file"
        if test ! -f "$file_path"; then
            echo -e "\"$MODULE/$EXERCISE/$SRC_DIR/$file\" DOES NOT exist in the repository.\n" \
                "Check the file struture of your repository. \n" \
                "THE FILES AND DIRECTORIES IN THE TEMPLATES MUST NOT BE MODIFIED!" >/feedback/err
            exit 1
        else
            # Move the exercise files into /submission/user
            mv "$file_path" "/submission/user/$file"
        fi
    done

    for file in "${SUPPLEMENTARY_FILES[@]}"; do
        file_path="$EXERCISE_DIR/$SRC_DIR/$file"
        if test -f "$file_path"; then
            cp "$file_path" "/submission/user/$file"
        else
            echo -e "\"$file_path\" DOES NOT exist in the grader file system.\n" \
                "Contact the course staff. \n" >/feedback/err
            exit 1
        fi
    done

    python3 /entrypoint/run.py
else
    echo -e "Error in cloning the repository!\nCheck your GIT repository configuration and validate deploy keys!" >/feedback/err
fi
