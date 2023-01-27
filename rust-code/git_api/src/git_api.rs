use std::process::{exit, ExitStatus};
use reqwest::{Client, StatusCode};
use serde_json::Value;
use crate::Config;

const SUCCESS: i32 = 0;
const FAILURE: i32 = 1;
pub struct GitApi 
{
    username: String,
    token: String
}

impl GitApi 
{
    pub fn new()  -> Self
    {
        let config = Config::new();
        let token  = config.get_token_string()
            .expect("Error: Could not find token");
        let token    = format!("token {}", token);
        let username = config.get_user_name()
            .expect("Error: Could not find username");
        GitApi {username, token}
    }

    pub async fn get_all_repo_info(&self) -> Result<(StatusCode, Value), reqwest::Error>
    {
    let client = Client::new();
    let url    = "https://api.github.com/user/repos";
    let res    = client.get(url)
        .header("User-Agent", "rust-testing")
        .header( "Authorization", &self.token)
        .send()
        .await?;

    let status      = res.status();
    let body: Value = serde_json::from_str(&res.text().await?).unwrap();

    Ok((status, body))
    }

    pub async fn create_new_repo(&self, repo_name: &str) -> Result<(StatusCode, String), reqwest::Error>
    {
        let client = Client::new();
        let url    = "https://api.github.com/user/repos";
        let mut private: bool = false;

        if self.repo_exists(repo_name).await?
        {
            eprintln!("Error: `{repo_name}` exists already");
            exit(FAILURE);
        }

        loop 
        {
            match Config::prompt("Private? [N/y] ").to_lowercase().as_str()
            {
                "y" | "yes"     => {private = true; break;},
                "n" | "no" | "" => {break;}
                value => println!("`{value}` is not a valid option!")
            }
        }
        let description = Config::prompt("Simple Repo Description: ");

        let body   = format!("{{
            \"name\": \"{repo_name}\",
            \"auto_init\": true,
            \"private\": false,
            \"description\": \"{description}\",
            \"gitignoretemplate\": \"nanoc\"
        }}");

        let response = client.post(url)
            .header("User-Agent", "rust-testing")
            .header( "Authorization", &self.token)
            .header("Accept", "application/vnd.github+json")
            .body(body)
            .send()
            .await?;

        let mut initialize_current_dir = false;
        loop 
        {
            match Config::prompt("Initialize current directory? [N/y] ").to_lowercase().as_str()
            {
                "y" | "yes"     => {initialize_current_dir = true ; break;},
                "n" | "no" | "" => {break;},
                value           => {println!("`{value}` is not a valid reponse!");}
            }
        }

        if initialize_current_dir 
        {
            self.init_current_dir(repo_name);
        }

        let status = response.status();
        let body   = response.text().await?;

        Ok((status, body))
    }

    pub async fn list_my_repos(&self, per_page: u32) -> Result<(StatusCode, Vec<String>), reqwest::Error>
    {
        let client   = Client::new();
        let url      = format!("https://api.github.com/user/repos?per_page={per_page}");
        let response = client.get(url)
            .header("User-Agent", "rust-testing")
            .header("Accept", "application/vnd.github+json")
            .header("Authorization", &self.token)
            .send()
            .await?;

        let status       = response.status();
        let body: Value  = serde_json::from_str(&response.text().await?).unwrap();

        let mut hector: Vec<String> = Vec::new();
        // Append each repo to hector
        body.as_array()
            .unwrap()
            .iter()
            .for_each(|x| hector.push(
                    x.get("full_name")
                    .unwrap()
                    .to_string()));

        Ok((status,hector))
    }

    pub async fn delete_repo(&self, repo: &str) -> Result<(StatusCode, String), reqwest::Error>
    {
        let client   = Client::new();
        // let url      = format!("https://api.github.com/user/{repo}");
        let url = format!("https://api.github.com/repos/{}/{}",
                          self.username,
                          repo);
        let response = client.delete(url)
            .header("User-Agent", "rust-testing")
            .header("Accept", "application/vnd.github+json")
            .header("Authorization", &self.token)
            .send()
            .await?;

        let status = response.status();
        let body   = response.text().await?;
        Ok((status, body))
    }
    pub fn print_repos(body: &Vec<String>)
    {
        for i in 0..body.len()
        {
            let repo = body[i].trim_matches('"');
            GitApi::print_with_correct_tabs(i, repo);
        }
        println!();
    }

    fn print_with_correct_tabs(index: usize, repo: &str)
    {
        let repo_len = repo.len();
        if index % 2 == 0 {
            if repo_len >= 35      {print!("{index}: {repo}\t")}
            else if repo_len >= 21 {print!("{index}: {repo}\t\t\t");} 
            else if repo_len >= 19 {print!("{index}: {repo}\t\t\t\t");}
            // else if repo_len >= 14 {print!("{index}: {repo}\t\t\t\t");}
            // else if repo_len >= 12 {print!("{index}: {repo}\t\t\t\t");}
            else                   {print!("{index}: {repo}\t\t\t\t\t")}
            return;
        }
        println!("{index}: {repo}");
    }

    pub async fn repo_exists(&self, repo: &str) -> Result<bool, reqwest::Error>
    {
        let (_status, possible_repos) = self.list_my_repos(100).await?;
        // Does repo exist
        let has_matching_repo = possible_repos
            .iter()
            .map(|x| x.trim_matches('"'))
            .map(|x| x.split('/').last().unwrap())
            .filter(|x| *x == repo)
            .next()
            .is_some();
        // If repo doesn't exist, return false
        if has_matching_repo { return Ok(true); }

        Ok(false)
    }

    pub fn init_current_dir(&self, repo_name: &str) 
    {
        GitApi::run_git(&["init"]);
        GitApi::run_git(&["add","."]);
        let msg = format!("-m '{}'",Config::prompt("Commit Message: "));

        GitApi::run_git(&["commit", &msg]);
        let remote_url = format!("git@github.com:{}/{}.git",
                                 self.username,
                                 repo_name);
        GitApi::run_git(&["remote", "add", "origin", &remote_url]);
        GitApi::run_git(&["push","-u", "origin", "master"]);
        GitApi::run_git(&["remote", "-v"]);
    }

    pub fn run_git(commands: &[&str]) -> ExitStatus
    {
        let status = std::process::Command::new("git")
            .args(commands)
            .status()
            .unwrap();
        return status;
    }

}
