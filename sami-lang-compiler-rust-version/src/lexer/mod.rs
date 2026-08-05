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
        ];

        for TestData { actual, expected } in tests {
            let lexer = Lexer::new(actual);
            let token_stream = lexer.into_iter().collect::<Vec<_>>();
            assert_eq!(token_stream, expected);
        }
    }
}