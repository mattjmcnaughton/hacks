# diesel_demo

http://diesel.rs/guides/getting-started/
Ensure we install `libpq-dev`.

Run `cargo install diesel_cli --no-default-features --features postgres`

Use `docker run -e POSTGRES_USER=username -e POSTGRES_PASSWORD=password -e
POSTGRES_DB=diesel_demo -p 5432:5432 -d postgres:10`
