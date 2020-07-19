# RSA cryptography

Console application that implements the RSA algorithm using to
generate keys (private and public), encrypt and decrypt file.

The application was created for private teaching
purpose and is not suitable for use due to the limited
size of prime numbers generated (maximum 64 bits)

### Steps of the algorithm

The whole RSA algorithm consists of the parts described below.

#### Generating keys

1. Find 2 big prime numbers, ex: p and q
2. Calculate euler function value: phi = (p - 1) x (q - 1)
   Calculate euler function module: n = p * q
3. Find the relatively prime number (e) with the calculated
   euler funtion value (phi)
4. Calculate inverse modulo phi to e
   satisfying the equation: d x e mod phi = 1
5. Pair (e, n) is a public key
6. Pair (d, n) is a private key

#### File encryption

1. Get public key (e, n)
2. Replace the message to encrypt with natural numbers: t
3. Perform encryption operation: c = t^e mod n
4. c numbers are encrypted message

#### File decryption

1. Get encrypted message
2. Convert c to oiginal t value: t = c^d mod n
3. Recreate text characters from number t

---

## Technology
* C++17
* cmake
* make

---

## Requirements
* Operation system: Windows, Linux, macOS
* C++17 compiler
* cmake tool installed
* make tool installed
---

## External library
* math-library: https://github.com/dmarcini/math-library.git
---

## Building & Running
Example for Linux system.
* install external libraries:
```
git clone library-github-url
cd path-to-clone-library
mkdir build
cd build
cmake ..
sudo make install
```
* build RSA-cryptography app
```
git clone https://github.com/dmarcini/RSA-cryptography.git
cd path-to-clone-directory
mkdir build
cd build
cmake ..
make
```
* run RSA-cryptography app
```
cd path-to-clone-directory/bin
./RSA-cryptography --selected-option(s)
```
Possible options:
* -h, --help
* --gen-keys=path_for_key
* --key=pub_key_path --encrypt=file_path
* --key=priv_key_path --decrypt=file_path

## Sources
All mathematical algorithms written in this project were based on
their description presented on the site:
https://eduinf.waw.pl/inf/
