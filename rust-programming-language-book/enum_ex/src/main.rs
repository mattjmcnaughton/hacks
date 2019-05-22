enum IpAddr {
    V4(String),
    V6(String),
}

// Can define methods on enums
impl IpAddr {
    fn identify(&self) -> &String {
        match self {
            IpAddr::V4(addr) => addr,
            IpAddr::V6(addr) => addr,
        }
    }
}

fn plus_one(x: Option<i32>) -> Option<i32> {
    match x {
        None => None,
        Some(i) => Some(i + 1),
    }
}

fn main() {
    let home = IpAddr::V4(String::from("127.0.0.1"));
    let loopback = IpAddr::V6(String::from("::1"));

    println!("{}:{}", home.identify(), loopback.identify());

    let five = Some(5);
    let _six = plus_one(five);
    let none = plus_one(None);
}
