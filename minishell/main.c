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
    NWLINE,
    PIPE,
    CMD,
    ARGS,
    HEREDOC,
    INPUT,
    OUTPUT,
    APPEND,
    BEGIN,
    END,
    SQERR,
    DQERR
}   t_toktype;

typedef struct s_tok
{
    char *word;
    struct s_tok *next;
    t_toktype type;
}   t_tok;

void process_tokens(t_tok *head);


size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (*((char *)s + i) != '\0')
		i++;
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	bflen;
	size_t	i;

	if (ft_strlen(s) < start)
		bflen = 0;
	else if (ft_strlen(s) - start < len)
		bflen = ft_strlen(s) - start;
	else
		bflen = len;
	ptr = malloc(bflen + 1);
	if (ptr == NULL)
		return (NULL);
	i = start;
	while (i < bflen + start)
	{
		ptr[i - start] = s[i];
		i++;
	}
	ptr[i - start] = '\0';
	return (ptr);
}

t_tok *gen_token(t_toktype type, char *input, int start, int len)
{
    t_tok *token = malloc(sizeof(t_tok));
    token->next = NULL;
    token->type = type;
    token->word = NULL;
    if (type == END || type == BEGIN || type == NWLINE)
        return (token);
    token->word = ft_substr(input, start, len);
    return token; //need to handle if it is NULL  
}

t_tok *lexer(char *input, lex_state state, t_tok *tail)
{
    char c;
     t_tok *head;
    if (!tail)
    {
        tail = gen_token(BEGIN, NULL, 0, 0); // need to protect malloc
        head = tail;
    }
    else
    {
        head = tail->next;
        tail->next = gen_token(NWLINE, NULL, 0, 0);
        tail = tail->next;
    }
    int start = 0;
    int wordlen;
    int i = -1;
    while(input[++i])
    {
        c = input[i];
        if (state == DELIM)
        {
            if (c == ' ' || c == '\t')
                continue;
            state = WORD;
            start = i;
        }
        if (c == '\'')
        {
            if (state == INSQTS)
                state = WORD;
            else if (state == WORD)
                state = INSQTS;
        }
        else if (c == '\"')
        {
            if (state == INDQTS)
                state = WORD;
            else if (state == WORD)
                state = INDQTS;
        }
        if (state == WORD && (c == ' ' || c == '\t' || !input[i+1]))
        {
            state = DELIM;
            wordlen = i - start;
            if (!input[i+1])
                wordlen = i + 1 - start;
            tail->next = gen_token(UNDETERM, input, start, wordlen);
            tail = tail->next;
        }
    }
    if (state == INSQTS)
        tail->next = gen_token(SQERR, input, start, i - start);
    else if (state == INDQTS)
        tail->next = gen_token(DQERR, input, start, i - start);
    else
        tail->next = gen_token(END, NULL, 0, 0);
    tail = tail->next;
    tail->next = head;
    return (tail);
}

int main()
{
    char *input = NULL;
    t_tok *tail;
    t_tok *head;
    t_tok *ptr;

    while (1)
    {
        if (input)
            free(input);
        input = readline("prompt> ");
        if (input == NULL) //will happen with ctrl+D
            break;
        if (*input)
            add_history(input);
        tail = lexer(input, DELIM, NULL);
        while (tail->type == SQERR)
        {
            input = readline("> ");
            if (input == NULL) //will happen with ctrl+D
                break;
            tail = lexer(input, INSQTS, NULL);
        }
        while (tail->type == DQERR)
        {
            input = readline("> ");
            if (input == NULL) //will happen with ctrl+D
                break;
            tail = lexer(input, INDQTS, tail);
        }
        head = tail->next;
        process_tokens(head);
        while (head->type != END)
        {
            if (head->type == BEGIN)
                printf("BEGIN ");
            else if (head->type == NWLINE)
                printf("\n");
            else if (head->type == PIPE)
                printf("PIPE ");
            else
                printf("%s ", head->word);
            if (head->word)
                free(head->word);
            ptr = head->next;
            free(head);
            head = ptr;
        }
        printf("END\n");
        free(head);
    }
}

void    io_type(t_tok *token, t_toktype type)
{
    token->type = type;
    t_tok *wcat;
    int idx;
    if (type == HEREDOC || type == APPEND)
        idx = 2;
    else
        idx = 1;
    if (!token->word[idx])
        token->next->type = type;
    else
    {
        token->type = type;
        token->word = 
    }
}


void process_tokens(t_tok *token)
{
    static int cmd;

    if (token->type == END)
        return ;
    else if (token->type == BEGIN)
    {
        cmd = 0;
        process_tokens(token->next);
        return ;
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
        token->type = CMD;
    else
        token->type = ARGS;
    process_tokens(token->next);
}