# Contributing
When contributing to this repository, please first discuss the change you wish to make via issue,
email, or any other method with the other maintainers of this repository before making a change. 

## Pull Request Process
1. Ensure any install or build dependencies are not part of any commit (not pushed to remote).
2. Update the README.md with details of changes to the interface, this includes new environment 
   variables, exposed ports, useful file locations and container parameters.
4. You may merge the Pull Request in once you have the sign-off of two other developers, or if you 
   do not have permission to do that, you may request the second reviewer to merge it for you.

## Update your fork with changes on remote:
1. Add upstream remote:	
```
  git remote add upstream https://github.com/mortenskoett/eCP.git
```

2. Fetch newest:
```
  git fetch upstream
``` 
3. Update your current branch using one of the two:
```
git merge upstream/master
git rebase upstream/master
```

## Remember
- To check whether you are pull requesting into remote or upstream.
- To push to the correct remote e.g. `git push origin your_branch` to push to the remote of the fork.
