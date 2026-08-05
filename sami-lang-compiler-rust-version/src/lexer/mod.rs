mod lexer;
pub mod token;

pub use lexer::Lexer;

#[cfg(test)]
mod lexer_tests {
    use crate::lexer::Lexer;
    use crate::lexer::token::Token;
    use pretty_assertions::assert_eq;

    struct TestData<A, E> {
        actual: A,
        expected: E,
    }

    #[test]
    fn lexer_scan_test() {
        let tests = vec![
            TestData {
                actual: "=+(){},;",
                expected: vec![
                    Token::Assign,
                    Token::Plus,
                    Token::LParen,
                    Token::RParen,
                    Token::LBrace,
                    Token::RBrace,
                    Token::Comma,
                    Token::Semicolon,
                    Token::Eof,
                ],
            },
            TestData {
                actual: r"let five = 5;
let ten = 10;

let add = fn(x, y) {
    x + y;
};

let result = add(five, ten);
",
                expected: vec![
                    Token::Let,
                    Token::Ident("five".as_bytes()),
                    Token::Assign,
                    Token::Int("5".as_bytes()),
                    Token::Semicolon,
                    Token::Let,
                    Token::Ident("ten".as_bytes()),
                    Token::Assign,
                    Token::Int("10".as_bytes()),
                    Token::Semicolon,
                    Token::Let,
                    Token::Ident("add".as_bytes()),
                    Token::Assign,
                    Token::Function,
                    Token::LParen,
                    Token::Ident("x".as_bytes()),
                    Token::Comma,
                    Token::Ident("y".as_bytes()),
                    Token::RParen,
                    Token::LBrace,
                    Token::Ident("x".as_bytes()),
                    Token::Plus,
                    Token::Ident("y".as_bytes()),
                    Token::Semicolon,
                    Token::RBrace,
                    Token::Semicolon,
                    Token::Let,
                    Token::Ident("result".as_bytes()),
                    Token::Assign,
                    Token::Ident("add".as_bytes()),
                    Token::LParen,
                    Token::Ident("five".as_bytes()),
                    Token::Comma,
                    Token::Ident("ten".as_bytes()),
                    Token::RParen,
                    Token::Semicolon,
                    Token::Eof,
                ],
            },
        ];

        for TestData { actual, expected } in tests {
            let lexer = Lexer::new(actual);
            let token_stream = lexer.into_iter().collect::<Result<Vec<_>, _>>();
            match token_stream {
                Ok(token_stream) => assert_eq!(token_stream, expected),
                Err(err) => panic!("{err}"),
            };
        }
    }
}
