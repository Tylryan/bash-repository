# In case I lose everything on my computer, I will have this.
# Run install.sh
## It should do the following
- Create a bin directory in ~/
    - If you have one there, it shouldn't replace anything.
- Move them to the new bin directory
- Set that directory as a PATH in whichever shell you are using.
- Restart your computer if you so choose.

## Options
### -Rr 
    - This will both reboot and remove bash_repository

### -R 
	- This only removes the bash_repositories
### -r 
	- This only reboots your computer.

I would recommend at least using `-r`. It's cleaner.

After your computer restarts, you should be able to run your .sh files from anywhere in the terminal.

# Other Scripts 

## add_git
Automatically performs a git push
- message = $1
  - Put this in quotes
- location = $2

Note: Message and Location are optional. If you don't enter in either, the commit message will be whatever the current day is.
E.g "Auto-commit on Xday, XX-XX-XX at XX:XX AM/PM"

## rice-copy
This just copies the original Rice Fintech Bootcamp's directory to another directory.

## tracker.sh
This runs my tracker program.

## sh-backup

Automatically back up my sh repository.

## Options
- ### -u 
	- This allows you to update your readme before you commit.
