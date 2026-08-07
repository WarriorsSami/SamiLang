mod lexer;
mod token;
mod error;

pub use lexer::Lexer;

#[cfg(test)]
mod lexer_tests {
    use crate::lexer::error::LexError;
    use crate::lexer::Lexer;
    use crate::lexer::token::Token;
    use pretty_assertions::assert_eq;

    #[test]
    fn lex_valid_input() {
        let input = r#"=+(){},;
let five = 5;
let ten = 10;

let add = fn(x, y) {
    x + y;
};

let result = add(five, ten);
!-/*%5;
5 < 10 > 5;

let myArray = [1, 2, 3, 4, 5];
myArray[0]

let thorsten = {"name": "Thorsten", "age": 28};
thorsten["name"]

let _str = "\thello, world!\n";

if 5 < 10 {
    return true;
} else {
    return false;
}

10 == 10;
10 != 9;
10 <= 11;
11 >= 10;

1 & 1
1 | 0
1 ^ 1
~1
1 << 3
1 >> 3

true && true
true || false
!true

let x, y <<= io.read("%d, %d");
x, y >>= io.write("%d, %d");
"#;
        let expected_token_stream = vec![
            Token::Assign,
            Token::Plus,
            Token::LParen,
            Token::RParen,
            Token::LBrace,
            Token::RBrace,
            Token::Comma,
            Token::Semicolon,
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
            Token::LogicalNot,
            Token::Minus,
            Token::Div,
            Token::Mul,
            Token::Mod,
            Token::Int("5".as_bytes()),
            Token::Semicolon,
            Token::Int("5".as_bytes()),
            Token::Lt,
            Token::Int("10".as_bytes()),
            Token::Gt,
            Token::Int("5".as_bytes()),
            Token::Semicolon,
            Token::Let,
            Token::Ident("myArray".as_bytes()),
            Token::Assign,
            Token::LBracket,
            Token::Int("1".as_bytes()),
            Token::Comma,
            Token::Int("2".as_bytes()),
            Token::Comma,
            Token::Int("3".as_bytes()),
            Token::Comma,
            Token::Int("4".as_bytes()),
            Token::Comma,
            Token::Int("5".as_bytes()),
            Token::RBracket,
            Token::Semicolon,
            Token::Ident("myArray".as_bytes()),
            Token::LBracket,
            Token::Int("0".as_bytes()),
            Token::RBracket,
            Token::Let,
            Token::Ident("thorsten".as_bytes()),
            Token::Assign,
            Token::LBrace,
            Token::String("name".as_bytes()),
            Token::Colon,
            Token::String("Thorsten".as_bytes()),
            Token::Comma,
            Token::String("age".as_bytes()),
            Token::Colon,
            Token::Int("28".as_bytes()),
            Token::RBrace,
            Token::Semicolon,
            Token::Ident("thorsten".as_bytes()),
            Token::LBracket,
            Token::String("name".as_bytes()),
            Token::RBracket,
            Token::Let,
            Token::Ident("_str".as_bytes()),
            Token::Assign,
            Token::String(r#"\thello, world!\n"#.as_bytes()),
            Token::Semicolon,
            Token::If,
            Token::Int("5".as_bytes()),
            Token::Lt,
            Token::Int("10".as_bytes()),
            Token::LBrace,
            Token::Return,
            Token::True,
            Token::Semicolon,
            Token::RBrace,
            Token::Else,
            Token::LBrace,
            Token::Return,
            Token::False,
            Token::Semicolon,
            Token::RBrace,
            Token::Int("10".as_bytes()),
            Token::Eq,
            Token::Int("10".as_bytes()),
            Token::Semicolon,
            Token::Int("10".as_bytes()),
            Token::NotEq,
            Token::Int("9".as_bytes()),
            Token::Semicolon,
            Token::Int("10".as_bytes()),
            Token::LtEq,
            Token::Int("11".as_bytes()),
            Token::Semicolon,
            Token::Int("11".as_bytes()),
            Token::GtEq,
            Token::Int("10".as_bytes()),
            Token::Semicolon,
            Token::Int("1".as_bytes()),
            Token::And,
            Token::Int("1".as_bytes()),
            Token::Int("1".as_bytes()),
            Token::Or,
            Token::Int("0".as_bytes()),
            Token::Int("1".as_bytes()),
            Token::Xor,
            Token::Int("1".as_bytes()),
            Token::Not,
            Token::Int("1".as_bytes()),
            Token::Int("1".as_bytes()),
            Token::LShift,
            Token::Int("3".as_bytes()),
            Token::Int("1".as_bytes()),
            Token::RShift,
            Token::Int("3".as_bytes()),
            Token::True,
            Token::LogicalAnd,
            Token::True,
            Token::True,
            Token::LogicalOr,
            Token::False,
            Token::LogicalNot,
            Token::True,
            Token::Let,
            Token::Ident("x".as_bytes()),
            Token::Comma,
            Token::Ident("y".as_bytes()),
            Token::IoRead,
            Token::Ident("io".as_bytes()),
            Token::Dot,
            Token::Ident("read".as_bytes()),
            Token::LParen,
            Token::String("%d, %d".as_bytes()),
            Token::RParen,
            Token::Semicolon,
            Token::Ident("x".as_bytes()),
            Token::Comma,
            Token::Ident("y".as_bytes()),
            Token::IoWrite,
            Token::Ident("io".as_bytes()),
            Token::Dot,
            Token::Ident("write".as_bytes()),
            Token::LParen,
            Token::String("%d, %d".as_bytes()),
            Token::RParen,
            Token::Semicolon,
            Token::Eof,
        ];

        let lexer = Lexer::new(input);
        let token_stream = lexer.into_iter().collect::<Result<Vec<_>, _>>();
        match token_stream {
            Ok(token_stream) => assert_eq!(token_stream, expected_token_stream),
            Err(err) => panic!("{err}"),
        };
    }

    #[test]
    fn lex_invalid_token() {
        let input = r#"let v @ 1;"#;

        let lexer = Lexer::new(input);
        let token_stream = lexer.into_iter().collect::<Result<Vec<_>, _>>();
        match token_stream {
            Ok(_) => panic!("test should fail due to: invalid token `@` encountered"),
            Err(err) => assert_eq!(err, LexError::InvalidToken('@')),
        };
    }

    #[test]
    fn lex_unterminated_string() {
        let input = r#"let name = "sami;"#;

        let lexer = Lexer::new(input);
        let token_stream = lexer.into_iter().collect::<Result<Vec<_>, _>>();
        match token_stream {
            Ok(_) => panic!(
                r#"test should fail due to: no matching closing quote found for string "sami""#
            ),
            Err(err) => assert_eq!(err, LexError::UnterminatedString("sami".into())),
        };
    }

    #[test]
    fn lex_invalid_escape() {
        let input = r#"let name = "sami\y";"#;

        let lexer = Lexer::new(input);
        let token_stream = lexer.into_iter().collect::<Result<Vec<_>, _>>();
        match token_stream {
            Ok(_) => panic!(
                r#"test should fail due to: invalid escape character `y` encountered in string "sami""#
            ),
            Err(err) => assert_eq!(err, LexError::InvalidEscape('y', "sami".into())),
        };
    }
}
