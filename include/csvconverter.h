#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

/**
 * Read a csv and save data to vector of vectors of doubles.
 *
 * @param filename The name of the file to load.
 * @param header The number of header lines to skip.
 * @return a vector of vectors of doubles. Each internal vector represents a
 * column.
 *
 */

// this was provided to us by a tutor for the course ESP II
// shout out to A. Orione

std::vector<std::vector<double>> csvReaderToDouble(std::string filename, int header) {
  std::vector<std::vector<double>> output;
  // Open the file
  std::ifstream in(filename);
  std::string line;

  // Skip the header lines
  for (int i = 0; i < header; i++)
    getline(in, line);

  bool firstLine = true;
  int columnCounter = 0;
  while (getline(in, line)) {
    std::stringstream lineStream(line);
    std::string cell;

    // Initialize the vector with the columns
    if (firstLine) {
      while (getline(lineStream, cell, ',')) {
        output.push_back(std::vector<double>());
        output[columnCounter].push_back(stod(cell));
        columnCounter++;
      }
      firstLine = false;
      continue;
    }

    int columnIndex = 0;
    while (getline(lineStream, cell, ',')) {
      output[columnIndex].push_back(stod(cell));
      columnIndex++;
    }
  }

  return output;
}
