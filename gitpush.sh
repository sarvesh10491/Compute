git add -A

echo 'Enter the commit message : '
read commitMessage
git commit -m "$commitMessage"

branch = "master"
echo 'Enter the name of the branch [default is master] : '
read branch

git push origin $branch
read