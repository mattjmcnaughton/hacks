#![feature(proc_macro_hygiene, decl_macro)]

extern crate rocket_pastebin_demo;

#[macro_use] extern crate rocket;
#[macro_use] extern crate rocket_contrib;
extern crate rand;

#[cfg(test)] mod tests;

use std::io;
use std::fs;
use std::fs::File;
use std::path::Path;

use rocket::Data;
use rocket::response::content;
use rocket_contrib::json::JsonValue;

use self::rocket_pastebin_demo::paste_id::PasteID;

const HOST: &str = "http://localhost:8000";
const UPLOAD_PATH: &str = "upload";
const ID_LENGTH: usize = 12;

#[post("/", data = "<paste>")]
fn upload(paste: Data) -> io::Result<String> {
    let id = PasteID::new(ID_LENGTH);
    let filename = format!("{upload}/{id}", upload = UPLOAD_PATH, id = id);
    let url = format!("{host}/{id}\n", host = HOST, id = id);

    paste.stream_to_file(Path::new(&filename))?;
    Ok(url)
}

#[get("/<id>")]
fn retrieve(id: PasteID) -> Option<content::Plain<File>> {
    let filename = format!("{upload}/{id}", upload = UPLOAD_PATH, id = id);
    File::open(&filename).map(|f| content::Plain(f)).ok()
}

#[get("/")]
fn index() -> JsonValue {
    let paths = fs::read_dir(format!("./{upload}", upload = UPLOAD_PATH)).unwrap();

    let files = paths
        .map(|path| {
            String::from(path.unwrap().path().file_name().unwrap().to_str().unwrap())
        })
        .collect::<Vec<String>>();

    json!({
        "files": files
    })
}

fn rocket() -> rocket::Rocket {
    rocket::ignite().mount("/", routes![index, upload, retrieve])
}

fn main() {
    rocket().launch();
}
