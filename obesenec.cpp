#include<iostream>
#include<iomanip>
#include<algorithm>
#include<string>
#include<limits>
#undef max

class Hangman
{
private:
    std::string wordName{ "0" }, wordHint{ "0" }, answer{ "" }, wordType{ "0" }, hanged[5]{ "Adam","Boris","Dominik","Fero","Jozko" };
    std::string keyboard = "\t\t  ___________________________________  \n"
        "\t\t |             KLAVESNICA            | \n"
        "\t\t |-----------------------------------| \n"
        "\t\t | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | \n"
        "\t\t |-----------------------------------| \n"
        "\t\t | a | b | c | d | e | f | g | h | i | \n"
        "\t\t |-----------------------------------| \n"
        "\t\t | j | k | l | m | n | o | p | q | r | \n"
        "\t\t |-----------------------------------| \n"
        "\t\t | s | t | u | v | w | x | y | z | 0 | \n"
        "\t\t |-----------------------------------| \n"
        "\t\t |___________________________________| \n";
    int countHang{ 0 }; 
    char ch{ 0 }; 
    bool active{ 1 }, flag{ 1 }, tag{ 1 };  

public:

    bool exit{ 0 }; 

    Hangman() {

        active = 1;
        while (active) {

            std::cout << "\t\t  ____________________________________  \n"
                "\t\t |              Hlavne menu           | \n"
                "\t\t |             -----------            | \n"
                "\t\t |     --XX---            ---XX--     | \n"
                "\t\t |       :      ~Obesenec~    :       | \n"
                "\t\t |       :                    :       | \n"
                "\t\t |       O      1.  Hrat      O       | \n"
                "\t\t |      /|\\                  /|\\      | \n"
                "\t\t |      / \\   2.  Pravidla   / \\      | \n"
                "\t\t |                                    | \n"
                "\t\t |              3.  Koniec            | \n"
                "\t\t |____________________________________| \n\n\n"


                "\t\t            -->";
            std::cin >> ch; 
            if (ch == '1') {
                active = 0;
                system("cls");
                HintWord();
            }
            else if (ch == '2') {
                active = 0;
                system("cls");
                Rules();
            }
            else if (ch == '3') {
                system("cls");
                active = 0;
                exit = 1;
            }
            else {
                system("cls");
            }
        }
    };

    inline void Rules() {

        std::cout << "\n\n\t\t                                        ~VYTAJ~                                            \n"
            "\n\n\t\t  ------------------------------------------------------------------------------------------ \n"
            "\n\n\t\t  (1) Vyberte si jednu osobu, ktora bude hostitelom. Toto je osoba, ktora vymysli slovo,           \n"
            "\t\t  ktore ma druha osoba vyriesit (uhadnut). Za ulohu dostanu vyber slova, ktore budu musiet „hraci“ vyriesit. \n"
            "\t\t  Hrac by mal pomocou nápoved vyriesit slovo, inak nebude mozne hru vyhrat.        \n\n"
            "\t\t  (2) Ak ste hostitelom, zvolte tajne slovo. Ostatni hraci budu musiet uhádnut vase    \n"
            "\t\t  slovo po pismene, takze si vyberte slovo, o ktorom si myslite, ze ho bude tazke uhadnut. Tazke    \n"
            "\t\t  slova maju zvycajne neobvykle pismena, napriklad „z“ alebo „j“, a iba niekolko samohlasok.             \n\n"
            "\t\t  (3) Ak ste hracom, zacnite hadat pismena. Po vybere slova a hraci vedia     \n"
            "\t\t  kolko pismen v tajnom slove, zacnite hrat zadanim ktorych pismen su v slove.  \n"
            "\t\t  (4) Kedykolvek hraci uhadnu pismeno, ktore nie je v tajnom slove, dostanu strajk    \n"
            "\t\t  cim sa priblizuju k stratam. Aby to bolo viditelne, hra nakresli jednoducheho panacika (figurku)  \n"
            "\t\t                                    *** 1.  Pod spat.                                         \n"
            "\t\t  ------------------------------------------------------------------------------------------ \n"
            "\t\t                                     -->";
        std::cin >> ch;
        if (ch == '1') {
            active = 0;
            system("cls");
            Hangman();
        }
        else {
            system("cls");
        }
    }


    inline void HintWord() {
        std::cout << "\t\t            ______                     \n"
            "\t\t           |      |                    \n"
            "\t\t           |      :                    \n"
            "\t\t           |                           \n"
            "\t\t           |          \\ O    O       \n"
            "\t\t           |           |\\   /|7       \n"
            "\t\t        ___|___       / \\   / \\      \n";

        std::cout << "\n\n\t\t *** Hostitel, zadajte hladane tajne slovo:  \t\t (*) HRACI SA NEPOZERAJU NA TUTO OBRAZOVKU !!\n"

            "\t\t               --> ";
        std::cin >> wordName;
        std::transform(wordName.begin(), wordName.end(), wordName.begin(), tolower);  
        std::cout << std::endl;
        std::cout << "\t\t *** Zadajte typ slova, napriklad Film, Jedlo/pitie, Skladba, Meno, Zviera atď: \n"

            "\t\t               --> ";

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::getline(std::cin, wordType);
        std::cout << std::endl;
        std::cout << "\t\t *** Zadajte napovedu:                          \n"

            "\t\t               --> ";

        std::getline(std::cin, wordHint);

        for (unsigned i = 0; i < wordName.length(); ++i)
            answer += "_";


        system("cls");
        HangBoard();

    }

    inline void HangBoard() {

        int i = 0;
        active = 1;

        while (active) {
            HangCheck();
            std::cout << "\t\t ~TYP~ \"" << wordType << "\"\t\t  ";
            for (unsigned i = 0; i < wordName.length(); ++i) {

                std::cout << answer[i] << " ";
            }
            std::cout << "\n\n\t\t ~NAPOVEDA~ \"" << wordHint << "\"\n\n";
            std::cout << "\t\t\t\t\t\t\t (*) '#' Zobrazene na klavesnici znamena, ze uz je vyskusane.";
            std::cout << "\t\t\t\t\t\t\t\t (*)  Enter '.' odosle zadany znak.";
            std::cout << "\n\n" << keyboard;

            if (flag == 1) {


                std::cout << "\t\t     ~X~ -->"; std::cin >> ch;
            }
            else {
                std::cout << "\t\t ;)  ~O~ -->"; std::cin >> ch;
            }

            if (ch == '.') {
                system("cls");
                Hangman();
                active = 0;
                break;
            }
            if (ch <= 90 && ch >= 65)
                ch += 32;

            if (ch != '|' && ch != '_' && ch != '-' && keyboard.find(ch) != std::string::npos)
                keyboard[keyboard.find(ch)] = '#';

            if (ch != '#')
                tag = 0;

            if (ch == '#' && flag == 1 && tag == 1) {
                ch = wordName[0];
                flag = 0;
            }

            i = wordName.find(ch);
            while (wordName.find(ch, i) != std::string::npos) {

                answer[wordName.find(ch, i)] = ch;
                i++;
            }
            if (wordName.find(ch) == std::string::npos) {
                countHang++;
                std::cout << "\a";
            }
            if (countHang == 6) {
                system("cls");
                AgainMenu();
            }
            else if (answer == wordName) {
                system("cls");
                AgainMenu();
            }
            system("cls");
        }
    }
    inline void AgainMenu() {
        active = 1;
        while (active) {
            if (countHang == 6) {

                std::cout << "\t\t  ____________________________________  \n"
                    "\t\t |             " << std::setw(5) << hanged[rand() % 5] << " ZOMREL   !       | \n"
                    "\t\t |             -----------            | \n"
                    "\t\t |              ( X _ X )             | \n"
                    "\t\t |                                    | \n"
                    "\t\t |                       ________     | \n"
                    "\t\t |                      / Nieee!!!\\   | \n"
                    "\t\t |       _____          \\  ______/    | \n"
                    "\t\t |      (     )     <O>  \\/           | \n"
                    "\t\t |      | RIP |      |                | \n"
                    "\t\t |      |_____|     <<                | \n"
                    "\t\t |   ------------------------------   | \n"
                    "\t\t |                                    | \n"
                    "\t\t |          1.  Hrat znovu            | \n"
                    "\t\t |                                    | \n"
                    "\t\t |          2.  Odist                 | \n"
                    "\t\t |____________________________________| \n\n\n";
            }
            else {
                std::cout << "\t\t  ____________________________________  \n"
                    "\t\t |            " << std::setw(5) << hanged[rand() % 5] << " ZIJE!             | \n"
                    "\t\t |             -----------            | \n"
                    "\t\t |           ________                 | \n"
                    "\t\t |          / ZIJEM! \\                | \n"
                    "\t\t |          \\  ______/                | \n"
                    "\t\t |            \\/                      | \n"
                    "\t\t |        |O/                         | \n"
                    "\t\t |         |                          | \n"
                    "\t\t |        / >                         | \n"
                    "\t\t |      _____       \\O>   \\O/         | \n"
                    "\t\t |     /     \\       |     |          | \n"
                    "\t\t |    /       \\     < \\   / \\         | \n"
                    "\t\t |   ------------------------------   | \n"
                    "\t\t |                                    | \n"
                    "\t\t |          1.  Hrat znovu            | \n"
                    "\t\t |                                    | \n"
                    "\t\t |          2.  Odist                 | \n"
                    "\t\t |____________________________________| \n\n\n";
            }
            std::cout << "\t\t            -->";
            std::cin >> ch;
            if (ch == '1') {
                active = 0;

                system("cls");
                countHang = 0;
                flag = 1;
                tag = 1;
                wordName = "0";
                wordHint = "0";
                answer = "";
                wordType = "0";

                keyboard = "\t\t  ___________________________________  \n"
                    "\t\t |             KLAVESNICA            | \n"
                    "\t\t |-----------------------------------| \n"
                    "\t\t | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | \n"
                    "\t\t |-----------------------------------| \n"
                    "\t\t | a | b | c | d | e | f | g | h | i | \n"
                    "\t\t |-----------------------------------| \n"
                    "\t\t | j | k | l | m | n | o | p | q | r | \n"
                    "\t\t |-----------------------------------| \n"
                    "\t\t | s | t | u | v | w | x | y | z | 0 | \n"
                    "\t\t |-----------------------------------| \n"
                    "\t\t |___________________________________| \n";
                HintWord();
            }
            else if (ch == '2') {
                system("cls");
                active = 0;
                exit = 1;
            }
            else {
                system("cls");
            }
        }
    }

    inline void HangCheck() {

        if (countHang == 0) {
            std::cout << "\t\t     ______                     \n"
                "\t\t    |      |                    \n"
                "\t\t    |      :                    \n"
                "\t\t    |                           \n"
                "\t\t    |                           \n"
                "\t\t    |                           \n"
                "\t\t ___|___                        \n\n\n";
        }
        else if (countHang == 1) {
            std::cout << "\t\t     ______                     \n"
                "\t\t    |      |                    \n"
                "\t\t    |      :                    \n"
                "\t\t    |      O                    \n"
                "\t\t    |                           \n"
                "\t\t    |                           \n"
                "\t\t ___|___                        \n\n\n";
        }
        else if (countHang == 2) {
            std::cout << "\t\t     ______                     \n"
                "\t\t    |      |                    \n"
                "\t\t    |      :                    \n"
                "\t\t    |      O                    \n"
                "\t\t    |      |                    \n"
                "\t\t    |                           \n"
                "\t\t ___|___                        \n\n\n";
        }
        else if (countHang == 3) {
            std::cout << "\t\t     ______                     \n"
                "\t\t    |      |                    \n"
                "\t\t    |      :                    \n"
                "\t\t    |      O                    \n"
                "\t\t    |      |\\                  \n"
                "\t\t    |                           \n"
                "\t\t ___|___                        \n\n\n";
        }
        else if (countHang == 4) {
            std::cout << "\t\t     ______                     \n"
                "\t\t    |      |                    \n"
                "\t\t    |      :                    \n"
                "\t\t    |      O                    \n"
                "\t\t    |     /|\\                  \n"
                "\t\t    |                           \n"
                "\t\t ___|___                        \n\n\n";
        }
        else if (countHang == 5) {
            std::cout << "\t\t     ______                     \n"
                "\t\t    |      |                    \n"
                "\t\t    |      :                    \n"
                "\t\t    |      O                    \n"
                "\t\t    |     /|\\                  \n"
                "\t\t    |     /                     \n"
                "\t\t ___|___                        \n\n\n";
        }
        else if (countHang == 6) {
            std::cout << "\t\t     ______                     \n"
                "\t\t    |      |                    \n"
                "\t\t    |      :                    \n"
                "\t\t    |      O                    \n"
                "\t\t    |     /|\\                  \n"
                "\t\t    |     / \\                  \n"
                "\t\t ___|___                        \n\n\n";
        }
    }
};

int main() {

    std::ios::sync_with_stdio(0);

    Hangman game;
    if (game.exit == 1) return 0;

    std::cin.get();
    return 0;
}