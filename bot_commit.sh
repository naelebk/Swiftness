#!/bin/bash

DISCORD_WEBHOOK_URL="https://discord.com/api/webhooks/1194617427028357190/NEWyHncA363p38fB41V0u9R-S7hfQvaZsNxRfAnzjTtfhNucqnJY3jseIXTYUlo87efQ"
GITHUB_REPO_URL="https://github.com/naelebk/Swiftness"

send_discord_notification() {
    commit_message="$1"
    payload="{\"content\":\"Nouveau commit sur le projet Swiftness : $commit_message\",\"username\":\"GitHub Bot\"}"
    curl -H "Content-Type: application/json" -X POST -d "$payload" "$DISCORD_WEBHOOK_URL"
}

get_latest_commit_message() {
    git clone "$GITHUB_REPO_URL" /tmp/swiftness-repo
    cd /tmp/swiftness-repo || exit 1
    latest_commit_message=$(git log --format="%s" -n 1)
    cd -
    rm -rf /tmp/swiftness-repo
    echo "$latest_commit_message"
}

latest_commit=$(get_latest_commit_message)
send_discord_notification "$latest_commit"
