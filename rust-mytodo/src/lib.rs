#[macro_use]
extern crate serde;

#[derive(Clone, Debug, Deserialize, Serialize)]
pub struct Task {
    pub id: i32,
    pub title: String,
}

#[derive(Clone, Debug, Deserialize, Serialize)]
pub struct JsonApiResponse {
    pub data: Vec<Task>,
}
