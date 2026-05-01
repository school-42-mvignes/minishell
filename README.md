*This project has been created as part of the 42 curriculum by mmusquer, mvignes.*

# minishell

## objective
The goal of this project is to recreate a simplified shell, which we have named minishell.

## Description
The aim is to build a functional command-line interface from scratch. Don't be fooled by the "simplified" label; this project is far from something that can be rushed. Shells are the backbone of our interaction with computers, whether on Windows, Linux, or macOS. Building one requires a deep understanding of process management and system calls.

### Features
- **Command Execution:** Full path handling and relative paths.
- **Built-ins:** `cd`, `echo`, `pwd`, `export`, `unset`, `env`, `exit`.
- **Pipes & Redirections:** Support for `|`, `>`, `<`, `>>`, and `<<`.
- **Logical Operators:** Implementation of `&&` and `||` with parentheses for priority.
- **Wildcards:** Pattern matching using the `*` character.
- **Environment Management:** Variable expansion and exit status handling (`$?`).
- **Signal Handling:** Proper management of interrupts in both interactive and execution modes.


### Challenges
- **Time Management:** This project is the most extensive one we have encountered so far in terms of scope and duration. It demanded rigorous organization from day one, requiring us to evaluate tasks accurately to stay on track and meet deadlines.
- **Team Collaboration:** Working as a pair introduced a new layer of complexity. Maintaining constant communication was essential to prevent redundant work and ensure that modifications to core functions didn't break our partner's progress.


### Project Structure summarise
```bash
minishell/
├── Makefile             # Master Makefile
├── README.md            # README.md
├── includes/            # Headers
├── srcs/                # Source files .c
│   ├── builtin/         # Built-in command logic
│   ├── execution/       # Process handling, pipes, and redirections
│   ├── expand/          # Variable and quote expansion
│   ├── lexer/           # Tokenization of the input string
│   ├── libft/           # Custom C library
│   ├── parser/          # Building the abstract syntax tree
│   ├── signal/          # Signal management (Ctrl-C, etc.)
│   ├── utils/           # Utils for multiple portion project
│   └── main.c
├── .objects/            # Source files .o
├── .readline.supp       # file for removes memory leaks coming from readline
├── .last_colors         # Stores the last color used for compilation
└── .gitignore           # Used to avoid pushing these files to git
```

### Project Structure complete
```bash
minishell/
├── Makefile             # Master Makefile
├── README.md            # README.md
├── includes/            # Headers
│   ├── builtin.h        # Built-in command logic
│   ├── env.h
│   ├── execution.h
│   ├── expand.h
│   ├── lexer.h
│   ├── libft.h
│   ├── minishell.h
│   └── parser.h
├── srcs/                # Source files .c
│   ├── builtin/
│   |   ├── cd.c
│   |   ├── echo.c
│   |   ├── env.c
│   |   ├── exit.c
│   |   ├── export_utils.c
│   |   ├── export.c
│   |   ├── orchestrator.c
│   |   ├── pwd.c
│   |   ├── unset.c
│   |   └── utils.c
│   ├── execution/       # Process handling, pipes, and redirections
│   |   ├── and.c
│   |   ├── env_utils.c
│   |   ├── env.c
│   |   ├── exec_cmd.c
│   |   ├── exec_line.c
│   |   ├── or.c
│   |   ├── path.c
│   |   ├── pipe.c
│   |   ├── redir_heredoc_utils.c
│   |   ├── redir_heredoc.c
│   |   ├── redir.c
│   |   ├── utils.c
│   |   ├── wildcard_utils.c
│   |   └── wildcard.c
│   ├── expand/          # Variable and quote expansion
│   |   ├── expand_concatenate.c
│   |   ├── expand_dollards.c
│   |   ├── expand_quotes.c
│   |   └── expand.c
│   ├── lexer/           # Tokenization of the input string
│   |   ├── lexer_checker_bracket.c
│   |   ├── lexer_checker_main.c
│   |   ├── lexer_checker_sep_redir.c
│   |   ├── lexer_cut.c
│   |   ├── lexer_utils.c
│   |   └── lexer.c
│   ├── libft/
│   |   └── *all_libft_mvignes.c*
│   ├── parser/          # Building the abstract syntax tree
│   |   ├── parser_cut.c
│   |   ├── parser_free.c
│   |   ├── parser_utils.c
│   |   └── parser.c
│   ├── signal/          # Signal management (Ctrl-C, etc.)
│   |   └── signal.c
│   ├── utils/
│   |   ├── lstenv.c
│   |   ├── other_split.c
│   |   ├── print_struc.c
│   |   └── utils.c
│   ├── main_cut.c
│   └── main.c
├── .objects/            # Source files .o
│   ├── builtin/
│   |   ├── cd.o
│   |   ├── echo.o
│   |   ├── env.o
│   |   ├── exit.o
│   |   ├── export_utils.o
│   |   ├── export.o
│   |   ├── orchestrator.o
│   |   ├── pwd.o
│   |   ├── unset.o
│   |   └── utils.o
│   ├── execution/
│   |   ├── and.o
│   |   ├── env_utils.o
│   |   ├── env.o
│   |   ├── exec_cmd.o
│   |   ├── exec_line.o
│   |   ├── or.o
│   |   ├── path.o
│   |   ├── pipe.o
│   |   ├── redir_heredoc_utils.o
│   |   ├── redir_heredoc.o
│   |   ├── redir.o
│   |   ├── utils.o
│   |   ├── wildcard_utils.o
│   |   └── wildcard.o
│   ├── expand/
│   |   ├── expand_concatenate.o
│   |   ├── expand_dollards.o
│   |   ├── expand_quotes.o
│   |   └── expand.o
│   ├── lexer/
│   |   ├── lexer_checker_bracket.o
│   |   ├── lexer_checker_main.o
│   |   ├── lexer_checker_sep_redir.o
│   |   ├── lexer_cut.o
│   |   ├── lexer_utils.o
│   |   └── lexer.o
│   ├── libft/
│   |   └── *all_libft_mvignes.o*
│   ├── parser/
│   |   ├── parser_cut.o
│   |   ├── parser_free.o
│   |   ├── parser_utils.o
│   |   └── parser.o
│   ├── signal/
│   |   └── signal.o
│   ├── utils/
│   |   ├── lstenv.o
│   |   ├── other_split.o
│   |   ├── print_struc.o
│   |   └── utils.o
│   ├── main_cut.o
│   └── main.o
├── .readline.supp         # file for removes memory leaks coming from readline
├── .last_colors          # Stores the last color used for compilation
└── .gitignore            # Used to avoid pushing these files to git
```

---

## Instructions

### Compilation
```bash
make
```

### Execution
```bash
./minishell
```

### Manual Testing
```bash
./minishell
Minishell$ echo "Hello world" > file.txt
Minishell$ cat file.txt && rm file.txt
Hello world
Minishell$ export MY_VAR=42
Minishell$ echo $MY_VAR
42
Minishell$ echo -n test
testMinishell$
Minishell$ export test1=a test2-=b test3+=c test4d
Minishell: export:`test2-=b': not a valid identifier
Minishell$ export | grep test
export test1="a"
export test3+="c"
export test4d=""
Minishell$ export test1=a test2-=b test3+=c test4d
Minishell: export:`test2-=b': not a valid identifier
Minishell$ export | grep test
export test1="a"
export test3+="cc"
export test4d=""
Minishell$ unset test11 test2 test3 test4
Minishell$ export | grep test
export test1="a"
export test4d=""
Minishell$ echo salut1 > test1
Minishell$ echo salut2 > test2
Minishell$ echo salut3 > test3
Minishell$ echo salut4 > test4
Minishell$ mkdir test
Minishell$ mv test1 test2 test3 test4 test
Minishell$ cd test
test/     teststar/ 
Minishell$ cd test
Minishell$ pwd
/home/mvignes/Documents/github/minishell/test
Minishell$ cat *
salut1
salut2
salut3
salut4
Minishell$ cat t*t*
salut1
salut2
salut3
salut4
Minishell$ cat t*t1
salut1
Minishell$ (cat t*t1 | grep bonjour) || echo OK
OK
Minishell$ (cat t*t1 | grep bonjour) && echo OK
Minishell$ (cat t*t1 | grep salut) && echo OK
salut1
OK
Minishell$ 
exit
bash-5.2$ ./minishell
Minishell$ ./minishell
Minishell$ env | grep SHLVL
SHLVL=7
Minishell$ ./minishell
Minishell$ ./minishell
Minishell$ ./minishell
Minishell$ ./minishell
Minishell$ ./minishell
Minishell$ ./minishell
Minishell$ env | grep SHLVL
SHLVL=13
Minishell$ 
exit
Minishell$ 
exit
Minishell$ 
exit
Minishell$ 
exit
Minishell$ 
exit
Minishell$ 
exit
Minishell$ 
exit
Minishell$ 
exit
bash-5.2$ 
exit
bash-5.2$ env | grep SHLVL
SHLVL=4
bash-5.2$ 
...
```

---

## Resources
- [Manual bash](https://www.justice.gov/epstein/files/DataSet%209/EFTA00315849.pdf)
- [Doc Minishell](https://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html)
- [Doc code sh](https://pubs.opengroup.org/onlinepubs/009695399/utilities/sh.html)
- [Doc all fonction readline](https://tiswww.case.edu/php/chet/readline/readline.html#index-rl_005freplace_005fline)
- [Doc historique](https://tiswww.case.edu/php/chet/readline/history.html)
- [Subshells](https://tldp.org/LDP/abs/html/subshells.html)

**For other fonction**
- [Open group](https://pubs.opengroup.org/onlinepubs/)
- [die.net](https://www.die.net/)
- [koor](https://koor.fr/)
- [IBM](https://www.ibm.com/docs/en/ibm-mq/9.2.x?topic=SSFKSJ_9.2.0/com.ibm.mq.ref.dev.doc/q093670_.html)
- [forum dev](https://www.developpez.net/forums/d235094/c-cpp/c/fonction-opendir/)
- [toturiel hostinger](https://www.hostinger.com/fr/tutoriels)

#### Artificial intelligence (Gemini) was used for the following tasks : Understanding of the subject and help with the translation into English of the README.

    Checking the README compliance with 42 project requirements.

    Assistance in structuring the documentation plan.

    Technical translation of the content.