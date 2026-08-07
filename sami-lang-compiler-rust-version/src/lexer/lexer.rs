use crate::lexer::error::LexError;
use crate::lexer::token::{KEYWORDS, Token};

// TODO: add line numbers and file names to easily report errors context
// TODO: replace manual indexing with CharIndices, Peekable<Chars> or other char iterators without trading away reference

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

    fn read_chars(&mut self, count: usize) {
        for _ in 0..count {
            self.read_char();
        }
    }

    fn peek_char(&self, offset: usize) -> u8 {
        if self.read_position + offset >= self.input.len() {
            0u8
        } else {
            self.input[self.read_position + offset]
        }
    }

    fn is_input_stream_empty(&self) -> bool {
        self.read_position >= self.input.len()
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

    fn read_str(&mut self) -> Result<&'l [u8], LexError> {
        // advance one more position to consume the opening string quote
        self.read_char();

        let start_position = self.current_position;
        while self.can_read_str_literal(start_position, self.current_char)? {
            self.read_char();
        }
        let str_literal = &self.input[start_position..self.current_position];

        // advance one more position to consume the closing string quote
        self.read_char();

        Ok(str_literal)
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

    fn can_read_str_literal(&mut self, start_str_position: usize, c: u8) -> Result<bool, LexError> {
        if Self::is_str_quote(c) {
            Ok(false)
        } else if Self::is_escape(c) {
            let str_bytes_so_far = &self.input[start_str_position..self.current_position];
            self.read_char();
            // SAFETY: the bytes lexed so far from the input are guaranteed to be ASCII, thus UTF8-valid
            let str_so_far = unsafe { String::from_utf8_unchecked(str_bytes_so_far.to_vec()) };

            if self.is_input_stream_empty() {
                Err(LexError::UnterminatedString(str_so_far))
            } else if !Self::is_escapable(self.current_char) {
                Err(LexError::InvalidEscape(char::from(self.current_char), str_so_far))
            } else {
                Ok(true)
            }
        } else if self.is_input_stream_empty() {
            let str_bytes_so_far = &self.input[start_str_position..self.current_position];
            // SAFETY: the bytes lexed so far from the input are guaranteed to be ASCII, thus UTF8-valid
            let str_so_far = unsafe { String::from_utf8_unchecked(str_bytes_so_far.to_vec()) };

            Err(LexError::UnterminatedString(str_so_far))
        } else {
            Ok(true)
        }
    }

    fn is_str_quote(c: u8) -> bool {
        c == b'"'
    }

    fn is_escape(c: u8) -> bool {
        c == b'\\'
    }

    fn is_escapable(c: u8) -> bool {
        c == b'n' || c == b't' || c == b'"' || c == b'\\'
    }
}

impl<'l> Iterator for Lexer<'l> {
    type Item = Result<Token<'l>, LexError>;

    fn next(&mut self) -> Option<Self::Item> {
        if self.is_eof {
            return None;
        }

        self.skip_whitespace();

        let token = match self.current_char {
            b',' => Token::Comma,
            b';' => Token::Semicolon,
            b':' => Token::Colon,
            b'(' => Token::LParen,
            b')' => Token::RParen,
            b'{' => Token::LBrace,
            b'}' => Token::RBrace,
            b'[' => Token::LBracket,
            b']' => Token::RBracket,
            b'=' => match self.peek_char(0) {
                b'=' => {
                    self.read_char();
                    Token::Eq
                }
                _ => Token::Assign,
            },
            b'&' => match self.peek_char(0) {
                b'&' => {
                    self.read_char();
                    Token::LogicalAnd
                },
                _ => Token::And,
            },
            b'|' => match self.peek_char(0) {
                b'|' => {
                    self.read_char();
                    Token::LogicalOr
                },
                _ => Token::Or,
            },
            b'^' => Token::Xor,
            b'~' => Token::Not,
            b'+' => Token::Plus,
            b'-' => Token::Minus,
            b'!' => match self.peek_char(0) {
                b'=' => {
                    self.read_char();
                    Token::NotEq
                }
                _ => Token::LogicalNot,
            },
            b'*' => Token::Mul,
            b'/' => Token::Div,
            b'%' => Token::Mod,
            b'<' => match (self.peek_char(0), self.peek_char(1)) {
                (b'<', b'=') => {
                    self.read_chars(2);
                    Token::IoRead
                }
                (b'<', _) => {
                    self.read_char();
                    Token::LShift
                }
                (b'=', _) => {
                    self.read_char();
                    Token::LtEq
                }
                _ => Token::Lt,
            },
            b'>' => match (self.peek_char(0), self.peek_char(1)) {
                (b'>', b'=') => {
                    self.read_chars(2);
                    Token::IoWrite
                }
                (b'>', _) => {
                    self.read_char();
                    Token::RShift
                }
                (b'=', _) => {
                    self.read_char();
                    Token::GtEq
                }
                _ => Token::Gt,
            },
            b'.' => Token::Dot,
            0u8 => Token::Eof,
            c => {
                // if identifier or literal, just return right away as there is no need to keep
                // advancing the lex iterator 'cause it's already been done
                return if Lexer::is_letter(c) {
                    let ident = self.read_span(Self::is_letter);
                    Some(Ok(Lexer::lookup_identifier(ident)))
                } else if Lexer::is_digit(c) {
                    let number = self.read_span(Self::is_digit);
                    Some(Ok(Token::Int(number)))
                } else if Lexer::is_str_quote(c) {
                    match self.read_str() {
                        Ok(str) => Some(Ok(Token::String(str))),
                        Err(err) => Some(Err(err)),
                    }
                } else {
                    Some(Err(LexError::InvalidToken(char::from(c))))
                };
            }
        };

        self.is_eof = self.is_input_stream_empty();

        self.read_char();
        Some(Ok(token))
    }
}
