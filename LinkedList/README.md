### Installation ###

  pip install --user -r forward_chaining/docs/requirements.txt
or
  python3 -m pip install --user -r forward_chaining/docs/requirements.txt


### Usage ###

 Compilation
  $ mkdir build
  $ cd build
  $ cmake ../forward_chaining
  $ make
  
  
 Run test
  $ make test
  
  
 Build the docs
  $ make docs
  
  
 Creates archives
  $make package
  $make package_source
  
  
 Install package
  $ sudo make install
  
  
### Locations ###

 Library location after $make
  build/src/forward_chaining/libforward_chaining.so

 Library location after $ sudo make install
  /usr/local/lib/libforward_chaining.so

  
 Forward Chaining Executable
  build/rules
  
  
 Archives
  build/Forward_Chaining-1.0-Linux.zip
  build/Forward_Chaining-1.0-Source.zip
  

### Note ###

  All the .c and .h files have been tested and approved by cclint.
  
