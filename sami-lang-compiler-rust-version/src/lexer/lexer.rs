use crate::lexer::token::Token;

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
}

impl<'l> Iterator for Lexer<'l> {
    type Item = Token<'l>;

    fn next(&mut self) -> Option<Self::Item> {
        if self.is_eof {
            return None;
        }

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
            _ => todo!(),
        };

        if token == Token::Eof {
            self.is_eof = true;
        }

        self.read_char();
        Some(token)
    }
}
