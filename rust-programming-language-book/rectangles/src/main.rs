// Derive adds useful behavior to custom types.
#[derive(Debug)]
struct Rectangle {
    width: u32,
    height: u32,
}

impl Rectangle {
    // Methods can take ownership of self, borrow self immutably, or borrow self mutably
    // just like with any other parameter.
    fn area(&self) -> u32 {
        self.width * self.height
    }

    fn can_hold(&self, other: &Rectangle) -> bool {
        self.width > other.width && self.height > other.height
    }

    // Can define "associated functions", which are like static methods (i.e. don't take self as a
    // parameter). Often used for constructors.
    // Use `::` syntax.
    fn square(size: u32) -> Rectangle {
        Rectangle { width: size, height: size }
    }
}

fn main() {
    let rect1 = Rectangle {
        width: 30,
        height: 50,
    };

    let rect2 = Rectangle {
        width: 50,
        height: 20,
    };

    let rect3 = Rectangle::square(30);

    println!(
        "The area of the rectangle is {} square pixels.",
        // Rust has automatic pointer referencing/dereferencing. So under the covers, this is
        // &rect1.area(), but Rust handles that automatically.
        rect1.area()
    );

    println!("Can rect1 hold rect2?: {}", rect1.can_hold(&rect2));
    println!("Can rect1 hold rect3?: {}", rect1.can_hold(&rect3));

    println!("rect1 is {:?}", rect1);
}
