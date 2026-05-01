*This project has been created as part of the 42 curriculum by mmusquer, mvignes.*

# minishell

## objective
Reproduire un shell tres simplifier qu'on nomera minishell

## Description
L'objectif du projet est de reproduire un shell tres simplifier. C'est pas parce qu'il est simplifier au shell que cela reste un projet rapidement baclable. Le shell on le retrouve dans nos tout nos ordinateurs que se soit sur windows, linux ou bien macos.

### Dificulter
Les deux premiere dificulter selon moi est que c'est le plus gros projet en terme de temps qu'on est eux. Il faut donc penser a comment s'organiser des le debut du projet, savoir evaluer combien de temps chaque tache va nous prendre pour respecter les deadline.
Et la deuxieme dificulter c'est que c'est un projet de groupe. Savoir bien communiquer pour ne pas faire des parties que l'autre est entrain de faire ou modifier des sorties de fonction pendant qu'un autre travail dessus.

### Project Structure
```bash
minishell/
├── Makefile             # Master Makefile
├── README.md            # README.md
├── includes/            # Headers
│   ├── builtin.h
│   ├── env.h
│   ├── execution.h
│   ├── expand.h
│   ├── lexer.h
│   ├── libft.h
│   ├── minishell.h
│   └── parser.h
├── srcs/                # .c files
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
│   ├── execution/
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
│   ├── expand/
│   |   ├── expand_concatenate.c
│   |   ├── expand_dollards.c
│   |   ├── expand_quotes.c
│   |   └── expand.c
│   ├── lexer/
│   |   ├── lexer_checker_bracket.c
│   |   ├── lexer_checker_main.c
│   |   ├── lexer_checker_sep_redir.c
│   |   ├── lexer_cut.c
│   |   ├── lexer_utils.c
│   |   └── lexer.c
│   ├── libft/
│   |   └── *all_libft_mvignes.c*
│   ├── parser/
│   |   ├── parser_cut.c
│   |   ├── parser_free.c
│   |   ├── parser_utils.c
│   |   └── parser.c
│   ├── signal/
│   |   └── signal.c
│   ├── utils/
│   |   ├── lstenv.c
│   |   ├── other_split.c
│   |   ├── print_struc.c
│   |   └── utils.c
│   ├── main_cut.c
│   └── main.c
├── .objects/            # .o files
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
ls | grep mi
cd srcs/
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