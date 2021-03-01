# minishell

## Mandatory

### Basic

| Prompt | Execve |
|--------|--------|
|   OK   |   OK   |

### Builtins

| cd | env | pwd | export | unset | exit | echo |
|----|-----|-----|--------|-------|------|------|
| OK |  OK |  OK |   OK   |   OK  |  OK  |  OK  |

### Separator

| ; | \| | ' | " | > | >> | < |
|---|---|---|---|---|----|---|
| OK| OK| OK| OK| OK| OK | OK|

### Env

| $? | $_ | $... |
|----|----|------|
| OK | OK |  OK  |

### Signals

| Ctrl+C | Ctrl+D | Ctrl+\ |
|--------|--------|--------|
|   OK   |   OK   |   OK   |

## Bonus

| << | Termcaps | && / \|\| | * |
|----|----------|-----------|---|
| NO |    NO    |     NO    | NO|
## GIF

![alt text](https://i.gyazo.com/5692b2fe2d03d5a82a86397095ffcd5d.gif)

![alt text](https://i.gyazo.com/687caedc7ce7747f0d0f887a3965a80c.gif)

![alt text](https://i.gyazo.com/ecadfef06318d3428c3dd29b23fffd56.gif)

## Tester

[minishell_tester](https://github.com/thallard_minishell_tester)

## Finale garde

![alt text](https://camo.githubusercontent.com/1890d425e2dbb090d4d27f285589f3dd4273e3a71600a28173c180efe0ca8e2b/68747470733a2f2f696d6167652e70726e747363722e636f6d2f696d6167652f2d5536727732586352417973505364556b32754768512e706e67)
