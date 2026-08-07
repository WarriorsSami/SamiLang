use std::io::{BufRead, BufReader, BufWriter, Read, Write};
use crate::lexer::Lexer;

pub struct Repl<R: Read, W: Write> {
    io_reader: BufReader<R>,
    io_writer: BufWriter<W>,
}

impl<R: Read, W: Write> Repl<R, W> {
    pub fn new(reader: R, writer: W) -> Self {
        Self {
            io_reader: BufReader::new(reader),
            io_writer: BufWriter::new(writer),
        }
    }

    pub fn start(&mut self) -> anyhow::Result<()> {
        loop {
            write!(self.io_writer, "{PROMPT}")?;
            self.io_writer.flush()?;

            let mut line = String::new();
            match self.io_reader.read_line(&mut line)? {
                len if len == 0 => {
                    return Ok(());
                },
                _ => {
                    let lexer = Lexer::new(line.as_str());
                    let tokens = lexer.into_iter().collect::<Result<Vec<_>, _>>()?;
                    for token in tokens {
                        writeln!(self.io_writer, "{}", token)?;
                    }
                }
            }
        }
    }
}

static PROMPT: &'static str = ">> ";
