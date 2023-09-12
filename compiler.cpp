#include <iostream>
#include <string>
#include <vector>

enum class TokenType {
    UNKNOWN,
    KEYWORD,
    IDENTIFIER,
    LITERAL,
    OPERATOR,
    NEWLINE
};

struct Token {
    TokenType type;
    std::string value;
};

bool isWhitespace(char c) {
    return (c == ' ' || c == '\t');
}

bool isSpecialCharacter(char c) {
    return (c == ':' || c == '(' || c == ')' || c == '\n');
}

bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '/' || c == '*' || c == '=');
}

bool isKeyword(std::string word) {
    return (word == "def" || word == "print");
}

//string& is passing by reference, which is encouraged over pass by value as it prevents "slicing" problem
std::vector<Token> tokenize(const std::string& code) {
    std::vector<Token> tokens;
    std::string currentToken;
    TokenType currentTokenType = TokenType::UNKNOWN;

    for (char c : code) {
        if (isWhitespace(c) || isSpecialCharacter(c)) {
            //note 2 newline
            if (!currentToken.empty()) {
                Token token;
                token.value = currentToken;
                token.type = currentTokenType;
                if (isKeyword(currentToken)) {
                    token.type = TokenType::KEYWORD;
                }
                tokens.push_back(token);
                currentToken.clear();
                currentTokenType = TokenType::UNKNOWN;
            }
            if (c == '\n') {
                tokens.push_back({TokenType::NEWLINE, "\n"});
            }
        } else {
            if (currentToken.empty()) {
                if (isOperator(c)) {
                    currentToken += c;
                    currentTokenType = TokenType::OPERATOR;
                } else if (isalpha(c) || c == '_') {
                    currentToken += c;
                    currentTokenType = TokenType::IDENTIFIER;
                } else if (isdigit(c)) {
                    currentToken += c;
                    currentTokenType = TokenType::LITERAL;
                }
            } else {
                if ((currentTokenType == TokenType::OPERATOR && !isOperator(c)) ||
                (currentTokenType == TokenType::IDENTIFIER && !(isalpha(c) || c == '_')) ||
                (currentTokenType == TokenType::LITERAL && !isdigit(c))) {
                    Token token;
                    token.value = currentToken;
                    token.type = currentTokenType;
                    tokens.push_back(token);
                    currentToken.clear();
                    currentTokenType = TokenType::UNKNOWN;
                }
                currentToken += c;
            }
        }
    }

    if (!currentToken.empty()) {
        Token token;
        token.value = currentToken;
        token.type = currentTokenType;
        tokens.push_back(token);
    }
    return tokens;
}

int main() {
    std::string input =
    "def s():\n"
        "\tab = 1\n"
        "\tb = 2\n"
        "\tprint(ab + b)";

    std::vector<Token> tokens = tokenize(input);
    //note 5
    for (const Token& token : tokens) {
        std::cout << "Type: ";
        switch (token.type) {
            case TokenType::KEYWORD:
                std::cout << "Keyword";
                break;
            case TokenType::IDENTIFIER:
                std::cout << "Identifier";
                break;
            case TokenType::LITERAL:
                std::cout << "Literal";
                break;
            case TokenType::OPERATOR:
                std::cout << "Operator";
                break;
            case TokenType::NEWLINE:
                std::cout << "Newline";
                break;
            default:
                std::cout << "Unknown";
                break;
        }
        std::cout << ", value = " << token.value << std::endl;
    }
  
    
    return 0;
}
