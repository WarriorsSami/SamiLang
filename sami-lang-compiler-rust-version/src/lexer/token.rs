use phf::phf_map;

#[derive(Debug, Clone, Eq, PartialEq, Hash)]
pub enum Token<'t> {
    Eof,
    // identifiers + literals
    Ident(&'t [u8]),
    Int(&'t [u8]),
    // operators
    Assign,
    Plus,
    Minus,
    Bang,
    Asterisk,
    Slash,
    Lt,
    Gt,
    LtEq,
    GtEq,
    Eq,
    NotEq,
    // delimiters,
    Comma,
    Semicolon,
    LParen,
    RParen,
    LBrace,
    RBrace,
    // keywords,
    Function,
    Let,
    True,
    False,
    If,
    Else,
    Return,
}

pub static KEYWORDS: phf::Map<&'static [u8], Token> = phf_map! {
    b"let" => Token::Let,
    b"fn" => Token::Function,
};
