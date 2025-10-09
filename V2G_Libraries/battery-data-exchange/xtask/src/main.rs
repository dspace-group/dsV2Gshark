//! Automation of some commonly used tasks.
//! See here for more details on xtask: https://github.com/matklad/cargo-xtask

use std::process::Command;

fn main() {
    let args: Vec<String> = std::env::args().collect();

    match args.get(1).map(String::as_str) {
        Some("ci") => ci(),
        _ => {
            eprintln!("No command provided.");
            std::process::exit(1);
        }
    }
}

fn run(cmd: &str, args: &[&str]) {
    let status = Command::new(cmd).args(args).status().unwrap();
    if !status.success() {
        std::process::exit(status.code().unwrap_or(1));
    }
}

/// Complete CI workflow with
///  - format check
///  - unit tests
///  - clippy
///  - build
fn ci() {
    run("cargo", &["fmt", "--all", "--check"]);
    run(
        "cargo",
        &["clippy", "--", "-W", "clippy::pedantic", "-D", "warnings"],
    );
    run("cargo", &["test", "--all-targets", "--all-features"]);

    if !Command::new("cargo")
        .arg("build")
        .arg("--release")
        .env("RUSTFLAGS", "-D warnings")
        .status()
        .unwrap()
        .success()
    {
        std::process::exit(1);
    }
}
