#include <iostream>

#include "Lexer.h"
#include "Tests.h"

using namespace std;

int main(int argc, char* argv[])
{
    string help_message ="\
    -f, --file      - enter input file\n\
    -h, --help      - print this message\n\
    -t, --test      - run tests\n\
";

    if(argc < 2)
        cout << help_message << endl;

    for(int i = 1; i < argc; i++)
    {
        string parameter = argv[i];	// next parameter

		// help message
        if( parameter == "-h" || parameter == "--help" )
            cout << help_message << endl;
        else if( parameter == "-t" || parameter == "--test" )
        {
            Tests tests;
            tests.TestAll();
        }
        else if( parameter == "-f" || parameter == "--file" )
        {
            if( argc > i+1 )
			{
				string file_name = argv[i+1]; // string with entered parameter value

                // Log file
                ofstream log;

                log.open("lexer.log", ios_base::app);

                // Tokens stream
                TokensFileStream tokens("tokens_stream");

                fstream input_file;
                input_file.open(file_name);

                iostream* stream = &input_file;

                Lexer lexer(stream, &tokens, &log);

                lexer.AnalizeInput();

                input_file.close();
                log.close();

                i++; // skip parameter value
			}
			else
                cerr << "There is not file name entered!" << endl;
        }
    }

    return 0;
}
