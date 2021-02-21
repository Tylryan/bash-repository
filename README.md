# In case I lose everything on my computer, I will have this.
# Make fresh_start.sh excecutable and run it.
It should do the following
* Create a bin directory in ~/
* Make all your .sh files excecutable
* Move them to the new bin directory
* Set that directory as a PATH
* Restart your computer

Options
* -Rr This will both reboot and remove bash_repositories
* -R This only removes the bash_repositories
* -r This only reboots your computer.

After your computer restarts, you should be able to run your .sh files from anywhere in the terminal.

# Other Scripts 

## add_git
Automatically performs a git push
* message = $1
  * Put this in quotes
* location = $2

Note: Message and Location are optional. If you don't enter in either, the commit message will be whatever the current day is.
E.g "Auto-commit on Xday, XX-XX-XX at XX:XX AM/PM"

## rice-copy
This just copies the original Rice Fintech Bootcamp's directory to another directory.

## tracker.sh
This runs my tracker program.

## sh-backup

Automatically back up my sh repository.

Options
-u This allows you to update your readme before you commit.
