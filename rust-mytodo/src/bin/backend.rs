#![feature(proc_macro_hygiene, decl_macro)]

#[macro_use]
extern crate rocket;
extern crate rocket_contrib;
extern crate serde;

use rocket_contrib::json::Json;

use mytodo::db::{query_task, establish_connection};
use mytodo::db::models::JsonApiResponse;

#[get("/tasks")]
fn tasks_get() -> Json<JsonApiResponse> {
    let mut response = JsonApiResponse { data: vec![], };

    let conn = establish_connection();
    for task in query_task(&conn) {
        response.data.push(task);
    }

    Json(response)
}

fn main() {
    rocket::ignite()
        .mount("/", routes![tasks_get])
        .launch();
}
