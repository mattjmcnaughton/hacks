use std::error::Error;
use std::fs;
use std::io::Read;
use std::path::Path;

use flate2::read::GzDecoder;
use quicli::prelude::*;
use structopt::StructOpt;
use tar::Archive;
use tempfile::tempdir;
use xz2::read::XzDecoder;

#[derive(Debug, StructOpt)]
struct Cli {
    remote_url: String,
    destination_directory: String,
    extracted_artifact_base: String,
    binary_name: String,
    #[structopt(flatten)]
    verbosity: Verbosity,
}

fn main() -> Result<(), Box<dyn Error>> {
    let args = Cli::from_args();
    args.verbosity.setup_env_logger("binstaller")?;

    run(&args.remote_url, &args.destination_directory, &args.extracted_artifact_base, &args.binary_name)
}

fn run(remote_url: &String, destination_directory: &String, extracted_artifact_base: &String, binary_name: &String) -> Result<(), Box<dyn Error>> {
    let url = reqwest::Url::parse(remote_url)?;

    let artifact_path_segments = url.path_segments().ok_or(format!("Cannot parse {} into path segments", remote_url))?;
    let artifact_name = artifact_path_segments.last().ok_or(format!("Cannot extract artifact name from path segments returned by {}", remote_url))?;

    // Long-term, long into async w/ reqwest.
    let res = reqwest::blocking::get(url.as_str())?;
    let decoder = decoder_factory(artifact_name, res)?;
    let mut archive = Archive::new(decoder);

    let tmp_dir = tempdir()?;

    info!("Unpacking tar into {:?}", tmp_dir.path());
    archive.unpack(tmp_dir.path())?;

    let src_path = tmp_dir.path().join(extracted_artifact_base).join(binary_name);

    // TODO: This is hacky
    let dest_path = Path::new(destination_directory).join(Path::new(binary_name).file_name().unwrap());

    info!("Copying file from {:?} to {:?}", src_path, dest_path);
    fs::copy(src_path, dest_path)?;

    Ok(())
}

fn decoder_factory(remote_artifact_name: &str, result: reqwest::blocking::Response) -> Result<Box<dyn Read>, Box<dyn Error>> {
    if remote_artifact_name.ends_with(".xz") {
        info!("Identified extractable file type: {}", "xz");
        Ok(Box::new(XzDecoder::new(result)))
    } else if remote_artifact_name.ends_with(".gz") {
        info!("Identified extractable file type: {}", "gz");
        Ok(Box::new(GzDecoder::new(result)))
    } else {
        // https://doc.rust-lang.org/std/convert/trait.From.html#impl-From%3C%26%27_%20str%3E
        let boxed_err = Box::<dyn Error>::from(format!("Cannot determine decoder for {}", remote_artifact_name));
        Err(boxed_err)
    }
}
