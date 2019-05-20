use boondock::Docker;

fn main() {
    let docker = Docker::connect_with_defaults().expect("Failed to connect to Docker");
    let images = docker.images(false).expect("Failed to query Docker images");

    for image in &images {
        println!("{} -> Size: {}", image.Id, image.Size);
    }
}
