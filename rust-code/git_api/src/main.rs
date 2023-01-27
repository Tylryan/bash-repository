mod git_api;
mod config;
mod arg_parser;
mod help;
use help::Help;
use git_api::GitApi;
use config::Config;
use arg_parser::{arg_parser, Action};

/* TODO: Update Help.
 * The commands aren't `gt r n User/repo`, its `gt r n repo`
 * or `gt r rm User/repo`, but rather `gt r rm repo`
 *
 * Though I haven't decided if I like that.
 * I might keep it for creating a repo, but for deleting a repo,
 * I might change it back to `User/repo`
 */
#[tokio::main]
async fn main() -> Result<(), reqwest::Error>
{
    let api = GitApi::new();
    let args: Vec<String> = std::env::args().collect();
    match arg_parser(&args)
    {
        Action::NewRepo => {
            let (status, _body) = api.create_new_repo(&args[3]).await?;
            if status.is_success() { println!("Created New Repo"); }
            else { println!("{status}"); }

        },
        Action::ListRepos => {
            let (status, body) = api.list_my_repos(100).await.expect("API DOWN");
            if status.is_success() { GitApi::print_repos(&body);}
            else { println!("{status}")}
        },
        Action::DeleteRepo => {
            loop 
            {
                // If repo doesn't exist, don't continue
                if !api.repo_exists(&args[3]).await?
                {
                    eprintln!("Error: `{}` is not a valid repo", args[3]);
                    return Ok(());
                }

                let msg = format!("Are you sure you want to delete {} [Y/n]? ", args[3]);
                let delete = Config::prompt(&msg);
                match delete.to_lowercase().as_str()
                {
                    "yes" | "y" | "" => {
                        let (status, body) = api.delete_repo(&args[3]).await?;
                        if status.is_success() { println!("Deleted: {}", args[3]);}
                        else {println!("{status}\n{body}");}
                        break;
                    },
                    "no" | "n" => {break;},
                    _ => println!("Error: `{delete}` is not valid reponse!"),
                }
            }
        },
        _ => println!("No Action")
    };

    Ok(())
}
