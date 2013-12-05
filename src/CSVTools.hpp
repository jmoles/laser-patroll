#ifndef CSV_TOOLS_H

#define CSV_TOOLS_H

#include <fstream>
#include <string>

#define DEFAULT_FILE_NAME "output.csv"
#define DEFAULT_OUTPUT_MODE std::ofstream::out | std::ofstream::app


class CSVTools
{

public:
    //*! Create a new object putting data at DEFAULT_FILE_NAME
    /*! Builds a new object ready for sending results to.
     */
    CSVTools();

    //*! Create a new object putting data at filename.
    /*! Builds a new object ready for sending results to.
      \param filename name of output file.
     */
    CSVTools(std::string filename);

    //*! The default deconstructor.
    ~CSVTools();

    //*! Writes a result to the CSV file.
    /*!
      \param name name of the algorithm used.
      \param threads number of threads used on this test.
      \param size number of elements in data array.
      \param runtime time it took for the algorithm to run in seconds.
     */
    void WriteResult(std::string name, size_t threads, size_t size, double runtime);

private:

    //*! Opens file and runs a few checks.
    void OpenFile();

    //*! Used to close the file.
    void CloseFile();

    //*! The filename that data is written to.
    const std::string       file_name_;

    //*! The output stream for filename.
    std::ofstream           os_;

    //*! Variable indicating if the header has been written yet.
    bool                    header_wrote_;



};

#endif
