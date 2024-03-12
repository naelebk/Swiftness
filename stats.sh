#!/bin/bash

authors=$(git log --format='%aN' | sort -u)
for author in $authors; do
    echo "Statistiques pour l'auteur : $author"
    commits=$(git log --author="$author" --oneline --format='%H')
    total_added=0
    total_deleted=0
    total_modified=0
    for commit in $commits; do
        stats=$(git show --pretty=format: --numstat $commit)
        added=$(echo "$stats" | awk '{s+=$1} END {print s}')
        deleted=$(echo "$stats" | awk '{s+=$2} END {print s}')
        modified=$(echo "$stats" | awk '{s+=$1+$2} END {print s}')
        echo "Commit $commit : Ajoutées = $added, Supprimées = $deleted, Modifiées = $modified"
        total_added=$((total_added + added))
        total_deleted=$((total_deleted + deleted))
        total_modified=$((total_modified + modified))
    done
    echo "Total pour $author : Ajoutées = $total_added, Supprimées = $total_deleted, Modifiées = $total_modified"
    echo "-----------------------------"
done
