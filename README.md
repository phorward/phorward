
DESCRIPTION
===========

The Phorward Toolkit provides a powerful, extensional set of useful functions for C programmers. It focuses on compiler development-related tasks, but can also be used for general purpose development tasks using the C programming language.

It comes with many useful extensions for universal linked lists, hash-tables, dynamic stacks and arrays, extended string management functions and some platform-independent, system-specific helper functions.

Based on top of these general purpose functions, the Phorward Toolkit provides more specializing tools for regular expression handling and parser implementation, focusing on both LL and LR/LALR grammars and parsers. Latter feature is currently under heavy development and will be made available in a consistent, well-tested environment made for implementing high-performance parsers directly in C without the usage of an additional parser generator step.


FEATURES
========

The Phorward Toolkit provides

- Universal data structures for
  - plist: For linked-lists with build-in hash table support
  - parray: For dynamic arrays and stacks
- Extended string management functions
  - consistent byte- and wide-character (unicode) function support
  - Unicode support for UTF-8 in byte-character functions
- Debug und trace facilities
- A build-in DOM-based XML-parser
- Universal system-specific functions for platform-independent C software development
- pregex: Regular expression functions, including tools for their construction, transformation and analysis
- Parser construction functions for syntax-directed LL/LR/LALR parsers with direct lookahead
- Object-oriented fashion for all function interfaces (e.g. plist, parray, pregex, pgram, ...)
- Growing code-base of more and more powerful functions

Please check out http://phorward.phorward-software.com/ from time to time to get the latest news, documentation, updates and support on the Phorward Toolkit.


BUILDING
========

Building the Phorward Toolkit is simple as every GNU-style open source program. Extract the release tarball or clone the Mercurial repository into a directory of your choice.

Then, run

  ./configure

to configure the build-system and generate the Makefiles for your current platform. After successful configuration, run

  make

and

  make install

(properly as root), to install the toolkit into your system.

On Windows systems, the usage of http://cygwin.org/ or another Unix shell environment is required. The Phorward Toolkit also perfectly cross-compiles on Linux using the MinGW and MinGW_x86-64 compilers.

To compile into 32-Bit Windows executables, configure with

  ./configure --host=i486-mingw32 --prefix=/usr/i486-mingw32

To compile into 64-Bit Windows executables, configure with

  ./configure --host=x86_64-w64-mingw32 --prefix=/usr/x86_64-w64-mingw32


LOCAL DEVELOPMENT MAKE-BASED BUILD-SYSTEM
=========================================

Alternatively to the autotools build system used for installation, there is also a simpler method on setting up a local build system for development and testing purposes.

Once, type

  make -f Makefile.gnu make_install

then, a simple run of

  make

can be used to simply build the entire library or parts of it.

Note, that changes to the build system then must be done in the local Makefile, the local Makefile.gnu as well as the Makefile.am for the autotools-based build system.


AUTHOR
======

The Phorward Foundation Toolkit is developed and maintained by Jan Max Meyer, Phorward Software Technologies.

Help of any kind to extend and improve this product is always appreciated.


COPYRIGHT
=========

Copyright (C) 2006-2015 by Phorward Software Technologies, Jan Max Meyer.

You may use, modify and distribute this software under the terms and conditions of the 3-clause BSD license. The full license terms can be obtained from the file LICENSE.

THIS SOFTWARE IS PROVIDED BY JAN MAX MEYER (PHORWARD SOFTWARE TECHNOLOGIES) AS IS AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL JAN MAX MEYER (PHORWARD SOFTWARE TECHNOLOGIES) BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

