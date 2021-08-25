use std::fs;
use std::path::Path;

use tar::Archive;
use tempfile::tempdir;
use xz2::read::XzDecoder;

const REMOTE_URL: &str  = "https://github.com/ziglang/zig/releases/download/0.7.1/zig-linux-x86_64-0.7.1.tar.xz";
const BINARY_DIRECTORY: &str = "/tmp";
const BINARY_NAME: &str = "zig";

fn main() -> Result<(), Box<dyn std::error::Error>> {
    let url = reqwest::Url::parse(REMOTE_URL)?;

    // Nested use of `ok_or` seems pretty hacky, but necessary for `Result`.
    let artifact_name = url.path_segments().ok_or("Cannot parse url")?.last().ok_or("Cannot parse url")?;

    // Long-term, long into async w/ reqwest.
    let res = reqwest::blocking::get(url.as_str())?;
    let mut archive = Archive::new(XzDecoder::new(res));

    let tmp_dir = tempdir()?;
    archive.unpack(tmp_dir.path())?;

    // Definitely need a better solution here (i.e. we can't just assume its a tar)
    let extracted_artifact_name = artifact_name.split(".tar").nth(0).ok_or("Cannot extract directory from compressed file name")?;

    let src_path = tmp_dir.path().join(extracted_artifact_name).join(BINARY_NAME);
    let dest_path = Path::new(BINARY_DIRECTORY).join(BINARY_NAME);

    fs::copy(src_path, dest_path)?;

    Ok(())
}
