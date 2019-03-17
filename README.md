# TheoryOfAlgorithms_SHA256

### Project Steps:

#### 30.01.2019 The first step regarding the project was to read the document under the title "SECURE HASH STANDARD" which is available under the link [1]. Then I decided to watch additional videos that helped me to understand more exactly what is SHA_256 [2], [3].

#### 09.02.2019  With the help of a video prepared by the lecturer, I was able to write a program that calculated 64 constants from SHA standards. First, I had to declare the first 64 primes numbers. Then, calculate the cube root of a prime numbers and  fractional part of a cube with 64 prime numbers. Next find the first 32 bits of decimal place of the number. Last part was to print this number in hexadecimal.[4]

#### 14.02.2019 Developed a program called “bit” which contains a bit operator that are used in secure hash algorithm[5]. Follow this link to find out more information’s about bitwise operators in c [6].

#### 28.02.2019 Following the video[7] that was recorded by our lecturer, I was able to develop the first part of the sha256 algorithm. Program  includes five functions. First which is sha256 calculates the sha256 bit algorithm but currently doesn’t return anything. Sig0 and sig1 functions are defined in hash standard which takes a single 32-bit integer as input and returns 32-bit integer as output. Functions rotr and shr takes two 32-bit integer arguments and returns 32-bit integer (n – amount of rotations).  Definitions for those function can be found under section 3.2 and 4.1.2 in Secure Hash Standards. 

#### 02.03.2019 Declared K which contains sixty-four constants 32-bit words. Those words represent the first thirty-two bits of the fractional parts of the cube roots of the first sixty-four primes numbers.  All elements of M were initialized to 0. Next step will be to calculate a message block. 

#### 08.03.2019 The next step was to create a program for preprocessing. It is described in the fifth section of the Secure Hash Standard and is divided into three parts. The first is padding the message which says that the message must be a multiple of 512 bits in length. This function is implemented in my “padfile” program[8] which also opens and read files. Padding can be inserted before the beginning of the process. It can contain the padding. 

#### 16.03.2019 This week I continued on padding message. Message is multiple of 512 bits in length. Chops the message up into 512 bits blocks and deal with each block in turn, as goes through the message. Generating new hash values as going through and once deals with the last message block, whatever the hash value is at that point this is the final hash value. Also converted big endian to little endian[9] for both 32- and 64-bit words.

### References:
[1] https://nvlpubs.nist.gov/nistpubs/FIPS/NIST.FIPS.180-4.pdf</br>
[2] https://www.youtube.com/watch?v=S5wI1s4Kaf4</br>
[3] https://www.youtube.com/watch?v=mbekM2ErHfM<br>
[4] https://web.microsoftstream.com/video/e5e7f5d8-3d2f-4115-9eaa-d9b1d6a91c4e</br>
[5] https://web.microsoftstream.com/video/c24ff5f4-e5e1-4747-af8d-c2c4892856e3?referrer=https:%2F%2Flearnonline.gmit.ie%2Fcourse%2Fview.php%3Fid%3D138 </br>
[6] https://www.geeksforgeeks.org/bitwise-operators-in-c-cpp/</br>
[7] https://web.microsoftstream.com/video/db7c03be-5902-4575-9629-34d176ff1366</br>
[8] https://web.microsoftstream.com/video/9daaf80b-9c4c-4fdc-9ef6-159e0e4ccc13</br>
[9] https://stackoverflow.com/questions/2182002/convert-big-endian-to-little-endian-in-c-without-using-provided-func</br>


