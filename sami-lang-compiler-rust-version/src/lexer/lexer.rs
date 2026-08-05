use crate::error::CompileError;
use crate::lexer::token::{KEYWORDS, Token};

#[derive(Debug)]
pub struct Lexer<'l> {
    input: &'l [u8],
    current_position: usize,
    read_position: usize,
    current_char: u8,
    is_eof: bool,
}

impl<'l> Lexer<'l> {
    pub fn new(input: &'l str) -> Self {
        let mut lexer = Self {
            input: input.as_bytes(),
            current_position: 0,
            read_position: 0,
            current_char: 0u8,
            is_eof: false,
        };
        lexer.read_char();

        lexer
    }

    fn read_char(&mut self) {
        if self.read_position >= self.input.len() {
            self.current_char = 0u8;
        } else {
            self.current_char = self.input[self.read_position];
        }

        self.current_position = self.read_position;
        self.read_position += 1;
    }

    fn read_span<F>(&mut self, checker: F) -> &'l [u8]
    where
        F: Fn(u8) -> bool,
    {
        let start_position = self.current_position;
        while checker(self.current_char) {
            self.read_char();
        }

        &self.input[start_position..self.current_position]
    }

    fn skip_whitespace(&mut self) {
        while Self::is_whitespace(self.current_char) {
            self.read_char()
        }
    }

    fn lookup_identifier(ident: &'l [u8]) -> Token<'l> {
        match KEYWORDS.get(ident) {
            Some(token) => token.clone(),
            None => Token::Ident(ident),
        }
    }

    fn is_letter(c: u8) -> bool {
        (b'a' <= c && c <= b'z') || (b'A' <= c && c <= b'Z') || c == b'_'
    }

    fn is_digit(c: u8) -> bool {
        b'0' <= c && c <= b'9'
    }

    fn is_whitespace(c: u8) -> bool {
        c == b' ' || c == b'\t' || c == b'\n' || c == b'\r'
    }
}

impl<'l> Iterator for Lexer<'l> {
    type Item = Result<Token<'l>, CompileError>;

    fn next(&mut self) -> Option<Self::Item> {
        if self.is_eof {
            return None;
        }

        self.skip_whitespace();

        let token = match self.current_char {
            b'=' => Token::Assign,
            b';' => Token::Semicolon,
            b'(' => Token::LParen,
            b')' => Token::RParen,
            b',' => Token::Comma,
            b'+' => Token::Plus,
            b'{' => Token::LBrace,
            b'}' => Token::RBrace,
            0u8 => Token::Eof,
            c => {
                return if Lexer::is_letter(c) {
                    let ident = self.read_span(Self::is_letter);
                    Some(Ok(Lexer::lookup_identifier(ident)))
                } else if Lexer::is_digit(c) {
                    let number = self.read_span(Self::is_digit);
                    Some(Ok(Token::Int(number)))
                } else {
                    Some(Err(CompileError::InvalidToken(char::from(c).into())))
                };
            }
        };

        if token == Token::Eof {
            self.is_eof = true;
        }

        self.read_char();
        Some(Ok(token))
    }
}
