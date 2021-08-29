use std::error::Error;
use std::fs;
use std::io::Read;
use std::path::Path;

use quicli::prelude::*;
use structopt::StructOpt;

use tar::Archive;
use tempfile::tempdir;
use xz2::read::XzDecoder;

#[derive(Debug, StructOpt)]
struct Cli {
    remote_url: String,
    destination_directory: String,
    binary_name: String,
    #[structopt(flatten)]
    verbosity: Verbosity,
}

fn main() -> Result<(), Box<dyn Error>> {
    let args = Cli::from_args();
    args.verbosity.setup_env_logger("binstaller")?;

    run(&args.remote_url, &args.destination_directory, &args.binary_name)
}

fn run(remote_url: &String, destination_directory: &String, binary_name: &String) -> Result<(), Box<dyn Error>> {
    let url = reqwest::Url::parse(remote_url)?;

    let artifact_path_segments = url.path_segments().ok_or(format!("Cannot parse {} into path segments", remote_url))?;
    let artifact_name = artifact_path_segments.last().ok_or(format!("Cannot extract artifact name from path segments returned by {}", remote_url))?;

    // Long-term, long into async w/ reqwest.
    let res = reqwest::blocking::get(url.as_str())?;
    let decoder = decoder_factory(artifact_name, res)?;
    let mut archive = Archive::new(decoder);

    let tmp_dir = tempdir()?;
    archive.unpack(tmp_dir.path())?;

    info!("Unpacking tar into {:?}", tmp_dir.path());

    // Definitely need a better solution here (i.e. we can't just assume its a tar)
    let extracted_artifact_name = artifact_name.split(".tar").nth(0).ok_or("Cannot extract directory from compressed file name")?;

    let src_path = tmp_dir.path().join(extracted_artifact_name).join(binary_name);
    let dest_path = Path::new(destination_directory).join(binary_name);

    fs::copy(src_path, dest_path)?;

    Ok(())
}

fn decoder_factory(remote_artifact_name: &str, result: reqwest::blocking::Response) -> Result<Box<dyn Read>, Box<dyn Error>> {
    if remote_artifact_name.ends_with(".xz") {
        Ok(Box::new(XzDecoder::new(result)))
    } else {
        // https://doc.rust-lang.org/std/convert/trait.From.html#impl-From%3C%26%27_%20str%3E
        let boxed_err = Box::<dyn Error>::from(format!("Cannot determine decoder for {}", remote_artifact_name));
        Err(boxed_err)
    }
}
