use std::fs;
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

fn main() -> Result<(), Box<dyn std::error::Error>> {
    let args = Cli::from_args();
    args.verbosity.setup_env_logger("binstaller")?;

    let url = reqwest::Url::parse(&args.remote_url)?;

    // Nested use of `ok_or` seems pretty hacky, but necessary for `Result`.
    let artifact_name = url.path_segments().ok_or("Cannot parse url")?.last().ok_or("Cannot parse url")?;

    // Long-term, long into async w/ reqwest.
    let res = reqwest::blocking::get(url.as_str())?;
    let mut archive = Archive::new(XzDecoder::new(res));

    let tmp_dir = tempdir()?;
    archive.unpack(tmp_dir.path())?;

    info!("Unpacking tar into {:?}", tmp_dir.path());

    // Definitely need a better solution here (i.e. we can't just assume its a tar)
    let extracted_artifact_name = artifact_name.split(".tar").nth(0).ok_or("Cannot extract directory from compressed file name")?;

    let src_path = tmp_dir.path().join(extracted_artifact_name).join(&args.binary_name);
    let dest_path = Path::new(&args.destination_directory).join(&args.binary_name);

    fs::copy(src_path, dest_path)?;

    Ok(())
}
