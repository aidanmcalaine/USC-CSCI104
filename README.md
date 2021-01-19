# Homework

Please do not share your code or copy code from other students.
Once you've read through this, feel free to delete it, though you may want to keep the formatting and linting sections as reference.

## Contents

You might have noticed a couple extra files lying around this repository.
Here's a rundown of what they do:

- `.clang-format` provides some settings for `clang-format`, which is a tool you can use to automatically reformat your code.
  You can read more about code style and formatting on [the wiki](https://github.com/csci104/wiki/blob/master/style.md), and the cheat sheet is below.
  Feel free to page through the configuration file if you're interested in how it works.
- `.clang-tidy` provides settings for `clang-tidy`, which does semantic checks on C++ files.
  We've included instructions on how to use this tool [below](#linting) as well.
- `.editorconfig` gives most IDEs some idea about how to handle whitespace in your code files.
  It also limits the charset to `utf8` to avoid any encoding bugs.
- `.gitignore` prevents files from being added to the index by git.
  Make sure you use this to avoid pushing things like compiled binaries and test files to keep your repository slim and ensure that graders can easily pick out what they need to grade.
  You can add a `.gitignore` file in any of this repository's subdirectories to add rules relative to that path.

## Formatting

`clang-format` is a utility built on top of the `clang` tooling that, among other things, visually restructures code based on a set of style guidelines.
Based on a collection of settings that may be specified in a `.clang-format` file, it manages things like spacing, newlines, brackets, and indentation.
We have already put a `.clang-format` file in your homework repository, so any files in or under the root directory will be formatted our ruleset.

You can invoke `clang-format` from the command line, and it comes installed out of the box on our [Docker container](https://github.com/csci104/docker).
Running the utility within your homework repository is as easy as:

```shell script
clang-format -i directory/file.cpp
``` 

If you want to format multiple files in a directory, you can use wildcard operators:

```shell script
# Format all .cpp files in directory/
clang-format -i directory/*.cpp

# Format all .cpp and .h/.hpp files in directory/ 
clang-format -i directory/*.{h,hpp,cpp}
```

Lastly, you can use the double asterisk to recursively glob.
This is necessary when you also want to format files in subdirectories.

```shell script
# Format all .cpp and .h/.hpp files in directory/ and subdirectories
clang-format -i directory/**/*.{h,hpp,cpp}
```

## Linting

`clang-tidy` is another tool for analyzing and fixing your code, but instead of focusing on syntax, it deals with semantics.
In short, `clang-tidy` provides additional insights into your code.
For example, it can warn you about unsafe memory management, point out unused variables, and suggest more modern approaches for certain snippets.
Much like `clang-format`, you can invoke `clang-tidy` from the command line.
We recommend you use it one file at a time so that the output is more digestible:

```shell script
# Get warnings about a single file
clang-tidy directory/file.cpp --

# You can add arguments you'd pass to g++ after the --
clang-tidy directory/file.cpp -- -I included/
```

Unlike `clang-format`, we don't require you to use `clang-tidy`.
Instead, we just offer it as a way for you to help debug your work.
Oftentimes, you'll find that heeding the warnings from `clang-tidy` will save you from bugs before you even find them.

Another tool you can use in this vein is `cppcheck`.
You can invoke `cppcheck` fairly similarly:

```shell script
# Check file.cpp
cppcheck --enable=all directory/file.cpp

# Specify include directories as well
cppcheck --enable=all directory/file.cpp -I included/
```
