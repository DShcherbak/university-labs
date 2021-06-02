#ifndef LEXER_TOKENTYPESLIST_H
#define LEXER_TOKENTYPESLIST_H

#include <stdint.h>

namespace lexer
{
    enum class TokenType : size_t
    {
        Identifier,
        DollarIdentifier,          // $
        // key words
        Include,                   // include
        Import,                   // include
        Namespace,                 // namespace
        If,
        Then,
        Else,
        Class,
        Where,
        Do,
        Case,
        Of,
        Error,
        Deriving,
        Echo,
        Print,
        //types
        Int,
        Integer,
        Bool,
        Scientific,
        Char,
        String,
        Integral,
        Ratio,
        Float,
        Fractional,
        Double,
        Complex,
        //type classes
        Eq,
        Num,
        Ord,
        Show,
        Bounded,
        Enum,
        Read,
        Monad,
        Maybe,
        Functor,
        Either,
        Ordering,
        Nothing,
        Just,
        Left,
        Right,
        LT,
        EQ,
        GT,
        //
        CharValueOneQuote,
        StringValueInTwoQuotes,
        IntValue,
        FloatValue,
        True,
        False,
        // arithmetic tokens 14
        Add,
        Sub
        ,Multi
        ,Div
        ,Mod
        ,Exp
        ,Assignment
        ,Equal
        ,NotEqualQuest
        ,NotEqualBracket
        ,GreaterThan
        ,LessThan
        ,GreaterThanEqual
        ,LessThanEqual
        ,Concat
        // logic
        ,Ampersand
        ,AndSymb
        ,OrSymb
        ,Not
        ,BitwiseOr
        ,BitwiseXor
        ,LeftShift
        ,RightShift
        ,BitwiseOrAssignment
        ,BitwiseXorAssignment
        ,LeftShiftAssignment
        ,RightShiftOrAssignment
        //special
        ,MinusLess
        ,MinusMinusLess
        ,Dot
        ,QuestMark
        ,Colon
        ,NullCoalescing
        ,ArrayKey
        ,VarReference,
        DoubleColon
        //comments
        ,SingleLineComment
        ,MultiLineComment
        , MultiLineArray,
        //punkuation
        Comma
        ,Semicolon
        ,LParen
        ,RParen
        ,LBracket
        ,RBracket
        ,LBrace
        ,RBrace
        ,Cat
        ,Dash
        , DotDotDot,
        XorWord,
        SESSION,
        This,
        WhiteSpace,
        Tab,
        INVALID,
        TOKEN_NUMBER
    };

    std::string const TokenValue[static_cast<size_t>(TokenType::TOKEN_NUMBER)] =
    {
        "Identifier", //2
        "$",                       // DollarIdentifier
        // key words
        "include",                 // Include //14
        "import",                 // Import
        "if",                      // If
        "then",                    // Else
        "else",                  // ElseIf
        "class",                // Function
        "where",                  // Return
        "do",                    // Define
        "case",                    // Static
        "of",                    // Global
        "error",                    // Global
        "deriving",                    // Global
        "echo",                      // Echo
        "print",                     // Print
        //data types cast
        "Int", //12
        "Integer",
        "Bool",
        "Scientific",
        "Char",
        "String",
        "Integral",
        "Ratio",
        "Float",
        "Fractional",
        "Double",
        "Complex",
        //type classes //19
        "Eq",
        "Num",
        "Ord",
        "Show",
        "Bounded",
        "Enum",
        "Read",
        "Monad",
        "Maybe",
        "Functor",
        "Either",
        "Ordering",
        "Nothing",
        "Just",
        "Left",
        "Right",
        "LT",
        "EQ",
        "GT",
        "StringValueOneQuote",
        "StringValueInTwoQuotes",
        "IntValue",
        "FloatValue",
        "True",
        "False",
        // arithmetic tokens 14
        "+",                        // Add
        "-",                        // Sub
        "*",                        // Multi
        "/",                        // Div
        "%",                        // Mod
        "**",                       // Exp
        "=",                        // Assignment
        "==",                       // Equal
        "/=",                       // NotEqualQuest
        "<>",                       // NotEqualBracket
        ">",                        // GreaterThan
        "<",                        // LessThan
        ">=",                       // GreaterThanEqual
        "<=",                       // LessThanEqual
        "++",                       // Concat
        // logic //14
        "&",                        // Ampersand
        "&&",                       // AndSymb
        "||",                       // OrSymb
        "!",                        // Not
        "|",                        // BitwiseOr
        "^",                        // BitwiseXor
        "<<",                       // LeftShift
        ">>",                       // RightShift
        "|=",                       // BitwiseOrAssignment
        "^=",                       // BitwiseXorAssignment
        "<<=",                      // LeftShiftAssignment
        ">>=",                      // RightShiftOrAssignment
        "-<",                      // MinusLess
        "--<",                      // MinusMinusLess
        // operations with string //7
        ".",                        // Dot
        "?",                        // QuestMark
        ":",                        // Colon
        "??",                       // NullCoalescing
        "=>",                       // ArrayKey
        "->",                       // VarReference,
        "::",                       // DoubleColon
        // comments 4
        "--",                       // SingleLineComment
        "{- -}",                    // MultiLineComment
        "[|, |]",                    // MultiLineArray
        // punctuation 12
        ",",                        // Comma
        ";",                        // Semicolon
        "(",                        // LParen
        ")",                        // RParen
        "[",                        // LBracket
        "]",                        // RBracket
        "{",                        // LBrace
        "}",                        // RBrace
        "@",                        // Cat
        "_",                        // Dash
        "...",                        // DotDotDot
        "xor",                        // DotDotDot
        "_SESSION",                        // DotDotDot
        "this",                        // DotDotDot
        " ",
        "\t"
        "INVALID"
    };





/*
26 |
27 ~
28 as
29 case, of
30 class
31 data
32 data family
33 data instance
34 default
35 deriving
36 deriving instance
37 do
38 forall
39 foreign
40 hiding
41 if, then, else
42 import
43 infix, infixl, infixr
44 instance
45 let, in
46 mdo
47 module
48 newtype
49 proc
50 qualified
51 rec
52 type
53 type family
54 type instance
55 where
*/
}

#endif //LEXER_TOKENTYPESLIST_H
