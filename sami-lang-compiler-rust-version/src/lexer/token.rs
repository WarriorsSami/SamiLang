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
    Comma,
    Semicolon,
    Colon,
    LParen,
    RParen,
    LBrace,
    RBrace,
    LBracket,
    RBracket,
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
    b"true" => Token::True,
    b"false" => Token::False,
    b"if" => Token::If,
    b"else" => Token::Else,
    b"return" => Token::Return,
};
