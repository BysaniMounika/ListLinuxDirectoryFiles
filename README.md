# ListLinuxDirectoryFiles
### Steps to create sample file structure.
```
$ mkdir test
$ touch test/sample.txt
$ touch test/anagram.txt
$ mkdir test/sub
$ touch test/sub/mile.txt
$ touch test/sub/management.txt
$ touch test/links.txt
```

### Compile the project file.
```
$ gcc listFiles.c -o listFiles
```

### Input Foramt to run the executable file.
```
$ ./listFiles "[directoryPath]" "[subString]" "[N]"
```

Result will be displayed in "output.txt" file upon successful execution.
### Output Format: 
Data will be displayed in 3 fields.  
First field conatins string which represents enabled modes(R - read, W - write, X - Execute).  
Second field represents size.  
Third field represents name.  

### Sample Test 1:
```
$ ./listFiles "test" "a" "3"
$ cat output.txt
Mode Size            FileName
R    0               anagram.txt
R    0               management.txt
R    0               sample.txt
```

### Sample Test 2:
```
$ ./listFiles "testw" "a" "3"
Directory doesn't exist
```

### Sample Test 3:
```
$ ./listFiles "test" "a" "3r"
Third parameter has to be an integer.
```

### Sample Test 4:
```
$ ./listFiles " test " " i " "1"
$ cat output.txt
Mode Size            FileName
R    0               mile.txt
```

### To remove sample file structure.
```
$ rm -rf test
```
