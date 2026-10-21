# QtExcel — Table Operations Practice

A C++/Qt Widgets university exercise for editing table values, sorting, searching, and calculating simple statistics.

## Features

- Resize and edit the table.
- Fill values randomly.
- Calculate minimum, maximum and average values.
- Search and sort values in ascending or descending order.

Despite its name, this is a table-widget exercise; Excel workbook import/export is not implemented in the reviewed source.

## Build on Windows

Install Visual Studio with the C++ workload and v143 toolset, an MSVC-compatible Qt installation, and Qt Visual Studio Tools.

1. Open `QtExcel.sln`.
2. Configure the installed Qt version in the project's Qt settings.
3. Select the x64 configuration, build, and run.

The project uses Qt/MSBuild integration. No CMake build configuration is included.

## Structure

`QtExcel/QtExcel.cpp` implements UI actions, `Table.cpp` manages table data, and `QtExcel.ui` defines the interface.

## License

See [CC0 1.0 Universal](LICENSE.txt).
