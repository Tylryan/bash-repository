use std::io::prelude::*;
use std::fs::OpenOptions;
pub struct Config 
{
    // config_path: String,
    // exists: bool,
    username: Option<String>,
    token: Option<String>,
}

impl Config 
{
    pub fn new() -> Self 
    {
        let home        = std::env::var("HOME").unwrap();
        let config_dir  = format!("{home}/.config/got");
        let config_path = format!("{config_dir}/config");

        match std::fs::metadata(&config_path)
        {
            Ok(_) => (),
            Err(_) => 
            {
                match std::fs::create_dir(&config_dir) 
                {
                    // If it works, cool
                    Ok(_) => (),
                    // If it doesn't cool
                    Err(_) => ()
                }

                {
                    std::fs::File::create(&config_path).unwrap();
                }
                let mut file = OpenOptions::new()
                    .write(true)
                    .append(true)
                    .open(&config_path)
                    .expect("Err: Could not open File");

                println!("Created {config_path}");

                let username    = Config::prompt("Enter your username: ");
                let token       = Config::prompt("Enter your github token: ");
                let user_name   = format!("username={username}\n");
                let token_entry = format!("token={token}\n");

                file.write_all(user_name.as_bytes()).unwrap();
                file.write_all(token_entry.as_bytes()).unwrap();

                return Self {
                    // config_path, 
                    // exists: true, 
                    username: Some(user_name),
                    token: Some(token_entry) 
                };
            }
        }

        let username = Config::get_username(&config_path);
        let token    = Config::get_token(&config_path);
        Self {
            // config_path, 
            // exists: true, 
            username: Some(username), 
            token: Some(token) 
        }
    }


    pub fn get_user_name(&self)    -> Option<String> { self.username.clone()}
    pub fn get_token_string(&self) -> Option<String> { self.token.clone() }

    pub fn prompt(msg: &str) -> String 
    {
        let mut buffer = String::new();
        print!("{msg}");
        std::io::stdout().flush().unwrap();
        std::io::stdin().read_line(&mut buffer).unwrap();
        return buffer.trim().to_string();
    }

    fn get_username(config_path: &str) -> String 
    {
        let config   = std::fs::read_to_string(&config_path).unwrap();
        let username = Config::search_key("username", &config)
            .expect("Error: No Username!");
        return username;
    }
    fn get_token(config_path: &str) -> String 
    {
        let config = std::fs::read_to_string(&config_path).unwrap();
        let token  = Config::search_key("token", &config)
            .expect("Error: No Token!");
        return token;
    }

    fn search_key(key: &str, config: &str) -> Option<String>
    {
        for line in config.lines() 
        {
            let key_value: Vec<&str> = line
                .split('=')
                .map(|x| x.trim())
                .collect();
            if key_value.get(0).unwrap() == &key 
            {
                return Some(key_value[1].to_string());
            }
        }
        return None;
    }

}
