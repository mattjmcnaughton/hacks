use std::io::prelude::*;
use std::io::{self, Write};
use std::io::BufReader;
use std::fs::File;

use structopt::StructOpt;

/// Search for pattern in a file and display the lines that contain it.
#[derive(StructOpt)]
struct Cli {
    /// The pattern to look for.
    pattern: String,
    /// The path to the file to read
    #[structopt(parse(from_os_str))]
    path: std::path::PathBuf,
}

fn main() -> Result<(), Box<dyn std::error::Error>> {
    let args = Cli::from_args();

    let f = File::open(&args.path)?;
    let reader = BufReader::new(f);

    let stdout = io::stdout();
    let mut handle = stdout.lock();

    for poss_line in reader.lines() {
        if let Ok(line) = poss_line {
            if line.contains(&args.pattern) {
                writeln!(handle, "{}", line)?;
            }
        }
    }

    Ok(())
}
