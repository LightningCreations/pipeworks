#ifndef INPUT_HPP_2021_02_15_16_08_32
#define INPUT_HPP_2021_02_15_16_08_32

#include <unordered_set>
#include <functional>
#include <type_traits>

namespace pipeworks{
    enum class KeyCode{
        Backspace = '\010',
        Tab = '\t',
        Enter = '\n',
        Return = '\r',
        Escape = '\x1b',
        Space = ' ',
        Bang = '!',
        Quote = '"',
        Pound = '#',
        Dolar = '$',
        Percent = '%',
        Amp = '&',
        SingleQuote ='\'',
        OpenParen = '(',
        CloseParen = ')',
        Astrisk = '*',
        Plus = '+',
        Comma = ',',
        Dash = '-',
        Period = '.',
        Backslash = '/',
        Num0 = '0',
        Num1 = '1',
        Num2 = '2',
        Num3 = '3',
        Num4 = '4',
        Num5 = '5',
        Num6 = '6',
        Num7 = '7',
        Num8 = '8',
        Num9 = '9',
        Colon = ':',
        Semicolon = ';',
        LessThan = '<',
        Equals = '=',
        GreaterThan = '>',
        QuestionMark = '?',
        At = '@',
        LetterA = 'A',
        LetterB = 'B',
        LetterC = 'C',
        LetterD = 'D',
        LetterE = 'E',
        LetterF = 'F',
        LetterG = 'G',
        LetterH = 'H',
        LetterI = 'I',
        LetterJ = 'J',
        LetterK = 'K',
        LetterL = 'L',
        LetterM = 'M',
        LetterN = 'N',
        LetterP = 'P',
        LetterQ = 'Q',
        LetterR = 'R',
        LetterS = 'S',
        LetterT = 'T',
        LetterU = 'U',
        LetterV = 'V',
        LetterW = 'W',
        LetterX = 'X',
        LetterY = 'Y',
        LetterZ = 'Z',
        BracketOpen = '[',
        ForwardSlash = '\\',
        BracketClose = ']',
        Caret = '^',
        Underscore = '_',
        Backtick = '`',
        BraceOpen = '{',
        VerticalBar = '|',
        BraceClose = '}',
        Tilda = '~',
        Delete = '\127'
    };
    class Engine;
    /**
     * \brief A type used to access synchronous input state from the engine.
     */
    struct InputManager{
    private:
        std::unordered_set<KeyCode> keys;
        friend class Engine;
        InputManager(Engine& e);
    public:
        /**
         * \brief checks if the given key is pressed
         * 
         * \pre Must only be called from the Engine Thread. 
         */ 
        bool key_pressed(KeyCode code);
    };
}

#endif /*INPUT_HPP_2021_02_15_16_08_32*/