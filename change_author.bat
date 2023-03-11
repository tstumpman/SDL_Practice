git filter-branch --env-filter '
if [ "$GIT_COMMIT" = "f5934115acd2fe3fabd70e6c80224c44e7082e47" ]
then
    export GIT_AUTHOR_NAME="tstumpman"
    export GIT_AUTHOR_EMAIL="tstumpman@gmail.com"
    export GIT_COMMITTER_NAME="tstumpman"
    export GIT_COMMITTER_EMAIL="tstumpman@gmail.com"
fi
' HEAD
pause