### Installation ###
```bash
pip install --user -r forward_chaining/docs/requirements.txt
```
or
```bash
  python3 -m pip install --user -r forward_chaining/docs/requirements.txt
```

### Usage ###

 Compilation
 ```bash
  $ mkdir build
  $ cd build
  $ cmake ../forward_chaining
  $ make
  ```
  
 Run test
 ```bash
  $ make test
  ```
  
 Build the docs
 ```bash
  $ make docs
  ```
  
 Creates archives
 ```bash
  $make package
  $make package_source
  ```
  
 Install package
 ```bash
  $ sudo make install
  ```
  
### Locations ###

 Library location after $make
 ```bash
  build/src/forward_chaining/libforward_chaining.so
```

 Library location after $ sudo make install
 ```bash
  /usr/local/lib/libforward_chaining.so
```
  
 Forward Chaining Executable
 ```bash
  build/rules
  ```
  
 Archives
 ```bash
  build/Forward_Chaining-1.0-Linux.zip
  build/Forward_Chaining-1.0-Source.zip
  ```

### Note ###

  All the .c and .h files have been tested and approved by cclint.
  
