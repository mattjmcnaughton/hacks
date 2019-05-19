fn main() {
    let ref_str = String::from("hello");
    let mutable_str = String::from("hhello");
    let mut mutable_ref_str = String::from("multiple_ref");

    let x = 5;

    println!("length: {}", uses_reference(&ref_str));

    uses_mutable_reference(&mut mutable_ref_str);
    takes_ownership(mutable_str);
    makes_copy(x);

    println!("Can still use string after reference: {}", mutable_ref_str);
}

// We call using references borrowing. You cannot modify something that you're borrowing.
fn uses_reference(s: &String) -> usize {
    s.len()
}

fn uses_mutable_reference(s: &mut String) {
    s.push_str("HIIII");
}

// Illegal, because can only have one mutable reference to a particular piece of data in a
// particular scope.
// fn _illegal_borrowing() {
//     let mut s = String::from("Hello");

//     let r1 = &mut s;
//     let r2 = &mut s;
//     println!("{} {}", r1, r2);
// }

// Illegal, bc cannot borrow `s` as mutable when it is also borrowed as immutable.
// fn _more_illegal_borrowing() {
//     let mut s = String::from("Hello");

//     let r1 = &s;
//     let r2 = &s;
//     let r3 = &mut s;

//     println!("{}, {}, and {}", r1, r2, r3);
// }

fn takes_ownership(mut some_string: String) {
    some_string.push_str(", world");
    println!("{}", some_string);
}

fn makes_copy(some_integer: i32) {
    println!("{}", some_integer);
}
