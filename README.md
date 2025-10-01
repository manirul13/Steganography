<<<<<<< HEAD
This is the content on your main branch
=======
This is the new content from your temp-fix branch
>>>>>>> temp-fix
# LSB Image Steganography

=======

**A secure and efficient command-line tool written in C for hiding secret messages inside 24-bit BMP images using the Least Significant Bit (LSB) steganography technique.**
 

📖 Overview
LSB Steganography is a technique to hide information within the digital data of an image file. This program modifies the least significant bits of the pixel data in a BMP image to encode a secret message. Because only the least significant bits are altered, the change is visually imperceptible to the human eye.

This project demonstrates core concepts of file handling, bit-level manipulation, and data structures in the C programming language.

Key Features:

Encode Message: Hide a secret text message inside a BMP image.

Decode Message: Extract a hidden message from a BMP image.

Password Protection: Optional password-based encryption for the hidden message for an added layer of security.

High Capacity: Utilizes all three color channels (R, G, B) of 24-bit BMP pixels for maximum data hiding capacity.

Lossless Operation: The encoding process does not significantly degrade the quality of the cover image.

🚀 Getting Started
Prerequisites
To compile and run this project, you need:

A C compiler (e.g., GCC - GNU Compiler Collection)

The make build tool (optional, but recommended)

A basic understanding of the command line/terminal

Installation & Compilation
Clone the repository

bash
git clone https://github.com/manirul13/Steganography
cd lsb-steganography
Compile the source code

Using the provided Makefile (Recommended):

bash
make
This will create an executable named stegano.

Compiling manually with GCC:

bash
gcc -o stegano main.c steganography.c -Wall -Wextra
📚 Usage:
# The message will be encrypted with the password before hiding

Encoding Syntax:

bash
./a.out -e beautiful.bpm secret.txt stego.bmp
 
Decoding Syntax: 

bash
./a.out -d stego.bmp decode.txt

# Output: The secret message is: "Meet me at 5"

If a password was used during encoding:

bash
./stegano -d -p secret_image.bmp mypassword123
🗂️ Project Structure
text
lsb-steganography/
├── src/
│ ├── test_encode.c # Handles command-line arguments and program flow
│ └── encode.c      # Core logic for encoding (LSB manipulation)
│ └── decode.c      # Core logic for decoding (LSB manipulation)
│ └── decode.h      # Header file with function declarations & structs
│ └── decode.h      # Header file with function declarations & structs
│ └── common.h      # Header file with function declarations & structs
├── samples/        # Example BMP images to test with
├── Makefile        # Instructions for the 'make' build tool
├ .gitignore        # Files for Git to ignore
└── README.md       # This file
🔧 How It Works
Encoding Process
The program reads the input BMP file, ensuring it's a supported 24-bit format.

The secret message is combined with a delimiter (or encrypted with a password if provided).

The program iterates through each pixel of the image, one color channel (Blue, Green, Red) at a time.

For each character in the message, it hides each bit by overwriting the least significant bit (LSB) of a pixel's color channel.

The modified pixels are written to a new output BMP file.

Decoding Process
The program reads the encoded BMP file.

It iterates through the pixels in the same order, reading the LSB of each color channel.

It collects these bits, reassembling them into bytes to reconstruct the original message.

The process stops when a pre-defined delimiter sequence is found, revealing the complete message.

🤝 Contributing
Contributions are welcome! If you have ideas for improvements, new features, or find any bugs, please feel free to:

Fork the Project.

Create your Feature Branch (git checkout -b feature/AmazingFeature).

Commit your Changes (git commit -m 'Add some AmazingFeature').

Push to the Branch (git push origin feature/AmazingFeature).

Open a Pull Request.

Please ensure your code follows the existing style.

⚖️ License
This project is licensed under the MIT License. See the LICENSE file for details.

📧 Contact
[MANIRUL ISLAM] - [manirulislam.official13@gmail.com]

Project Link: https://github.com/manirul13/Steganography

🙏 Acknowledgments
This project was inspired by the fundamental concepts of steganography and information security.

Thanks to the countless tutorials and resources available for learning C and file format structures.
