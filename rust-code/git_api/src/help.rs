pub struct Help { }

impl Help 
{
    pub fn main(program_name: &str) 
    {
        println!("USAGE
    {program_name} <arg>

ARGUMENTS
    repo   | r              Alter your repositories
    --help | [nothing]      Display help messages for each argument

EXAMPLES
    Remove a repo: {program_name} r rm `User/repo`
    Getting Help:  {program_name} r rm [nothing]");
    }
    pub fn new(program_name: &str) 
    {
        println!("USAGE
    {program_name} new `User/repo`

DESCRIPTION
    The `new` argument will create a new remote Github repository.

ARGUMENTS
    <User/repo>             Enter in the name of the repo you want
                            to create.
    [nothing]               Displays this help message.
EXAMPLE
    {program_name} repo new `User/repo`");
    }
    pub fn delete(program_name: &str) 
    {
        println!("USAGE
    {program_name} delete `User/repo`

DESCRIPTION
    The 'delete' argument will delete a remote Github repository.

ARGUMENTS
    <User/repo>             Enter in the name of the repo you want
                            to delete.
    [nothing]               Displays this help message.
EXAMPLE
    {program_name} repo delete `User/repo`

TIP
    To list all your repos, enter `{program_name} r list`\n");
    }
    pub fn repo(program_name: &str) 
    {
        println!("USAGE
    {program_name} repo <arg>

DESCRIPTION
    The `repo` argument is for listing, creating, or removing
    remote Github repositories.

ARGUMENTS
    [nothing]               Displays this help message
    delete   | rm           Remove a repository
    new      | n            Create a repository
    list     | ls           List all repositories

EXAMPLES
    Remove a repo:  {program_name} r rm `User/repo`
    Create a repo:  {program_name} r n  `User/repo`
    List all repos: {program_name} r ls
    Arg Help: {program_name} r rm [nothing]");
    }
}
