# CGI-test
Simple CGI application<br>
The application should be placed in the `cgi-bin` directory of any webserver<br>
The QBS is used to build the project. Just open *.qbs* project file with *QtCreator* IDE and setup a build Kit<br>
To simplify installation process you can add `qbs.installRoot:</full/path/to/parent/dir/of/the/cgi-bin/dir>` option to *qbs* command line 
(press **Ctrl+5** in QtCreator IDE and find the *Build Steps -> Properties:* field)<br>

### Note
* To perform simple testing you can run a *python3* module: `python3 -m http.server --cgi`<br>
* The `archives` directory should be placed alongside the `cgi-bin` directory. 
* Or you can edit the sources to set preferred place for the `archives` directory (see `constants.h` and `main.cpp` for further details)