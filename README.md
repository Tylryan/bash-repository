### NOTE: `--help` with most scripts will provide you with some pretty decent information about them.  

## elinks-search
![Elinks](./assets/elinks-search-example.gif)
**Quickly search the web from the command line using Elinks** 

Note that i'm using `www` instead of `elinks-search`.
This is because I've aliased `www` to `elinks-search` in order to write less.

## gp.sh
Automatically performs a git push
- message = $1
  - Put this in quotes
- location = $2

Note: Message and Location are optional. If you don't enter in either, the commit message will be whatever the current day is.
E.g "Auto-commit on Xday, XX-XX-XX at XX:XX AM/PM"

## ssh-setup.sh
- Automatically downloads Private and Public keys.
- Copies the public key to your clipboard.
- You just have to paste that into your github account settings.

## man-search
Provides a better search than `man -k "fprintf"`
- More refined result
- Color Coded  (result of using Grep)
- Options
    - `-b`: for a broad search
    - `-B`: for an even broader search
    - Default search is Narrow

## new-scala-project
- Creates a new scala project with SBT
- Creates the build.sbt and plugins.sbt files
- Includes a couple packages and plugins
    - Compiles a Fat Jar

## Compilers
- `asmc`: Assembly
- `cpp_run`: C/C++
