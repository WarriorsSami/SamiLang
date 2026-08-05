use thiserror::Error;

#[derive(Error, Debug)]
pub enum CompileError {
    #[error("invalid token `{0}` encountered during lexical analysis")]
    InvalidToken(String),
}
