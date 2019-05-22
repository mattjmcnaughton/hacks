fn main() {
    // vec! is a macro to create a vector using type inference. Vectors can only store values of
    // the same type. Can use Enums/Structs if necessary.
    let mut v = vec![1, 2, 3, 4, 5];

    // Iterate over mutable references to each element. If we want to do this, then `v`
    // itself must be mutable.
    for i in &mut v {
        *i += 51;
    }

    for i in v {
        println!("{}", i);
    }
}
