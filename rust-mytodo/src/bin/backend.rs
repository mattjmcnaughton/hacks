#![feature(proc_macro_hygiene, decl_macro)]

#[macro_use]
extern crate rocket;
#[macro_use]
extern crate rocket_contrib;
#[macro_use]
extern crate serde;

use mytodo::db::{query_task, establish_connection};

#[get("/tasks")]
fn tasks_get() -> String {
    let mut response: Vec<String> = vec![];

    let conn = establish_connection();
    for task in query_task(&conn) {
        response.push(task.title);
    }

    response.join("\n")
}

fn main() {
    rocket::ignite()
        .mount("/", routes![tasks_get])
        .launch();
}
