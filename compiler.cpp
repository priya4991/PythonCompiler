#include <iostream>
#include <string>
#include <vector>
#include <stack>

using namespace std;

enum class TokenType
{
    UNKNOWN,
    KEYWORD,
    IDENTIFIER,
    LITERAL,
    OPERATOR,
    NEWLINE,
    TAB
};

struct Token
{
    TokenType type;
    string value;
};

bool isWhitespace(char c)
{
    return (c == ' ');
}

bool isSpecialCharacter(char c)
{
    return (c == ':' || c == '(' || c == ')' || c == '\n' || c == '\t');
}

bool isOperator(char c)
{
    return (c == '+' || c == '-' || c == '/' || c == '*' || c == '=');
}

bool isKeyword(string word)
{
    return (word == "def" || word == "print");
}

// string& is passing by reference, which is encouraged over pass by value as it prevents "slicing" problem
vector<Token> tokenize(const string &code)
{
    vector<Token> tokens;
    string currentToken;
    TokenType currentTokenType = TokenType::UNKNOWN;

    for (char c : code)
    {
        if (isWhitespace(c) || isSpecialCharacter(c))
        {
            // note 2 newline
            if (!currentToken.empty())
            {
                Token token;
                token.value = currentToken;
                token.type = currentTokenType;
                if (isKeyword(currentToken))
                {
                    token.type = TokenType::KEYWORD;
                }
                tokens.push_back(token);
                currentToken.clear();
                currentTokenType = TokenType::UNKNOWN;
            }
            if (c == '\n')
            {
                tokens.push_back({TokenType::NEWLINE, "\n"});
            }
            else if (c == '\t')
            {
                tokens.push_back({TokenType::TAB, "\t"});
            }
        }
        else
        {
            if (currentToken.empty())
            {
                if (isOperator(c))
                {
                    currentToken += c;
                    currentTokenType = TokenType::OPERATOR;
                }
                else if (isalpha(c) || c == '_')
                {
                    currentToken += c;
                    currentTokenType = TokenType::IDENTIFIER;
                }
                else if (isdigit(c))
                {
                    currentToken += c;
                    currentTokenType = TokenType::LITERAL;
                }
            }
            else
            {
                if ((currentTokenType == TokenType::OPERATOR && !isOperator(c)) ||
                    (currentTokenType == TokenType::IDENTIFIER && !(isalpha(c) || c == '_')) ||
                    (currentTokenType == TokenType::LITERAL && !isdigit(c)))
                {
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

    // if (!currentToken.empty()) {
    //     Token token;
    //     token.value = currentToken;
    //     token.type = currentTokenType;
    //     tokens.push_back(token);
    // }
    return tokens;
}

enum class OpCode
{
    LOAD_CONST,
    STORE_FAST,
    LOAD_GLOBAL,
    LOAD_FAST,
    BINARY_ADD,
    CALL_FUNCTION,
    POP_TOP,
    RETURN_VALUE
};

struct Instruction
{
    OpCode opcode;
    string operand;
};

vector<Instruction> parse(vector<Token> &tokens)
{
    vector<Instruction> instructions;
    stack<string> operandStack;
    vector<string> identifierQueue;
    stack<string> keywordStack;

    for (const Token &token : tokens)
    {
        if (token.type == TokenType::IDENTIFIER)
        {
            if (operandStack.empty() && keywordStack.empty())
            {
                identifierQueue.push_back(token.value);
            }
            else if (!keywordStack.empty() && keywordStack.top() == "def")
            {
                keywordStack.pop();
            }
            else
            {
                // check if variables are valid or not
                string lastVariable = identifierQueue.back();
                identifierQueue.pop_back();
                if ((find(identifierQueue.begin(), identifierQueue.end(), lastVariable) == identifierQueue.end()) ||
                    find(identifierQueue.begin(), identifierQueue.end(), token.value) == identifierQueue.end())
                {
                    throw invalid_argument("Invalid argument");
                }
                /// load instructions
                instructions.push_back({OpCode::LOAD_FAST, identifierQueue.back()});
                instructions.push_back({OpCode::LOAD_FAST, token.value});
                if (operandStack.top() == "+")
                {
                    instructions.push_back({OpCode::BINARY_ADD, ""});
                    operandStack.pop();
                }
            }
        }
        else if (token.type == TokenType::OPERATOR)
        {
            operandStack.push(token.value);
        }
        else if (token.type == TokenType::LITERAL)
        {
            if (!operandStack.empty() && operandStack.top() == "=")
            {
                instructions.push_back({OpCode::LOAD_CONST, token.value});
                instructions.push_back({OpCode::STORE_FAST, identifierQueue.back()});
                operandStack.pop();
            }
        }
        else if (token.type == TokenType::KEYWORD)
        {
            if (token.value == "print")
            {
                instructions.push_back({OpCode::LOAD_GLOBAL, "print"});
            }
            else if (token.value == "def")
            {
                keywordStack.push("def");
            }
        }
    }
    return instructions;
}

int main()
{
    string input =
        "def s():\n"
        "\tab = 1\n"
        "\tb = 12\n"
        "\tprint(ab + b)\n";

    vector<Token> tokens = tokenize(input);
    // note 5
    for (const Token &token : tokens)
    {
        cout << "Type: ";
        switch (token.type)
        {
        case TokenType::KEYWORD:
            cout << "Keyword";
            break;
        case TokenType::IDENTIFIER:
            cout << "Identifier";
            break;
        case TokenType::LITERAL:
            cout << "Literal";
            break;
        case TokenType::OPERATOR:
            cout << "Operator";
            break;
        case TokenType::NEWLINE:
            cout << "Newline";
            break;
        case TokenType::TAB:
            cout << "TAB";
            break;
        default:
            cout << "Unknown";
            break;
        }
        cout << ", value = " << token.value << endl;
    }
    try
    {
        vector<Instruction> instructions = parse(tokens);

        for (const Instruction &ins : instructions)
        {
            switch (ins.opcode)
            {
            case OpCode::LOAD_CONST:
                cout << "LOAD_CONST " << ins.operand << endl;
                break;
            case OpCode::STORE_FAST:
                cout << "STORE_FAST " << ins.operand << endl;
                break;
            case OpCode::LOAD_FAST:
                cout << "LOAD_FAST " << ins.operand << endl;
                break;
            case OpCode::LOAD_GLOBAL:
                cout << "LOAD_GLOBAL " << ins.operand << endl;
                break;
            case OpCode::BINARY_ADD:
                cout << "BINARY_ADD " << endl;
            }
        }
    }
    catch (invalid_argument &e)
    {
        cerr << e.what() << endl;
        return -1;
    }

    return 0;
}
