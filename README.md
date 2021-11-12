# get-hash-checksum


## HOW TO USE THIS SOFTWARE

### 1. Install openssl development library -> libssl-dev in Ubuntu
```
$ apt install libssl-dev build-essential
```

&nbsp;&nbsp;&nbsp;libssl-dev is a library for development with openssl related API.  

&nbsp;&nbsp;&nbsp;build-essential is a package with bunch of building tools, like ggc, ...etc.



### 2. Download this repository and make

```
$ cd get-hash-checksum/ && make
```

### 3. get hash value of file

#### get file hash value only

&nbsp;&nbsp;&nbsp;This command will display the hash value of the "example_file_for_hash".

```
$ ./get-hash-checksum   ./files/example_file_for_hash
```

![hash_only_pic](./README.files/hash_only.png)

#### get file hash value and comapring with yours

&nbsp;&nbsp;&nbsp;This command will display the hash value of the "example_file_for_hash".

```
$ ./get-hash-checksum   ./files/example_file_for_hash   YOUR_HASH_VALUE_HERE
```

#### MATCH
![hash_with_valify_1](./README.files/hash_with_valify_1.png)

#### NOT MATCH
![hash_with_valify_2](./README.files/hash_with_valify_2.png)


Enjoy it, 
if this suit your needs. :)