use std::fmt::{Display, Formatter};
use phf::phf_map;

// TODO: add other tokens as required

#[derive(Debug, Clone, Eq, PartialEq, Hash)]
pub enum Token<'t> {
    Eof,
    // identifiers + literals
    Ident(&'t [u8]),  // x
    Int(&'t [u8]),    // 1
    String(&'t [u8]), // "str"
    // operators
    Assign,     // =
    LogicalAnd, // &&
    LogicalOr,  // ||
    Plus,       // +
    Minus,      // -
    LogicalNot, // !
    Mul,        // *
    Div,        // /
    Mod,        // %
    Lt,         // <
    Gt,         // >
    LtEq,       // <=
    GtEq,       // >=
    Eq,         // ==
    NotEq,      // !=
    And,        // &
    Or,         // |
    Xor,        // ^
    Not,        // ~
    LShift,     // <<
    RShift,     // >>
    IoRead,     // <<=
    IoWrite,    // >>=
    Dot,        // .
    // delimiters,
    Comma, // ,
    Semicolon, // ;
    Colon, // :
    LParen, // (
    RParen, // )
    LBrace, // {
    RBrace, // }
    LBracket, // [
    RBracket, // ]
    // keywords,
    Function, // fn
    Let, // let
    True, // true
    False, // false
    If, // if
    Else, // else
    Return, // return
}

impl Token<'_> {
    fn type_str(&self) -> &str {
        match self {
            Token::Eof => "EOF",
            Token::Ident(_) => "IDENT",
            Token::Int(_) => "INT",
            Token::String(_) => "STRING",
            Token::Assign => "=",
            Token::LogicalAnd => "&&",
            Token::LogicalOr => "||",
            Token::Plus => "+",
            Token::Minus => "-",
            Token::LogicalNot => "!",
            Token::Mul => "*",
            Token::Div => "/",
            Token::Mod => "%",
            Token::Lt => "<",
            Token::Gt => ">",
            Token::LtEq => "<=",
            Token::GtEq => ">=",
            Token::Eq => "==",
            Token::NotEq => "!=",
            Token::And => "&",
            Token::Or => "|",
            Token::Xor => "^",
            Token::Not => "~",
            Token::LShift => "<<",
            Token::RShift => ">>",
            Token::IoRead => "<<=",
            Token::IoWrite => ">>=",
            Token::Dot => ".",
            Token::Comma => ",",
            Token::Semicolon => ";",
            Token::Colon => ":",
            Token::LParen => "(",
            Token::RParen => ")",
            Token::LBrace => "{",
            Token::RBrace => "}",
            Token::LBracket => "[",
            Token::RBracket => "]",
            Token::Function => "fn",
            Token::Let => "let",
            Token::True => "true",
            Token::False => "false",
            Token::If => "if",
            Token::Else => "else",
            Token::Return => "return",
        }
    }
}

impl Display for Token<'_> {
    fn fmt(&self, f: &mut Formatter<'_>) -> std::fmt::Result {
        match self {
            Token::Ident(literal) | Token::Int(literal) | Token::String(literal) => write!(
                f,
                "{{Type: {} Literal: {}}}",
                self.type_str(),
                String::from_utf8_lossy(literal)
            ),
            _ => write!(f, "{{Type: {} Literal: {}}}", self.type_str(), self.type_str()),
        }
    }
}

pub static KEYWORDS: phf::Map<&'static [u8], Token> = phf_map! {
    b"let" => Token::Let,
    b"fn" => Token::Function,
    b"true" => Token::True,
    b"false" => Token::False,
    b"if" => Token::If,
    b"else" => Token::Else,
    b"return" => Token::Return,
};
