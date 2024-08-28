#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include "libft.h"

#include <stdio.h>


typedef enum lex_state
{
    WORD,
    DELIM,
    INSQTS,
    INDQTS
} lex_state;

typedef enum e_toktype
{
    UNDETERM,
    END,
    SQERR,
    DQERR,
    NWLINE,
    PIPE,
    CMD,
    ARGS,
    HEREDOC,
    INPUT,
    OUTPUT,
    APPEND,
    DISCARD
}   t_toktype;

typedef struct s_tok
{
    char *word;
    int idx;
    struct s_tok *next;
    t_toktype type;
}   t_tok;

void process_tokens(t_tok *head);

void print_toktype(t_tok *token)
{
    if (token->type == UNDETERM)
        printf("UNDETERM ");
    else if (token->type == END)
        printf("END\n");
    else if (token->type == SQERR)
        printf("SQERR ");
    else if (token->type == DQERR)
        printf("DQERR ");
    else if (token->type == NWLINE)
        printf("NWLINE ");
    else if (token->type == PIPE)
        printf("PIPE ");
    else if (token->type == CMD)
        printf("CMD ");
    else if (token->type == ARGS)
        printf("ARGS ");
    else if (token->type == HEREDOC)
        printf("HEREDOC ");
    else if (token->type == INPUT)
        printf("INPUT ");
    else if (token->type == OUTPUT)
        printf("OUTPUT ");
    else if (token->type == APPEND)
        printf("APPEND ");
    else if (token->type == DISCARD)
        printf("DISCARD ");
}

t_tok *gen_token(t_toktype type, int len)
{
    t_tok *token = malloc(sizeof(t_tok));
    token->next = NULL;
    token->type = type;
    token->word = ft_calloc(len + 1, sizeof(char));
    token->idx = 0;
    if (!token->word)
    {
        free(token);
        return (NULL);
    }
    return token; //need to handle if it is NULL  
}

char    *expand(char *start, int *lenvar, char **envp)
{
    int i = 0;
    while(start[i] && ft_isalnum(start[i]))
        i++;
    *lenvar = i;
    char *var = ft_strdup(start);
    var[i] = '\0';
    int len = ft_strlen(var);
    while (*envp)
	{
		if (ft_strncmp((const char *) *envp, var, len) == 0 || *envp[len] == '=')
			break ;
		envp++;
	}
    free(var);
	if (!*envp)
		return (ft_strdup(""));
    return (ft_strdup(*envp + len + 1)); //need to free though later
}

void    change_word(t_tok *token, char *var, int len)
{
    int lenvar = ft_strlen(var);
    int lenword = ft_strlen(token->word);
    char *newword = ft_calloc(lenvar + len + 1, sizeof(char));
    ft_strlcpy(newword, token->word, lenword + 1);
    ft_strlcat(newword, var, lenvar + len + 1);
    free(token->word);
    free(var);
    token->word = newword;
    token->idx += lenvar;
    //printf("idx is %d\n", token->idx);
}

t_tok *lexer(char *input, lex_state state, t_tok *tail, char **envp)
{
    char c;
    t_tok *head;
    int len = ft_strlen(input);
    int i = -1;

    int lenvar;
    char *varvalue;

    if (!tail)
    {
        tail = gen_token(UNDETERM, len); // need to protect malloc
        head = tail;
    }
    else
    {
        head = tail->next;
        tail->next = gen_token(NWLINE, 1);
        tail = tail->next;
        tail->word[tail->idx++] = '\n';
        tail->next = gen_token(UNDETERM, len);
        tail = tail->next;
    }
    while(input[++i])
    {
        c = input[i];
        if (state == DELIM)
        {
            if (c == ' ' || c == '\t')
                continue;
            state = WORD;
        }
        if (c == '\'')
        {
            if (state == INSQTS)
                state = WORD;
            else if (state == WORD)
                state = INSQTS;
            else
                tail->word[tail->idx++] = c;
        }
        else if (c == '\"')
        {
            if (state == INDQTS)
                state = WORD;
            else if (state == WORD)
                state = INDQTS;
            else
                tail->word[tail->idx++] = c;
        }
        else if (state == WORD && (c == ' ' || c == '\t'))
        {
            state = DELIM;
            tail->next = gen_token(UNDETERM, len);
            tail = tail->next;
        }
        else if (c == '$' && (state == WORD || state == INDQTS))
        {
            varvalue = expand(input + i + 1, &lenvar, envp);
            change_word(tail, varvalue, len);
            i += lenvar;
        }
        else
            tail->word[tail->idx++] = c;
    }
    if (state == INSQTS)
        tail->type = SQERR;
    else if (state == INDQTS)
        tail->type = DQERR;
    else if (state == DELIM)
        tail->type = END;
    else
    {
        tail->next = gen_token(END, 0);
        tail = tail->next;
    }
    tail->next = head;
    return (tail);
}

int main(int argc, char **argv, char **envp)
{
    char *input = NULL;
    t_tok *tail;
    t_tok *head;
    t_tok *ptr;
    if (argc != 1)
        return 2 ;
    (void)argv;
    while (1)
    {
        if (input)
            free(input);
        input = readline("prompt> ");
        if (input == NULL) //will happen with ctrl+D
            break;
        if (*input)
            add_history(input);
        tail = lexer(input, DELIM, NULL, envp);
        while (tail->type == SQERR)
        {
            input = readline("> ");
            if (input == NULL) //will happen with ctrl+D
                break;
            tail = lexer(input, INSQTS, NULL, envp);
        }
        while (tail->type == DQERR)
        {
            input = readline("> ");
            if (input == NULL) //will happen with ctrl+D
                break;
            tail = lexer(input, INDQTS, tail, envp);
        }
        head = tail->next;
        process_tokens(head);
        while (head->type != END)
        {
            print_toktype(head);
            printf("%s ", head->word);
            free(head->word);
            ptr = head->next;
            free(head);
            head = ptr;
        }
        print_toktype(head);
        free(head->word);
        free(head);
    }
}

int    io_type(t_tok *token, t_toktype type)
{
    token->type = type;
    char *io_arg;
    int idx;
    if (type == HEREDOC || type == APPEND)
        idx = 2;
    else
        idx = 1;
    if (!token->word[idx])
    {
        token->type = DISCARD;
        token->next->type = type;
    }
    else
    {
        token->type = type;
        io_arg = ft_strdup(token->word + idx);
        if (!io_arg)
            return (1);
        free(token->word);
        token->word = io_arg; 
    }
    return (0);
}


void process_tokens(t_tok *token)
{
    int cmd = 0;

    while (token->type != END)
    {
        if (token->type >= HEREDOC)
        {   
            token = token->next;
            continue ;
        }
        if (ft_strncmp(token->word, "|", 2) == 0)
            token->type = PIPE;
        else if (token->word[0] == '<')
        {
            if (token->word[1] == '<')
                io_type(token, HEREDOC);
            else
                io_type(token, INPUT);
        }    
        else if (token->word[0] == '>')
        {
            if (token->word[1] == '>')
                io_type(token, APPEND);
            else
                io_type(token, OUTPUT);
        }
        else if (!cmd)
        {
            token->type = CMD;
            cmd = 1;
        }
        else
            token->type = ARGS;
        token = token->next;
    }
}