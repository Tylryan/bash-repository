use std::process::exit;
use crate::Help;

pub enum Action 
{
    NewRepo,
    ListRepos,
    DeleteRepo
}

pub fn arg_parser(args: &Vec<String>) -> Action
{
    const SUCCESS: i32 = 0;
    const FAILURE: i32 = 1;

    let basename = args[0]
        .clone()
        .split('/')
        .last()
        .unwrap()
        .to_string();

    let argc = args.len();
    if argc == 1 
    {
        Help::main(&basename);
        exit(FAILURE);
    }
    match args[1].as_str()
    {
        "repo" | "r" => match args.get(2)
        {
            Some(value) => match value.as_str()
            {
                "--help" => {Help::main(&basename); exit(SUCCESS);},
                "new" | "n" => match args.get(3) 
                {
                    Some(_) => Action::NewRepo,
                    None => {Help::new(&basename); exit(FAILURE);}
                },
                "list" | "ls"   => Action::ListRepos,
                "delete" | "rm" => match args.get(3) 
                {
                    Some(_) => Action::DeleteRepo,
                    None => {Help::delete(&basename); exit(SUCCESS);}
                }
                _ => {Help::main(&basename); exit(FAILURE);}
            },
            None => {Help::repo(&basename); exit(FAILURE);}
        },
        // Move on to the next option
        _ => {Help::main(&basename); exit(FAILURE);}
    }
}
