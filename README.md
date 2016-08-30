[![Release](https://img.shields.io/badge/Release-v1.0.0-brightgreen.svg)](https://github.com/Grandbrain/SphinxQt/releases)
[![Licence](https://img.shields.io/badge/License-MIT-blue.svg)](https://github.com/Grandbrain/SphinxQt/blob/master/LICENSE)

# Welcome to SphinxQt project!

[SphinxQt](https://github.com/Grandbrain/SphinxQt) is an application for speech recognition based on CMU. The program uses third-party recognition models that are available on CMU Sphinx website. The program is based on the Qt Framework and includes binary libraries CMU Sphinx for Windows.


## Contribute

There are several ways to contribute to SphinxQt project:
* [Submit bugs](https://github.com/Grandbrain/SphinxQt/issues) and help me verify fixes.
* Review the [source code changes](https://github.com/Grandbrain/SphinxQt/pulls).


## Building

*  Download and extract the [latest release](https://github.com/Grandbrain/SphinxQt/releases) of the source code.
*  Download and install the latest version of [Qt Community](https://www.qt.io/ru/download-open-source).
*  Launch Qt Creator and open the project file "SphinxQt.pro".
*  Rebuild the project by clicking "Rebuild all" in the "Build" menu.
*  Launch the application by clicking "Run" in the "Build" menu.


## Usage

* Launch the application and select preferred microphone and sample rate from the list.
* Specify the recognition models on disk.
* Click the "Initialization" button to initialize recognition.
* Click the "Begin recognition" button to begin recognition.