use std::io::{stdin, stdout};
use crate::repl::Repl;

mod lexer;
mod repl;

fn main() -> anyhow::Result<()> {
    let mut repl = Repl::new(stdin(), stdout());
    repl.start()?;

    Ok(())
}
