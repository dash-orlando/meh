#include <cstring>
#include <iostream>
#include <meh/logic.hpp>
#include <sys/stat.h>

using namespace meh;

int main(int argc, char *argv[]) {

  // Loop through files specified as inputs and add them to the 3MF wrapper
  if (argc > 2) {
    std::cout << "Will export file to " << argv[1] << std::endl;
    char *out;
    out = argv[1];

    char *in[argc - 2];
    char *intex[argc - 2];
    for (int i = 2; i < argc; i++) {
      std::cout << "Adding " << argv[i] << " to process list" << std::endl;
      std::string input = std::string(argv[i]);
      int splitLoc = input.rfind("+");
      std::string mesh = "";
      std::string tex = "";
      if (splitLoc != std::string::npos) {
        std::string mesh = input.substr(0, splitLoc);
        std::string tex = input.substr(splitLoc + 1, input.length());
      } else {
        std::string mesh = input;
        std::string tex = "None";
      }

      char *inFinal = new char[mesh.length() + 1];
      strcpy(inFinal, mesh.c_str());

      char *texFinal = new char[tex.length() + 1];
      strcpy(texFinal, tex.c_str());

      in[i - 2] = inFinal;
      intex[i - 2] = texFinal;

      // Check stat to see if file exists to prevent accidental overwrite
      char overwrite;
      struct stat buffer;
      if (stat(argv[1], &buffer) == 0) {
        std::cout
            << argv[1]
            << " already exists, are you sure you want to overwrite? [y/n] ";
        std::cin >> overwrite;
        if (overwrite == 'n' || overwrite == 'N') {
          std::cout << "Won't overwrite file, exiting." << std::endl;
          return 1;
        }
      }
    }

    exportModelListTo3MF(in, intex, out, argc - 2);
    return 0;
  }
  // If there are no arguments specified, print help text
  else {
    std::cout << "No model files where specified.";
    std::cout
        << "To use this tool, run meh followed by the name of the output 3mf"
        << std::endl
        << "and then the names of the files to convert to 3mf." << std::endl
        << "You can add a texture to a file by using adding a '+' and the "
           "path "
           "to the"
        << std::endl
        << "file as well. For example:" << argv[0]
        << " MyNew3MF.3mf MyFile1.obj+MyTexture1.png  MyFile2.stl etc";
    return 0;
  }
}
