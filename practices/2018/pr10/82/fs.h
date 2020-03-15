#include <string>

using std::string;

namespace Fs
{
string readTextFromFile(const string & filename);
void writeTextToFile(const string & filename, const string & text);
}