#ifndef PW_INPUT_HPP
#define PW_INPUT_HPP

#include <unordered_set>
#include <functional>
#include <type_traits>

namespace pipeworks {
    /// \brief Represents a key being pressed
    enum class KeyCode {
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
        LetterLowerA = 'a',
        LetterLowerB = 'b',
        LetterLowerC = 'c',
        LetterLowerD = 'd',
        LetterLowerE = 'e',
        LetterLowerF = 'f',
        LetterLowerG = 'g',
        LetterLowerH = 'h',
        LetterLowerI = 'i',
        LetterLowerJ = 'j',
        LetterLowerK = 'k',
        LetterLowerL = 'l',
        LetterLowerM = 'm',
        LetterLowerN = 'n',
        LetterLowerP = 'p',
        LetterLowerQ = 'q',
        LetterLowerR = 'r',
        LetterLowerS = 's',
        LetterLowerT = 't',
        LetterLowerU = 'u',
        LetterLowerV = 'v',
        LetterLowerW = 'w',
        LetterLowerX = 'x',
        LetterLowerY = 'y',
        LetterLowerZ = 'z',
        BraceOpen = '{',
        VerticalBar = '|',
        BraceClose = '}',
        Tilda = '~',
        Delete = '\127',




        LShift = 0xff00,
        LCtrl  = 0xff01,
        LAlt   = 0xff02,
        LMeta  = 0xff03,
        RShift = 0xff04,
        RCtrl  = 0xff05,
        RAlt   = 0xff06,
        RMeta  = 0xff07,

        F1  = 0xff11,
        F2  = 0xff12,
        F3  = 0xff13,
        F4  = 0xff14,
        F5  = 0xff15,
        F6  = 0xff16,
        F7  = 0xff17,
        F8  = 0xff18,
        F9  = 0xff19,
        F10 = 0xff1a,
        F11 = 0xff1b,
        F12 = 0xff1c,


        ArrowL = 0xff20,
        ArrowR = 0xff21,
        ArrowU = 0xff22,
        ArrowD = 0xff23,
        PrnScn = 0xff24,
        Pause  = 0xff25,
        Home   = 0xff26,
        End    = 0xff27,
        Insert = 0xff28,
        PageUp = 0xff29,
        PageDwn= 0xff2a,
        

        NumpadAstrisk = 0xfe00|'*',
        NumpadPlus = 0xfe00|'+',
        NumpadComma = 0xfe00|',',
        NumpadDash = 0xfe00|'-',
        NumpadPeriod = 0xfe00|'.',
        NumpadBackslash = 0xfe00|'/',

        Numpad0 = 0xfe30,
        Numpad1 = 0xfe31,
        Numpad2 = 0xfe32,
        Numpad3 = 0xfe33,
        Numpad4 = 0xfe34,
        Numpad5 = 0xfe35,
        Numpad6 = 0xfe36,
        Numpad7 = 0xfe37,
        Numpad8 = 0xfe38,
        Numpad9 = 0xfe39,
        
    };
    class Engine;
    /// \brief A type used to access synchronous input state from the engine.
    struct InputManager{
      private:
        std::unordered_set<KeyCode> keys;
        friend class Engine;
        InputManager(Engine& e);
      public:
        /// \brief checks if the given key is pressed
        /// \param code The code to check
        /// \pre Must only be called from the Engine Thread.
        bool is_key_pressed(KeyCode code);
    };
}

#endif /*INPUT_HPP_2021_02_15_16_08_32*/
