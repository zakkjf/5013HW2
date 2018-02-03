# cmocka example for ECEN 5013

* [cmocka](https://cmocka.org/)

* cmocka [API](https://api.cmocka.org/index.html)

cmocka is included in this repository as a git subtree. See
3rd-party/README.md for details.

## Requirements

* cmake - available through most package managers.

## Build

* building cmocka:

    ```SHELL
    make cmocka
    ```

    This will go into the 3rd-party libraries directory and call cmake
    correctly to build cmocka.

* building and running tests:

    ```SHELL
    make test
    ```
    
* building main executable

    ```SHELL
    make all
    ```
    
* cleaing up local build artifacts:

    ```SHELL
    make clean
    ```
    
* removing all generated files, including 3rd-party builds

    ```SHELL
    make clobber
    ```
    
## Source

Included source files are:

* dll.{h|c} - library containing doubly-linked list functionality

* test_quadratic.c - unit tests for the doubly-linked list library

* main.c - simple demo driver using dll library.

