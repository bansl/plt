# PLT

## Installation

1. Download latest release
2. install texlive and some dependencies: `apt-get install texlive texlive-math-extra texlive-science texlive-latex-extra texlive-lang-french`
3. cd into build folder
4. Compile the code: `cmake -DBUILD_CODE_COVERAGE=ON .. && make -j3`

## Generate PDF Documentation of the projet
1. install texlive: `apt-get install texlive`
2. install intall some texlive packages: `apt-get install texlive-math-extra texlive-science texlive-latex-extra texlive-lang-french`
3. The output document is generated in the build folder to prevent from overwriting the one in the project root path

## Usage
1. Unit test are available to test `make code-coverage`.
2. To test render : `./bin/client render`.


## Contributing
1. Fork it!
2. Create your feature branch: `git checkout -b my-new-feature`
3. Commit your changes: `git commit -am 'Add some feature'`
4. Push to the branch: `git push origin my-new-feature`
5. Submit a pull request :D

## History
* Release 1.1 : Initial Rapport and first test code.
* Release 1.final : States implemented and unit tests.

## Credits
* bansl 
* MathHadj

## License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details
