extern crate reqwest;

use std::collections::HashMap;

const HOST: &str = "http://localhost:8000";

fn main() {
    let client = reqwest::Client::new();
    let mut resp = client.get(HOST).send().unwrap();
    let json_resp: HashMap<String, Vec<String>>  = resp.json().unwrap();
    let files = &json_resp["files"];

    for file in files {
        let url = format!("{}/{}", HOST, file);
        let mut individual_resp = client.get(&url).send().unwrap();
        let text = individual_resp.text().unwrap();
        println!("{}", text);
    }
}
