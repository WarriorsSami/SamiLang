use thiserror::Error;

#[derive(Error, Debug, Eq, PartialEq)]
pub enum LexError {
    #[error("invalid token `{0}` encountered")]
    InvalidToken(char),
    #[error(r#"no matching closing quote found for string "{0}""#)]
    UnterminatedString(String),
    #[error(r#"invalid escape character `{0}` encountered in string "{1}""#)]
    InvalidEscape(char, String),
}
