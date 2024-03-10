#include "Config.hpp"
#include <bitset>
#include <direct.h>
#include <fstream>
#include <string>

#ifndef VERSION
#define VERSION "0.0.1"
#endif // !VERSION

#ifndef PROJECT_NAME
#define PROJECT_NAME "null"
#endif // !PROJECT_NAME

namespace Config {
argparse::ArgumentParser parser(PROJECT_NAME, VERSION,
                                argparse::default_arguments::all);
bool isUsed(Argument arg) { return parser.is_used(Arguments[arg]); }

bool parse(int argc, char const *argv[]) {
  parser.add_argument("-V", "--verbose")
      .nargs(argparse::nargs_pattern::optional)
      .scan<'i', int>()
      .default_value(0);

  parser.add_argument("-P", "--printvals")
      .help(std::string{"Print configurated values"})
      .default_value(false)
      .implicit_value(true);

  parser.add_argument("-i", "--input")
      .nargs(1)
      .default_value(std::string{"input.png"})
      .help("Input image fileName");

  parser.add_argument("-t", "--threads")
      .nargs(1)
      .default_value(8)
      .help("Number of threads that the program will use for calculations.")
      .scan<'i', int>();

  parser.add_argument("-p", "--population")
      .nargs(1)
      .default_value(8)
      .help("Size of population.")
      .scan<'i', int>();

  parser.add_argument("-s", "--shape-amount")
      .nargs(1)
      .default_value(5)
      .help("Amount of generated shapes per speciman.")
      .scan<'i', int>();

  parser.add_argument("-S", "--shape-types")
      .nargs(1)
      .default_value<unsigned int>(0b100)
      .help("Types of generated types in binary 100 - triangles 10 - ellipses "
            "1 - squares.")
      .scan<'b', unsigned int>();

  parser.add_argument("-r", "--resemblance")
      .nargs(1)
      .default_value(0.97f)
      .help("resemblance of source image at which the program will exit.")
      .scan<'g', float>();

  parser.add_argument("--hours")
      .nargs(1)
      .default_value(4.f)
      .help("hours after which the program will call it a day.")
      .scan<'g', float>();

  parser.add_argument("--scale")
      .nargs(1)
      .default_value(0.4f)
      .help("scale of shapes 1 means a shape can take the whole canvas.")
      .scan<'g', float>();

  parser.add_argument("-m", "--mutation")
      .nargs(1)
      .default_value(1.f)
      .help("scale of shapes 1 means a shape can take the whole canvas.")
      .scan<'g', float>();

  parser.add_argument("-L", "--log-to-file ")
      .nargs(argparse::nargs_pattern::optional)
      .default_value(std::string{"artGen.log"})
      .help("log to file and an optional name of file Log will be saved to");

  parser.parse_args(argc, argv);
  start_time = std::time(nullptr);
  createFolderForOutput();

  return true;
}

std::time_t start_time;
std::string out_folder_name = "./";

bool doStop() {
  return (time(nullptr) - start_time) > (int)(3600 * get<Argument::HOURS>());
}

void createFolderForOutput() {
  std::string dir =
      "./in-" + get<Argument::INPUT>() + "." + std::to_string(time(nullptr));
  struct stat st = {0};
  if (stat(dir.c_str(), &st) == -1) {
    if (_mkdir(dir.c_str()) == -1) {
      auto t = errno;
      std::cout << t;
      exit(20);
    }
  }
  std::ofstream MyFile(dir + "/info.txt");
  MyFile << "input_name: " << get<Argument::INPUT>() << std::endl
         << "thread_count: " << get<Argument::THREADS>() << std::endl
         << "population_size: " << get<Argument::POPULATION>() << std::endl
         << "shape_amount: " << get<Argument::SHAPE_AMOUNT>() << std::endl
         << "shape_types: " << std::bitset<8>(get<Argument::SHAPE_TYPES>())
         << std::endl
         << "resemblance: " << get<Argument::RESEMBLENCE>() << std::endl
         << "time_hours: " << get<Argument::HOURS>() << std::endl
         << "scale: " << get<Argument::SCALE>() << std::endl
         << "mutation rate: " << get<Argument::MUTATION>() << std::endl
         << "verbose: " << get<Argument::VERBOSE>() << std::endl
         << "verbose_level: " << get<Argument::VERBOSE>() << std::endl
         << "log_to_file: " << get<Argument::LOG>() << std::endl
         << "log_to_file_name: " << get<Argument::LOG>() << std::endl;
  MyFile.close();
  out_folder_name = dir;
}
std::string getOutputFilePathAndFileName(float resemblance) {
  return out_folder_name + "/" + std::to_string(resemblance) +
         get<Argument::INPUT>();
}
} // namespace Config
